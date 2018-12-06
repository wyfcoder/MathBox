#include "widget.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QInputDialog>
#include"qcustomplot.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

    //设置窗体
    setWindowTitle(tr("MathBox Plot"));
    //创建动作，菜单，工具栏
    createActions();
    createMenus();

    //设置坐标轴风格
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectLegend| QCP::iSelectPlottables);

    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // 添加数据曲线（一个图像可以有多个数据曲线）
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

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
    title=new QCPTextElement(customPlot,"A Graph of A Function",QFont("仿宋_GB2312",18));
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

Widget::~Widget()
{
   ;
}
void Widget::setPenStyle(QColor color,float penWidth,Qt::PenStyle style,QCPScatterStyle connectStyle)
{
    customPlot->selectedGraphs().first()->setPen(QPen(color,penWidth,style));
    customPlot->selectedGraphs().first()->setScatterStyle(connectStyle);
    customPlot->replot();
}

void Widget::graphDoubleClicked()
{
   CurveSetting *view=new CurveSetting;
   connect(view,SIGNAL(sendData(QColor, float,Qt::PenStyle,QCPScatterStyle)),this,
           SLOT(setPenStyle(QColor, float,Qt::PenStyle,QCPScatterStyle)));
   view->show();
}

void Widget::titleDoubleClicked()
{
        TitleSetting *view=new TitleSetting;
        connect(view,SIGNAL(sendTitle(QColor,QFont,QString)),this,
                SLOT(setTitle(QColor,QFont,QString)));
        view->show();

}

void Widget::axisDoubleClicked(QCPAxis *axis,QCPAxis::SelectablePart part)
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

void Widget::legendDoubleClicked(QCPLegend *legend, QCPAbstractLegendItem *item)
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
}

void Widget::selectionChanged()
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

void Widget::mousePress()
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

void Widget::mouseWheel()
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


void Widget::setAxis(QColor xLabelColor,QFont xLabelFont,QColor yLabelColor,QFont yLabelFont,
                     double xLeftRange,double xRightRange,QColor xTickColor,QFont xTickFont,
                     double yLeftRange,double yRightRange,QColor yTickColor,QFont yTickFont)
{
    setxAxisLable(xLabelColor,xLabelFont);
    setyAxisLable(yLabelColor,yLabelFont);
    setxAxis(xLeftRange,xRightRange,xTickColor,xTickFont);
    setyAxis(yLeftRange,yRightRange,yTickColor,yTickFont);
    customPlot->replot();
}


void Widget::setxAxisLable(QColor color,QFont font)
{
    customPlot->xAxis->setLabelColor(color);
    customPlot->xAxis->setLabelFont(font);
}
void Widget::setyAxisLable(QColor color,QFont font)
{
    customPlot->yAxis->setLabelColor(color);
    customPlot->yAxis->setLabelFont(font);
}
void Widget::setxAxis(double leftRange,double rightRange,QColor color,QFont font)
{
    customPlot->xAxis->setRange(leftRange,rightRange);
    customPlot->xAxis->setTickLabelColor(color);
    customPlot->xAxis->setTickLabelFont(font);
}

void Widget::setyAxis(double leftRange,double rightRange,QColor color,QFont font)
{
    customPlot->yAxis->setRange(leftRange,rightRange);
    customPlot->yAxis->setTickLabelColor(color);
    customPlot->yAxis->setTickLabelFont(font);
}

void Widget::setTitle(QColor color,QFont font,QString titleText)
{
   title->setTextColor(color);
   title->setFont(font);
   title->setText(titleText);
   customPlot->replot();
}


//设置窗体
void Widget::createActions()
{
    addAGraph=new QAction(tr("Add a Graph"));
    connect(addAGraph,SIGNAL(triggered(bool)),this,SLOT(AddAGraph()));
    addGraphs=new QAction(tr("Add Graphs"));
    //connect(addGraphs,SIGNAL(triggered(bool)),this,SLOT(AddGraphs()));
    deleteAGraph=new QAction(tr("Delete a Graph"));
    connect(deleteAGraph,SIGNAL(triggered(bool)),this,SLOT(DeleteAGraph()));
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
}
void Widget::createMenus()
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
void Widget::SavePlotPng()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Png");
    customPlot->setBackground(Qt::white);
    customPlot->savePng(fileName);
}

void Widget::SavePlotJpg()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Jpg");
    customPlot->setBackground(Qt::white);
    customPlot->savePng(fileName);
}

void Widget::SavePlotBmp()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.Bmp");
    customPlot->setBackground(Qt::white);
    customPlot->savePng(fileName);
}

void Widget::AddAGraph()
{
  int n = 101;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = i/50.0 - 1;
    y[i] = x[i]*x[i]*x[i];
  }
  customPlot->addGraph();
  customPlot->graph()->setName(QString("Graph %1").arg(customPlot->graphCount()));
  customPlot->graph()->setData(x, y);
  customPlot->replot();
}
void Widget::DeleteAllGraphs()
{
    customPlot->clearGraphs();
    customPlot->replot();
}
void Widget::DeleteAGraph()
{
    if (customPlot->selectedGraphs().size() > 0)
    {
      customPlot->removeGraph(customPlot->selectedGraphs().first());
      customPlot->replot();
    }
}
void Widget::ClosePlot()
{
    this->close();
}
