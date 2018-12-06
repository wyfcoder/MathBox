#ifndef TIMECOUNTWIDGET_H
#define TIMECOUNTWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include<qcustomplot.h>
#include<QVector>
using namespace std;
class TimeCountWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeCountWidget(QWidget *parent = nullptr);
    void addData(double time);//添加时间的端口，传入运行时间即可绘制折线图.wyf
signals:

public slots:

private:

    QCustomPlot *customPlot;
    int position;
    QVector<double> x;
    QVector<double> y;

    void initWindow();//初始化窗口，布局和窗口大小等等。wyf
};

#endif // TIMECOUNTWIDGET_H
