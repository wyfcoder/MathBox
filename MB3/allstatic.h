#ifndef ALLSTATIC_H
#define ALLSTATIC_H
#include <QPalette>
#include "qcustomplot.h"
#include "titlesetting.h"
#include "axissetting.h"
#include "widget.h"
#include <QFont>
class Allstatic
{
public:
    Allstatic();
    static int indexStyle;
    static QColor indexColor;
    static int indexConnect;
    static QFont titleFont;
    static QColor titleColor;
    static QColor axisColor;
    static QColor xAxisLabelColor;
    static QFont xAxisLabelFont;
    static QString xAxisLabelFontSize;
    static QString xAxisLabelFontString;
    static QColor yAxisLabelColor;
    static QFont yAxisLabelFont;
    static QString yAxisLabelFontSize;
    static QString yAxisLabelFontString;
    static QColor xAxisColor;
    static QFont xAxisFont;
    static QString xAxisFontSize;
    static QString xAxisFontString;
    static double xAxisFromEdit;
    static double xAxisToEdit;
    static QColor yAxisColor;
    static QFont yAxisFont;
    static QString yAxisFontSize;
    static QString yAxisFontString;
    static double yAxisFromEdit;
    static double yAxisToEdit;
    static QString titleText;
    static QString titleFontSize;
    static QString titleFontString;
};

#endif // ALLSTATIC_H
