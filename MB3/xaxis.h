#ifndef XAXIS_H
#define XAXIS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include "allstatic.h"
class Allstatic;

class xAxis : public QWidget
{
    Q_OBJECT
public:
    explicit xAxis(QWidget *parent = 0);
public:
    QLabel *xAxisFromLabel;
    QLabel *xAxisToLabel;
    QLineEdit *xAxisFromEdit;
    QLineEdit *xAxisToEdit;
    QLabel *xAxisColorLabel;
    QLabel *xAxisFontLabel;
    QFrame *xAxisColorFrame;
    QLineEdit *xAxisFontEdit;
    QLineEdit *xAxisSizeEdit;
    QLabel *xAxisSizeLabel;
    QPushButton *xAxisColorBtn;
    QPushButton *xAxisFontBtn;
    QFont font;
    QColor color;
    int size;
    double fromEdit;
    double toEdit;

signals:

public slots:
    void ShowColorDialog();
    void ShowFontDialog();
    void getFromEdit();
    void getToEdit();

};

#endif // XAXIS_H
