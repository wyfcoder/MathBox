#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T09:13:55
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += charts
RC_ICONS = mathbox2.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MathBox 1.0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    matrix.cpp \
    number.cpp \
    mathi.cpp \
    mi.cpp \
    MianGauss.cpp \
    classexplor.cpp \
    compliedeals.cpp \
    buildhelper.cpp \
    randcount.cpp \
    parmtype.cpp \
    function.cpp \
    functionbuildhelper.cpp \
    c.cpp \
    functioncalculate.cpp \
    dealparams.cpp \
    functionprogram.cpp \
    allstatic.cpp \
    qcustomplot.cpp \
    titlesetting.cpp \
    xaxis.cpp \
    xaxislable.cpp \
    yaxis.cpp \
    yaxislable.cpp \
    curvesetting.cpp \
    axissetting.cpp \
    plot2dwidget.cpp \
    deletgraphs.cpp \
    timecountwidget.cpp \
    equationsolving.cpp \
    matrixbuilderhelper.cpp \
    stepsimpson.cpp \
    integrationsolving_simpson.cpp \
    integrationsolving_romberg.cpp \
    integrationguassfivepoint.cpp \
    matrixcheck.cpp \
    randmatrix.cpp \
    result.cpp \
    linearequationssolving.cpp \
    showhelpdoc.cpp \
    mainwindow.cpp \
    regressionunified.cpp \
    regressionplecrvefitting.cpp \
    regressionmultiple.cpp \
    linearequationssolving_iterationw.cpp \
    mucic.cpp \
    linearequationssolving_diagonal.cpp \
    project_Antennawire_ssa.cpp \
    project_Antennawire_oea.cpp \
    project_Antennawire_pa.cpp \
    project_Antennawire_tea.cpp \
    specialfunction_hermite.cpp \
    specialfunction_legendre.cpp \
    specialfunction_bezier.cpp \
    project_quantummechanics_odho.cpp \
    plotpolar.cpp \
    chartview_polar.cpp

HEADERS  += \
    matrix.h \
    number.h \
    mathi.h \
    MainGauss.h \
    mi.h \
    classexplor.h \
    compliedeals.h \
    buildhelper.h \
    randcount.h \
    parmtype.h \
    function.h \
    functionbuildhelper.h \
    c.h \
    functioncalculate.h \
    dealparams.h \
    functionprogram.h \
    allstatic.h \
    qcustomplot.h \
    titlesetting.h \
    xaxis.h \
    xaxislable.h \
    yaxis.h \
    yaxislable.h \
    curvesetting.h \
    axissetting.h \
    plot2dwidget.h \
    deletgraphs.h \
    timecountwidget.h \
    equationsolving.h \
    matrixbuilderhelper.h \
    stepsimpson.h \
    integrationsolving_simpson.h \
    integrationsolving_romberg.h \
    integrationguassfivepoint.h \
    matrixcheck.h \
    matrixfunction.h \
    randmatrix.h \
    result.h \
    linearequationssolving.h \
    showhelpdoc.h \
    mainwindow.h \
    regressionunified.h \
    regressionplecrvefitting.h \
    regressionmultiple.h \
    linearequationssolving_iterationw.h \
    mucic.h \
    linearequationssolving_diagonal.h \
    project_Antennawire_ssa.h \
    project_Antennawire_oea.h \
    project_Antennawire_pa.h \
    project_Antennawire_tea.h \
    specialfunction_hermite.h \
    specialfunction_legendre.h \
    specialfunction_bezier.h \
    project_quantummechanics_odho.h \
    plotpolar.h \
    chartview_polar.h

FORMS    += mainwindow.ui

DISTFILES += \
    mathbox2.ico

RESOURCES += \
    picture.qrc \
    file.qrc
