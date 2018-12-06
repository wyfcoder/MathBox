#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QMenu>
#include <QMenuBar>
#include "qcustomplot.h"
#include "curvesetting.h"
#include "titlesetting.h"
#include "axissetting.h"
#include "QPen"
#include "QPushButton"
#include "QVBoxLayout"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
     void createActions();
     void createMenus();
private slots:
     void graphDoubleClicked();
     void setPenStyle(QColor, float,Qt::PenStyle,QCPScatterStyle );
     void titleDoubleClicked();
     void axisDoubleClicked(QCPAxis *axis,QCPAxis::SelectablePart part);
     void legendDoubleClicked(QCPLegend *legend, QCPAbstractLegendItem *item);
     void selectionChanged();
     void mousePress();
     void mouseWheel();
     void setTitle(QColor,QFont,QString);
     void setxAxisLable(QColor,QFont);
     void setyAxisLable(QColor,QFont);
     void setxAxis(double,double,QColor,QFont);
     void setyAxis(double,double,QColor,QFont);
     void setAxis(QColor,QFont,QColor,QFont,double,double,
                  QColor,QFont,double,double,QColor,QFont);
     void AddAGraph();
     //void AddGraphs();
     void DeleteAGraph();
     void DeleteAllGraphs();
     void ClosePlot();
     void SavePlotPng();
     void SavePlotJpg();
     void SavePlotBmp();
     //void About();
private:
    QMenu *fileMenu;
    QMenu *saveMenu;
    QMenu *helpMenu;
    QAction *addAGraph;
    QAction *addGraphs;
    QAction *deleteAGraph;
    QAction *deleteAllGraphs;
    QAction *closePlot;
    QAction *savePng;
    QAction *saveJpg;
    QAction *saveBmp;
    QAction *aboutMathBoxPlot;
    QMenuBar *menuBar=new QMenuBar(this);
public:
    Ui::Widget *ui;
    QCPTextElement *title;
    QPushButton *pushButton;
    QVBoxLayout *mainLayout;
};

#endif // WIDGET_H
