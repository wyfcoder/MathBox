#ifndef PLOT2DWIDGET_H
#define PLOT2DWIDGET_H

#include <QWidget>
#include <QPalette>
#include<vector>
#include <QMenu>
#include <QMenuBar>
#include<function.h>
#include<QCloseEvent>
#include "qcustomplot.h"
#include "curvesetting.h"
#include "titlesetting.h"
#include "axissetting.h"
#include "QPen"
#include "QPushButton"
#include "QVBoxLayout"
#include "matrix.h"
class Plot2DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit
       Plot2DWidget(QWidget *parent = nullptr);
      ~Plot2DWidget();
       void plotGraph(Function f,double min,double max);
       void plorGraph2(Matrix m);
       void clearGraph();
signals:
       void sendData(QString);
       void closeWindow();
private:
     QVector<double> x;
     QVector<double> y;
     QString constPlotname;
     void createActions();
     void createMenus();
     //------------------------ plot function
     void plotGraph(QString path);
     int  readDatas(QString path);
     void getFileName(QString path);
     void plot();
     void flashNames();
     int sizeOfLines;
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
     void AddGraphs();
     void DeleteGraph();
     void RecieveSignalDelet(QString name);
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
    QCustomPlot *customPlot;
    //------------------------------------保存操作
    vector<QString> graphNames;
private:
    QCPTextElement *title;
    QPushButton *pushButton;
    QVBoxLayout *mainLayout;
protected:void closeEvent(QCloseEvent * event);
};

#endif // PLOT2DWIDGET_H
