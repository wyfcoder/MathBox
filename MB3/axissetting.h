#ifndef AXISSETTING_H
#define AXISSETTING_H

#include <QObject>
#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include "xaxis.h"
#include "yaxis.h"
#include "xaxislable.h"
#include "yaxislable.h"
class xAxis;
class xAxisLable;
class yAxis;
class yAxisLable;
class AxisSetting : public QFrame
{
    Q_OBJECT
public:
    AxisSetting(QWidget *parent=0);
    QStackedWidget *stack;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;
    xAxis *xaxis;
    yAxis *yaxis;
    xAxisLable *xaxislable;
    yAxisLable *yaxislable;
    QSplitter *splitter;
    QListWidget *list;
    QHBoxLayout *mainLayout;
signals:
   sendAxis(QColor,QFont,QColor,QFont,double,double,QColor,QFont,double,double,QColor,QFont);
public slots:
   void ShowOk();
   void ShowCancel();
};

#endif // AXISSETTING_H
