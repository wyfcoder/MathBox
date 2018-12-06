#include "titlesetting.h"

TitleSetting::TitleSetting(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setWindowFlags(windowFlags()&~Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Title Setting");

    TitleTextLabel=new QLabel(tr("Title:"));
    TitleTextEdit=new QLineEdit;
    TitleTextEdit->setText(Allstatic::titleText);
    TitleTextEdit->selectAll();

    TitleColorLabel=new QLabel(tr("Color:"));
    TitleColorFrame=new QFrame;
    TitleColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    TitleColorFrame->setAutoFillBackground(true);
    color=Allstatic::titleColor;
    TitleColorFrame->setPalette(color);
    TitleColorBtn=new QPushButton(tr("Change"));

    TitleFontLabel=new QLabel(tr("Font:"));
    TitleFontBtn=new QPushButton(tr("Change"));
    TitleFontEdit=new QLineEdit;
    TitleFontEdit->setText(Allstatic::titleFontString);

    TitleFontSizeLabel=new QLabel(tr("Size;"));
    TitleFontSizeEdit=new QLineEdit;
    TitleFontSizeEdit->setText(Allstatic::titleFontSize);

    TitleSettingOk=new QPushButton(tr("Ok"));
    TitleSettingCancel=new QPushButton(tr("Cancel"));

    TitleSettingLayout1=new QGridLayout;
    TitleSettingLayout1->addWidget(TitleTextLabel,0,0);
    TitleSettingLayout1->addWidget(TitleTextEdit,0,1);

    TitleSettingLayout2=new QGridLayout;
    TitleSettingLayout2->addWidget(TitleColorLabel,0,0);
    TitleSettingLayout2->addWidget(TitleColorFrame,0,1);
    TitleSettingLayout2->addWidget(TitleColorBtn,0,2);
    TitleSettingLayout2->addWidget(TitleFontLabel,1,0);
    TitleSettingLayout2->addWidget(TitleFontEdit,1,1);
    TitleSettingLayout2->addWidget(TitleFontBtn,1,2);
    TitleSettingLayout2->addWidget(TitleFontSizeLabel,2,0);
    TitleSettingLayout2->addWidget(TitleFontSizeEdit,2,1);

    TitleSettingBtnLayout=new QHBoxLayout;
    TitleSettingBtnLayout->addStretch(1);
    TitleSettingBtnLayout->addWidget(TitleSettingOk);
    TitleSettingBtnLayout->addWidget(TitleSettingCancel);


    mainLayout=new QVBoxLayout;
    mainLayout->addLayout(TitleSettingLayout1);
    mainLayout->addLayout(TitleSettingLayout2);
    mainLayout->addLayout(TitleSettingBtnLayout);
    mainLayout->setSpacing(20);
    mainLayout->setMargin(40);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(mainLayout);
    font=Allstatic::titleFont;
    connect(TitleTextEdit,SIGNAL(textChanged(QString)),this,SLOT(getTitleText()));
    connect(TitleFontBtn,SIGNAL(clicked(bool)),this,SLOT(ShowFontDialog()));
    connect(TitleColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorDialog()));
    connect(TitleSettingOk,SIGNAL(clicked(bool)),this,SLOT(ShowOk()));
    connect(TitleSettingCancel,SIGNAL(clicked(bool)),this,SLOT(ShowOk()));

}

void TitleSetting::ShowFontDialog()
{
    bool ok;
    font=QFontDialog::getFont(&ok);
    if(ok)
    {
        QString fontName=font.family();
        size=font.pointSize();
        QString fontSize=QString::number(size);
        TitleFontEdit->setText(fontName);
        TitleFontSizeEdit->setText(fontSize);
        Allstatic::titleFontString=fontName;
        Allstatic::titleFontSize=fontSize;
    }
    Allstatic::titleFont=font;
}
void TitleSetting::ShowColorDialog()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    TitleColorFrame->setPalette(QPalette(color));
    Allstatic::titleColor=color;
}

void TitleSetting::ShowOk()
{
   this->close();
   emit sendTitle(Allstatic::titleColor,Allstatic::titleFont,Allstatic::titleText);
}
void TitleSetting::ShowCancel()
{
    this->close();
}

void TitleSetting::getTitleText()
{
   titleTextEdit=TitleTextEdit->text();
   Allstatic::titleText=titleTextEdit;
}
