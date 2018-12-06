#ifndef XAXISLABLE_H
#define XAXISLABLE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFontDialog>
#include <QPalette>
#include <QLineEdit>
#include "allstatic.h"
#include "widget.h"
class Allstatic;
class xAxisLable : public QWidget
{
    Q_OBJECT
public:
    explicit xAxisLable(QWidget *parent = 0);

signals:

public:
    QLabel *xAxisLabelSizeLabel;
    QLineEdit *xAxisLabelSizeEdit;
    QLabel *xAxisLabelColorLabel;
    QLabel *xAxisLabelNameLabel;
    QLineEdit *xAxisLabelNameEdit;
    QFrame *xAxisLabelColorFrame;
    QPushButton *xAxisLabelColorBtn;
    QLabel *xAxisLabelFontLabel;
    QLineEdit *xAxisLabelFontEdit;
    QPushButton *xAxisLabelFontBtn;
    QGridLayout *xAxisLabelLayout;
    QVBoxLayout *mainLayout;
    QFont font;
    QColor color;
    int size;
public slots:
    void ShowFontDialog();
    void ShowColorDialog();

};

#endif // XAXISLABLE_H
