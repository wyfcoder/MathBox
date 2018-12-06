#include "plotpolar.h"
#include<QVBoxLayout>
#include<QMenu>
#include<QMenuBar>
#include<QFileDialog>
#include<QScreen>
#include<QtGui>
#include<QScatterSeries>
#include<QBrush>
#include<fstream>
#include<QMessageBox>

using namespace std;
plotpolar::plotpolar(QWidget *parent) : QWidget(parent)
{
    buildPainter();
    buildWindow();
    menuBar=new QMenuBar(this);
    creatActions();
    creatMenus();
}

void plotpolar::plot(vector<double> x,vector<double> y,QString name)
{
    this->new_name=name;
    if(this->x.size()!=0) this->x.clear();
    if(this->y.size()!=0) this->y.clear();
    for(unsigned i=0;i<x.size();i++)
    {
        this->x.push_back(x[i]);
        this->y.push_back(y[i]);
    }
    plot();
}


void plotpolar::buildWindow()
{    
    QVBoxLayout* mainLayout=new QVBoxLayout;
    mainLayout->addWidget(polar_view);
    mainLayout->setMargin(40);
    setMinimumSize(690,550);
    setWindowTitle(tr("MathBox Plot"));
    this->setLayout(mainLayout);
}

void plotpolar::buildPainter()
{
    polar_view  =new chartview_polar();
    chart       =new QPolarChart();
    angularAxis =new QValueAxis();
    angularAxis->setTickCount(9);
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    radialAxis  =new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%.1f");
    chart->setTitle("Polar Graph");
}

void plotpolar::creatActions()
{
    AddGraph=new QAction(tr("Add Graph"));
    connect(AddGraph,SIGNAL(triggered(bool)),this,SLOT(addGraph()));

    DeleteGraph=new QAction(tr("Delete Graph"));
    connect(DeleteGraph,SIGNAL(triggered(bool)),this,SLOT(clearWindow()));

    savePng=new QAction(tr("Save as Png"));
    connect(savePng,SIGNAL(triggered(bool)),this,SLOT(SavePlotPng()));
    saveJpg=new QAction(tr("Save as Jpg"));
    connect(saveJpg,SIGNAL(triggered(bool)),this,SLOT(SavePlotJpg()));
    saveBmp=new QAction(tr("Save as Bmp"));
    connect(saveBmp,SIGNAL(triggered(bool)),this,SLOT(SavePlotBmp()));

    help=new QAction(tr("Help Document"));

    AddGraph->setIcon(QIcon(":/picture/circle.png"));
    DeleteGraph->setIcon(QIcon(":/picture/circle.png"));
    help->setIcon(QIcon(":/picture/circle.png"));
    saveBmp->setIcon(QIcon(":/picture/circle.png"));
    savePng->setIcon(QIcon(":/picture/circle.png"));
    saveJpg->setIcon(QIcon(":/picture/circle.png"));
}

void plotpolar::creatMenus()
{
    baseOperations=new QMenu(tr("Base"));

    baseOperations->addAction(AddGraph);
    baseOperations->addSeparator();
    baseOperations->addAction(DeleteGraph);
    baseOperations->addSeparator();
    baseOperations->addAction(help);

    saveMenu=new QMenu(tr("Save"));
    saveMenu->addAction(savePng);
    saveMenu->addSeparator();
    saveMenu->addAction(saveJpg);
    saveMenu->addSeparator();
    saveMenu->addAction(saveBmp);

    menuBar->addMenu(baseOperations);
    menuBar->addMenu(saveMenu);
}

void plotpolar::SavePlotPng()
{
 QScreen *screen=QGuiApplication::primaryScreen();
 QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Png");
 QPixmap pixmap=screen->grabWindow(polar_view->winId());
 pixmap.save(fileName,"PNG");
}

void plotpolar::SavePlotJpg()
{
  QScreen *screen=QGuiApplication::primaryScreen();
  QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Jpg");
  QPixmap pixmap=screen->grabWindow(polar_view->winId());
  pixmap.save(fileName,"Jpg");
}

void plotpolar::SavePlotBmp()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Bmp");
    QScreen *screen=QGuiApplication::primaryScreen();
    QPixmap pixmap=screen->grabWindow(polar_view->winId());
    pixmap.save(fileName,"Bmp");
}

void plotpolar::addGraph()
{
     QString filenames=QFileDialog::getOpenFileName(this,tr("文件选择"),tr("/home"),"数据文件(*.txt *.dat)");
     int code=readDatas(filenames);
     if(code==0)
     {
         plot();
     }
     else if(code==-1)
     {
         QMessageBox::critical(this, "Warming", "Can't open "+filenames+" !", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
     }
     else if(code==-2)
     {
         QMessageBox::critical(this, "Warming", "Datas in "+filenames+" are wrong!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
     }
}

int plotpolar::readDatas(QString path)
{
    if(x.size()!=0) x.clear();
    if(y.size()!=0) y.clear();

    ifstream f(path.toStdString());
    int dot=0;
    int first=0;
    new_name="";
    for(int i=0;i<path.size();i++)
    {
        if(path[i]=='.')
        {
            for(unsigned j=i;j>0;j--)
            {
                if(path[j]=='/')
                {
                    first=j+1;
                    break;
                }
            }
            dot=i;
            break;
        }
    }
    for(int i=first;i<dot;i++)
    {
          new_name.append(path[i]);
    }

    if(!f)
  {
    return -1;//打不开文件
  }
    double a,b;
    while(f>>a&&f>>b)
   {
       x.push_back(a);
       y.push_back(b);
   }
    if(f.eof())
   {
       return 0;
   }
    else
   {
       return -2;//数据有误
   }
}

int plotpolar::addDatas(Matrix data)
{
    return 1;
}

void plotpolar::plot()
{
    double min_theata,max_theata,min_r,max_r;
    min_theata=max_theata=x[0];
    min_r=max_r=y[0];
    for(int i=0;i<x.size();i++)
    {
        if(x[i]>max_theata)
        {
            max_theata=x[i];
        }
        if(x[i]<min_theata)
        {
            min_theata=x[i];
        }
        if(y[i]>max_r)
        {
            max_r=y[i];
        }
        if(y[i]<min_r)
        {
            min_r=y[i];
        }
    }
    radialAxis->setRange(min_r,max_r);
    angularAxis->setRange(min_theata,max_theata);
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    QSplineSeries* line=new QSplineSeries;
    for(int i=0;i<x.size();i++)
    {
        line->append(x[i],y[i]);
    }

    line->attachAxis(radialAxis);
    line->attachAxis(angularAxis);

    for(int i=0;i<chart->series().size();i++)
    {
        chart->series()[i]->attachAxis(radialAxis);
        chart->series()[i]->attachAxis(angularAxis);
    }
    int f=0;
    for(unsigned i=0;i<graph_names.size();i++)
    {
        if(QString::compare(graph_names[i],new_name)==0)
        {
            new_name+=QString::number(f);
            f++;
            i=0;
        }
    }

    line->setName(new_name);
    chart->addSeries(line);
    graph_names.push_back(new_name);
    polar_view->setChart(chart);
    polar_view->setRenderHint(QPainter::Antialiasing);
    polar_view->show();
}

void plotpolar::clearWindow()
{
    chart->removeAllSeries();
    polar_view->setChart(chart);
    polar_view->show();
    graph_names.clear();
}

void plotpolar::closeEvent(QCloseEvent* event)
{
    emit closePolarWindow();
}
