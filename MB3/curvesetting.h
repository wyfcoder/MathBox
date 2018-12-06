#ifndef CURVESETTING_H
#define CURVESETTING_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "QFrame"
#include <QPalette>
#include "widget.h"
#include "allstatic.h"
#include "qcustomplot.h"
class Allstatic;
class CurveSetting : public QWidget
{
    Q_OBJECT
public:
    explicit CurveSetting(QWidget *parent = 0);
private slots:
    void ShowOk();
    void ShowLineStyle(int);
    void ShowLineConnect(int);
    void ShowLineWidth();
    void ShowLineColor();
    void ShowCancel();
public:
    QLabel *LineStyleLabel;
    QLabel *LineConnectLabel;
    QLabel *LineWidthLabel;
    QLabel *LineColorLabel;
    QComboBox *LineStyleComboBox;
    QComboBox *LineConnectComboBox;
    QComboBox *LineWidthComboBox;

    QFrame *LineColorFrame;
    QPushButton *LineColorBtn;
    QPushButton *LineSettingOk;
    QPushButton *LineSettingCancel;

    QGridLayout *LineSettingLayout;
    QHBoxLayout *LineSettingBtnLayout;
    QVBoxLayout *mainLayout;
signals:
    void sendData(QColor, float,Qt::PenStyle,QCPScatterStyle);

public:
    Qt::PenStyle style;
    QColor color=Qt::black;
    QCPScatterStyle connectStyle;
    float penWidth;
};

#endif // CURVESETTING_H
