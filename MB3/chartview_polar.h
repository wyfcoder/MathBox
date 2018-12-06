#ifndef CHARTVIEW_POLAR_H
#define CHARTVIEW_POLAR_H
#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>

QT_CHARTS_USE_NAMESPACE
class chartview_polar: public QChartView
{
public:
    chartview_polar(QWidget *parent = 0);
    void flash(QChart* newchart);
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void switchChartType();
};
#endif // CHARTVIEW_POLAR_H
