#include "plot2dwidget.h"
#include"deletgraphs.h"
#include<QFileDialog>
#include<QMessageBox>
#include<iostream>
#include<fstream>
using namespace std;
Plot2DWidget::Plot2DWidget(QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("MathBox Plot"));//创建动作，菜单，工具栏
    createActions();
    createMenus();
    setMinimumSize(690,550);
    setWindowIcon(QIcon(":/picture/plot.jpg"));
    sizeOfLines=0;
    customPlot=new QCustomPlot(this);

    //设置坐标轴风格
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectLegend| QCP::iSelectPlottables);


// 为坐标轴添加标签
   customPlot->xAxis->setLabel("x");

   customPlot->yAxis->setLabel("y");

   customPlot->xAxis->setTickLabelFont(QFont("sans",10));

   customPlot->yAxis->setTickLabelFont(QFont("sans",10));

// 设置坐标轴的范围，以看到所有数据
   customPlot->axisRect()->setupFullAxesBox();

   customPlot->replot();

//设置标题

   customPlot->plotLayout()->insertRow(0);

   title=new QCPTextElement(customPlot,"Graph",QFont("仿宋_GB2312",18));

   customPlot->plotLayout()->addElement(0,0,title);

   customPlot->plotLayout()->setRowSpacing(10);


   customPlot->plotLayout()->setAutoMargins(QCP::MarginSide::msAll);


   //设置Legend

   customPlot->legend->setVisible(true);

   QFont legendFont=font();

   legendFont.setPointSize(10);

   customPlot->legend->setFont(legendFont);

   customPlot->legend->setSelectedFont(legendFont);

   customPlot->legend->setSelectableParts(QCPLegend::spItems);


   mainLayout=new QVBoxLayout;

   mainLayout->addWidget(customPlot);

   mainLayout->setMargin(40);

   this->setLayout(mainLayout);


   //Connect区

        connect(customPlot,SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)),this,
        SLOT(graphDoubleClicked()));

        connect(title,SIGNAL(doubleClicked(QMouseEvent*)),this,SLOT(titleDoubleClicked()));

        connect(customPlot,SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
        this,SLOT(axisDoubleClicked(QCPAxis*,QCPAxis::SelectablePart)));

        connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
        this, SLOT(legendDoubleClicked(QCPLegend*,QCPAbstractLegendItem*)));

        connect(customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePress()));

        connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));


}

Plot2DWidget::~Plot2DWidget()
{
;
}
void Plot2DWidget::setPenStyle(QColor color,float penWidth,Qt::PenStyle style,QCPScatterStyle connectStyle)
{
customPlot->selectedGraphs().first()->setPen(QPen(color,penWidth,style));
customPlot->selectedGraphs().first()->setScatterStyle(connectStyle);
customPlot->replot();
}

void Plot2DWidget::graphDoubleClicked()
{
CurveSetting *view=new CurveSetting;
connect(view,SIGNAL(sendData(QColor, float,Qt::PenStyle,QCPScatterStyle)),this,
       SLOT(setPenStyle(QColor, float,Qt::PenStyle,QCPScatterStyle)));
view->show();
}

void Plot2DWidget::titleDoubleClicked()
{
    TitleSetting *view=new TitleSetting;
    connect(view,SIGNAL(sendTitle(QColor,QFont,QString)),this,
            SLOT(setTitle(QColor,QFont,QString)));
    view->show();

}

void Plot2DWidget::axisDoubleClicked(QCPAxis *axis,QCPAxis::SelectablePart part)
{
if(part==QCPAxis::spAxisLabel)
{
    bool ok;
    QString newLabel=QInputDialog::getText(this,tr("Plot Axis Label"),
                                           tr("Input the New Plot Label:"),QLineEdit::Normal,axis->label(),&ok);
    if(ok)
    {
        axis->setLabel(newLabel);
        customPlot->replot();
    }
}
else if(part==QCPAxis::spAxis||part==QCPAxis::spTickLabels)
{
    AxisSetting *view=new AxisSetting;
    view->show();
    connect(view,SIGNAL(sendAxis(QColor,QFont,QColor,QFont,double,double,
                                 QColor,QFont,double,double,QColor,QFont)),
            this,SLOT(setAxis(QColor,QFont,QColor,QFont,double,double,
                               QColor,QFont,double,double,QColor,QFont)));

}
}

void Plot2DWidget::legendDoubleClicked(QCPLegend *legend, QCPAbstractLegendItem *item)
{
// Rename a graph by double clicking on its legend item

    Q_UNUSED(legend)
if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
{
QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
bool ok;
QString newName = QInputDialog::getText(this,tr("Plot Legend"),tr("New graph name:"), QLineEdit::Normal, plItem->plottable()->name(), &ok);
if (ok)
{
  plItem->plottable()->setName(newName);
  customPlot->replot();
}
}
flashNames();
}

void Plot2DWidget::selectionChanged()
{

// make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
  customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
{
customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
}
// make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
  customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
{
customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
}

for (int i=0; i<customPlot->graphCount(); ++i)
{
QCPGraph *graph = customPlot->graph(i);
QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
if (item->selected() || graph->selected())
{
  item->setSelected(true);
  graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
}
}

}

