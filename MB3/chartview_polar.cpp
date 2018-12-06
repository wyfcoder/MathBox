#include "chartview_polar.h"
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>
using namespace std;
QT_CHARTS_USE_NAMESPACE

chartview_polar::chartview_polar(QWidget *parent)
    :QChartView(parent)
{

}

void chartview_polar::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-1.0, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(1.0, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 1.0);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -1.0);
        break;
    case Qt::Key_Space:
        //switchChartType();
        break;
    default:
        break;
    }
}

void chartview_polar::switchChartType()
{
    QChart *newChart;
    QChart *oldChart = chart();

    if (oldChart->chartType() == QChart::ChartTypeCartesian)
        newChart = new QPolarChart();
    else
        newChart = new QChart();

    // Move series and axes from old chart to new one
    const QList<QAbstractSeries *> seriesList = oldChart->series();
    const QList<QAbstractAxis *> axisList = oldChart->axes();
    QList<QPair<qreal, qreal> > axisRanges;

    for (QAbstractAxis *axis : axisList)
    {
        QValueAxis *valueAxis = static_cast<QValueAxis *>(axis);
        axisRanges.append(QPair<qreal, qreal>(valueAxis->min(), valueAxis->max()));
    }

    for (QAbstractSeries *series : seriesList)
        oldChart->removeSeries(series);

    for (QAbstractAxis *axis : axisList)
    {
        oldChart->removeAxis(axis);
        newChart->addAxis(axis, axis->alignment());
    }

    for (QAbstractSeries *series : seriesList) {
        newChart->addSeries(series);
        for (QAbstractAxis *axis : axisList)
            series->attachAxis(axis);
    }

    int count = 0;
    for (QAbstractAxis *axis : axisList)
    {
        axis->setRange(axisRanges[count].first, axisRanges[count].second);
        count++;
    }

    newChart->setTitle(oldChart->title());
    setChart(newChart);
    delete oldChart;
}

void chartview_polar::flash(QChart* newchart)
{
    QChart *oldChart = chart();
    QChart *newOne=newchart;
    oldChart->removeAllSeries();
    setChart(newOne);
    delete oldChart;
}
