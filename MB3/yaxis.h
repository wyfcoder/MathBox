#ifndef YAXIS_H
#define YAXIS_H

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
class yAxis : public QWidget
{
    Q_OBJECT
public:
    explicit yAxis(QWidget *parent = 0);
public:
    QLabel *yAxisFromLabel;
    QLabel *yAxisToLabel;
    QLineEdit *yAxisFromEdit;
    QLineEdit *yAxisToEdit;
    QLabel *yAxisColorLabel;
    QLabel *yAxisFontLabel;
    QFrame *yAxisColorFrame;
    QLineEdit *yAxisFontEdit;
    QLineEdit *yAxisSizeEdit;
    QLabel *yAxisSizeLabel;
    QPushButton *yAxisColorBtn;
    QPushButton *yAxisFontBtn;
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

#endif // YAXIS_H