void Plot2DWidget::mousePress()
{
// if an axis is selected, only allow the direction of that axis to be dragged
// if no axis is selected, both directions may be dragged

if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
else
customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void Plot2DWidget::mouseWheel()
{
// if an axis is selected, only allow the direction of that axis to be zoomed
// if no axis is selected, both directions may be zoomed

if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
else
customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}


void Plot2DWidget::setAxis(QColor xLabelColor,QFont xLabelFont,QColor yLabelColor,QFont yLabelFont,
                 double xLeftRange,double xRightRange,QColor xTickColor,QFont xTickFont,
                 double yLeftRange,double yRightRange,QColor yTickColor,QFont yTickFont)
{
setxAxisLable(xLabelColor,xLabelFont);
setyAxisLable(yLabelColor,yLabelFont);
setxAxis(xLeftRange,xRightRange,xTickColor,xTickFont);
setyAxis(yLeftRange,yRightRange,yTickColor,yTickFont);
customPlot->replot();
}


void Plot2DWidget::setxAxisLable(QColor color,QFont font)
{
customPlot->xAxis->setLabelColor(color);
customPlot->xAxis->setLabelFont(font);
}
void Plot2DWidget::setyAxisLable(QColor color,QFont font)
{
customPlot->yAxis->setLabelColor(color);
customPlot->yAxis->setLabelFont(font);
}
void Plot2DWidget::setxAxis(double leftRange,double rightRange,QColor color,QFont font)
{
customPlot->xAxis->setRange(leftRange,rightRange);
customPlot->xAxis->setTickLabelColor(color);
customPlot->xAxis->setTickLabelFont(font);
}

void Plot2DWidget::setyAxis(double leftRange,double rightRange,QColor color,QFont font)
{

    customPlot->yAxis->setRange(leftRange,rightRange);

    customPlot->yAxis->setTickLabelColor(color);

    customPlot->yAxis->setTickLabelFont(font);
}

void Plot2DWidget::setTitle(QColor color,QFont font,QString titleText)
{

    title->setTextColor(color);

    title->setFont(font);

    title->setText(titleText);

    customPlot->replot();
}


//设置窗体
void Plot2DWidget::createActions()
{
addAGraph=new QAction(tr("Add a Graph"));
connect(addAGraph,SIGNAL(triggered(bool)),this,SLOT(AddAGraph()));
addGraphs=new QAction(tr("Add Graphs"));
connect(addGraphs,SIGNAL(triggered(bool)),this,SLOT(AddGraphs()));
deleteAGraph=new QAction(tr("Delete Graph"));
connect(deleteAGraph,SIGNAL(triggered(bool)),this,SLOT(DeleteGraph()));
deleteAllGraphs=new QAction(tr("Delete All Graphs"));
connect(deleteAllGraphs,SIGNAL(triggered(bool)),this,SLOT(DeleteAllGraphs()));
closePlot=new QAction(tr("Close MathBox Plot"));
connect(closePlot,SIGNAL(triggered(bool)),this,SLOT(ClosePlot()));

savePng=new QAction(tr("Save as Png"));
connect(savePng,SIGNAL(triggered(bool)),this,SLOT(SavePlotPng()));
saveJpg=new QAction(tr("Save as Jpg"));
connect(saveJpg,SIGNAL(triggered(bool)),this,SLOT(SavePlotJpg()));
saveBmp=new QAction(tr("Save as Bmp"));
connect(saveBmp,SIGNAL(triggered(bool)),this,SLOT(SavePlotBmp()));

aboutMathBoxPlot=new QAction(tr("About MathBox Plot"));

//connect(aboutMathBoxPlot,SIGNAL(triggered(bool)),this,SLOT(About()));
closePlot->setIcon(QIcon(":/picture/circle.png"));
addAGraph->setIcon(QIcon(":/picture/circle.png"));
addGraphs->setIcon(QIcon(":/picture/circle.png"));
deleteAGraph->setIcon(QIcon(":/picture/circle.png"));
deleteAllGraphs->setIcon(QIcon(":/picture/circle.png"));
saveBmp->setIcon(QIcon(":/picture/circle.png"));
saveJpg->setIcon(QIcon(":/picture/circle.png"));
savePng->setIcon(QIcon(":/picture/circle.png"));

aboutMathBoxPlot->setIcon(QIcon(":/picture/circle.png"));
}

void Plot2DWidget::createMenus()
{
fileMenu=new QMenu(tr("File"));

fileMenu->addAction(addAGraph);
fileMenu->addAction(addGraphs);
fileMenu->addSeparator();
fileMenu->addAction(deleteAGraph);
fileMenu->addAction(deleteAllGraphs);
fileMenu->addSeparator();
fileMenu->addAction(closePlot);

saveMenu=new QMenu(tr("Save"));
saveMenu->addAction(savePng);
saveMenu->addSeparator();
saveMenu->addAction(saveJpg);
saveMenu->addSeparator();
saveMenu->addAction(saveBmp);

helpMenu=new QMenu(tr("Help"));
helpMenu->addAction(aboutMathBoxPlot);

menuBar->addMenu(fileMenu);
menuBar->addMenu(saveMenu);
menuBar->addMenu(helpMenu);
}

void Plot2DWidget::SavePlotPng()
{
QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Png");
customPlot->setBackground(Qt::white);
customPlot->savePng(fileName);
}

void Plot2DWidget::SavePlotJpg()
{
QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Jpg");
customPlot->setBackground(Qt::white);
customPlot->savePng(fileName);
}

void Plot2DWidget::SavePlotBmp()
{
QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Bmp");
customPlot->setBackground(Qt::white);
customPlot->savePng(fileName);
}


//------------------------------------------------------------------
void Plot2DWidget::AddAGraph()
{
   AddGraphs();
}

void Plot2DWidget::AddGraphs()
{
    QStringList filenames=QFileDialog::getOpenFileNames(this,tr("文件选择"),tr("/home"),"数据文件(*.txt *.dat)");

    for(int i=0;i<filenames.size();i++)
    {
        plotGraph(filenames[i]);
    }

}

void Plot2DWidget::plotGraph(QString path)
{
    int code=readDatas(path);
    if(code==0)
    {
        getFileName(path);
        plot();
    }
    else if(code==-1)
    {
        QMessageBox::critical(this, "Warming", "Can't open "+path+" !", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(code==-2)
    {
        QMessageBox::critical(this, "Warming", "Datas in "+path+" are wrong!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}


int Plot2DWidget::readDatas(QString path)
{
    if(x.size()!=0) x.clear();
    if(y.size()!=0) y.clear();

    ifstream f(path.toStdString());

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

void Plot2DWidget::getFileName(QString path)
{
    int dot=0;
    while(path[dot]!='.')
    {
        dot++;
    }
    QString end= "";
    int a=dot+1;
    while(a<path.size())
    {
        end.append(path[a]);
        a++;
    }
    a=dot-1;
    while(path[a]!='/')
    {
        a--;
    }
    a++;
    QString start="";
    while(a<=dot)
    {
        start.append(path[a]);
        a++;
    }
    constPlotname=start+end;
}

void Plot2DWidget::plot()
{
    bool isUsed=false;
    for(int i=0;i<graphNames.size();i++)
    {
        if(constPlotname==graphNames[i])
        {
            RecieveSignalDelet(constPlotname);
            isUsed=true;
            break;
        }
    }
    customPlot->addGraph();
    customPlot->graph(sizeOfLines)->setData(x, y);
    customPlot->graph(sizeOfLines)->setName(constPlotname);
    graphNames.push_back(constPlotname);
    sizeOfLines++;
}

void Plot2DWidget::flashNames()
{
    graphNames.clear();
    for(int i=0;i<sizeOfLines;i++)
    graphNames.push_back(customPlot->graph(i)->name());
}
//---------------------------------------------------------------------
void Plot2DWidget::DeleteAllGraphs()
{
 customPlot->clearGraphs();
 customPlot->replot();
 if(graphNames.size()!=0)graphNames.clear();
 sizeOfLines=0;
}


void Plot2DWidget::DeleteGraph()
{
    DeletGraphs* d=new DeletGraphs();
    connect(d,SIGNAL(sendData(QString)),this,SLOT(RecieveSignalDelet(QString)));
    if(graphNames.size()>0)
   {
        d->setName(graphNames);
        d->show();
   }
    else
    {
        QMessageBox::critical(this, "Warming", "Graphs are all deleted!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}
void Plot2DWidget::RecieveSignalDelet(QString name)
{
    for(int i=0;i<sizeOfLines;i++)
    {
        if(customPlot->graph(i)->name()==name)
        {
            customPlot->removeGraph(customPlot->graph(i));
            customPlot->replot();
            sizeOfLines--;
            flashNames();
        }
    }
}
void Plot2DWidget::ClosePlot()
{
   this->close();
}
//---------------------------------------------------------------------控制指令
void Plot2DWidget::closeEvent(QCloseEvent* event)
{
    emit closeWindow();
}
//----------------------------------------------------------------------外围接口
void Plot2DWidget::clearGraph()
{
    DeleteAllGraphs();
}

void Plot2DWidget::plotGraph(Function f,double min,double max)
{
    if(x.size()!=0) x.clear();
    if(y.size()!=0) y.clear();
    double step=0;
    if(fabs(max-min)/0.01>5000000)
    {
        step=(max-min)/5000000.0;
    }
    else
    {
        step=0.01;
    }
    while(min<max)
    {
        vector<double> v;
        v.push_back(min);
        x.push_back(min);
        y.push_back(f.calculate(v));
        min+=step;
    }
    constPlotname=f.virtualName;
    plot();
}

void Plot2DWidget::plorGraph2(Matrix m)
{
    if(x.size()!=0) x.clear();
    if(y.size()!=0) y.clear();
    unsigned i=0;
    while(i<m.m)
    {
        x.push_back(m.arrays[i][0]);
        y.push_back(m.arrays[i][1]);
        i++;
    }
    constPlotname=m.name;
    plot();
}
