#ifndef PLOTPOLAR_H
#define PLOTPOLAR_H

#include <QWidget>
#include<QMenu>
#include<QMenuBar>
#include<vector>
#include<QSplineSeries>
#include<QValueAxis>
#include"matrix.h"
#include"chartview_polar.h"
using namespace std;
class plotpolar : public QWidget
{
    Q_OBJECT
public:
    explicit plotpolar(QWidget *parent = nullptr);
    int      addDatas(Matrix data);
    void     plot(vector<double> x,vector<double> y,QString name);
signals:
    void closePolarWindow();
private slots:
    void SavePlotPng();
    void SavePlotJpg();
    void SavePlotBmp();
    void addGraph();
    void clearWindow();

protected:void closeEvent(QCloseEvent * event);

private:
         //绘图类
         chartview_polar* polar_view;
         QPolarChart*     chart;
         QValueAxis*      angularAxis;
         QValueAxis*      radialAxis;

         void buildWindow();
         void buildPainter();
         void creatActions();
         void creatMenus();

         QMenu *baseOperations;
         QMenu* saveMenu;
         QAction *AddGraph;
         QAction *DeleteGraph;
         QAction *help;
         QAction *savePng;
         QAction *saveJpg;
         QAction *saveBmp;
         QMenuBar *menuBar;

         //管理类
         QVector<double> x;
         QVector<double> y;
         QString         new_name;
         vector<QString> graph_names;
         int  readDatas(QString path);
         void plot();
};

#endif // PLOTPOLAR_H
