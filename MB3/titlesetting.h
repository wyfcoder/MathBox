#ifndef TITLESETTING_H
#define TITLESETTING_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QFontDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "QFrame"
#include <QPalette>
#include "allstatic.h"
class Allstatic;
class TitleSetting : public QWidget
{
    Q_OBJECT

public:
    explicit TitleSetting(QWidget *parent = 0);

public:
    QLabel *TitleTextLabel;
    QLineEdit *TitleTextEdit;
    QLabel *TitleColorLabel;
    QLabel *TitleFontLabel;
    QFrame *TitleColorFrame;
    QPushButton *TitleFontBtn;
    QPushButton *TitleColorBtn;
    QLineEdit *TitleFontEdit;
    QLabel *TitleFontSizeLabel;
    QLineEdit *TitleFontSizeEdit;
    QPushButton *TitleSettingOk;
    QPushButton *TitleSettingCancel;
    QGridLayout *TitleSettingLayout1;
    QGridLayout *TitleSettingLayout2;
    QHBoxLayout *TitleSettingBtnLayout;
    QVBoxLayout *mainLayout;
public:
    QFont font;
    QColor color;
    int size;
    QString titleTextEdit;
signals:
    void sendTitle(QColor,QFont,QString);
public slots:
    void getTitleText();
    void ShowFontDialog();
    void ShowColorDialog();
    void ShowOk();
    void ShowCancel();

};

#endif // TITLESETTING_H
