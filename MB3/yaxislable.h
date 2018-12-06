#ifndef YAXISLABLE_H
#define YAXISLABLE_H

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

class yAxisLable : public QWidget
{
    Q_OBJECT
public:
    explicit yAxisLable(QWidget *parent = 0);
public slots:
    void ShowFontDialog();
    void ShowColorDialog();
public:
    QLabel *yAxisLabelSizeLabel;
    QLineEdit *yAxisLabelSizeEdit;
    QLabel *yAxisLabelColorLabel;
    QLabel *yAxisLabelNameLabel;
    QLineEdit *yAxisLabelNameEdit;
    QFrame *yAxisLabelColorFrame;
    QPushButton *yAxisLabelColorBtn;
    QLabel *yAxisLabelFontLabel;
    QLineEdit *yAxisLabelFontEdit;
    QPushButton *yAxisLabelFontBtn;
    QGridLayout *yAxisLabelLayout;
    QVBoxLayout *mainLayout;
    QFont font;
    QColor color;
    int size;


public slots:
};

#endif // YAXISLABLE_H
