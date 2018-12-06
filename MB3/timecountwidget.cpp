#include "timecountwidget.h"

TimeCountWidget::TimeCountWidget(QWidget *parent) : QWidget(parent)
{
    initWindow();
    x.push_back(0);
    y.push_back(0);
    position=1;
}

void TimeCountWidget::initWindow()
{
    setWindowTitle("Time's Analysis");
    customPlot=new QCustomPlot();
    //设置坐标轴风格.
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    // 为坐标轴添加标签.

    customPlot->xAxis->setLabel("Command's ID");

    customPlot->xAxis->setRange(0,10);


    customPlot->yAxis->setLabel("Time/ms");//可以修改，根据得到的时间设置单位。wyf

    customPlot->yAxis->setRange(0,50);

    customPlot->xAxis->setTickLabelFont(QFont("sans",10));

    customPlot->yAxis->setTickLabelFont(QFont("sans",10));

    QVBoxLayout* mainLayout=new QVBoxLayout;


    mainLayout->addWidget(customPlot);

    mainLayout->setMargin(10);

    this->setLayout(mainLayout);

    setMinimumSize(300,200);
}

void TimeCountWidget::addData(double time)
{
    x.push_back(position);
    y.push_back(time);
    if(position==1)
    {
        customPlot->addGraph();
    }
    customPlot->graph(0)->setData(x,y);
    customPlot->replot();
    position++;
}
