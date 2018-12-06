#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H
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


class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

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
    QCustomPlot*  customPlot;
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
    QCPTextElement *title;
    QPushButton *pushButton;
    QVBoxLayout *mainLayout;
};

#endif // PLOTWIDGET_H
