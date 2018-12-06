#include "curvesetting.h"
#include "QPen"
#include "widget.h"
#include <QColorDialog>

CurveSetting::CurveSetting(QWidget *parent) : QWidget(parent)
{
    this->resize(400,350);
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setWindowFlags(windowFlags()&~Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Curve Setting");


    LineStyleLabel=new QLabel(tr("Stytle:"));
    LineStyleComboBox=new QComboBox;
    LineStyleLabel->setAlignment(Qt::AlignCenter);
    LineStyleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    LineStyleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    LineStyleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    LineStyleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    LineStyleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    LineStyleComboBox->addItem(tr("CustomDashLine"),static_cast<int>(Qt::CustomDashLine));
    LineStyleComboBox->setCurrentIndex(Allstatic::indexStyle);
    style =Qt::PenStyle(LineStyleComboBox->itemData(Allstatic::indexStyle,Qt::UserRole).toInt());
    connect(LineStyleComboBox,SIGNAL(activated(int)),this,SLOT(ShowLineStyle(int)));

    LineConnectLabel=new QLabel(tr("Connect:"));
    LineConnectLabel->setAlignment(Qt::AlignCenter);
    LineConnectComboBox=new QComboBox;
    LineConnectComboBox->addItem(tr("None￼"),static_cast<int>(QCPScatterStyle::ssNone));
    LineConnectComboBox->addItem(tr("Dote￼"),static_cast<int>(QCPScatterStyle::ssDot));
    LineConnectComboBox->addItem(tr("-×-￼"),static_cast<int>(QCPScatterStyle::ssCross));
    LineConnectComboBox->addItem(tr("-＋-￼"),static_cast<int>(QCPScatterStyle::ssPlus));
    LineConnectComboBox->addItem(tr("-○-￼"),static_cast<int>(QCPScatterStyle::ssCircle));
    LineConnectComboBox->addItem(tr("-●-￼"),static_cast<int>(QCPScatterStyle::ssDisc));
    LineConnectComboBox->addItem(tr("-□-￼"),static_cast<int>(QCPScatterStyle::ssSquare));
    LineConnectComboBox->addItem(tr("-◇-￼"),static_cast<int>(QCPScatterStyle::ssDiamond));
    LineConnectComboBox->addItem(tr("-*-￼"),static_cast<int>(QCPScatterStyle::ssStar));
    LineConnectComboBox->addItem(tr("-△-￼"),static_cast<int>(QCPScatterStyle::ssTriangle));
    LineConnectComboBox->addItem(tr("-▽-￼"),static_cast<int>(QCPScatterStyle::ssTriangleInverted));
    LineConnectComboBox->addItem(tr("-☒-￼"),static_cast<int>(QCPScatterStyle::ssCrossSquare));
    LineConnectComboBox->addItem(tr("-田-￼"),static_cast<int>(QCPScatterStyle::ssPlusSquare));
    LineConnectComboBox->addItem(tr("CrossCircle￼"),static_cast<int>(QCPScatterStyle::ssCrossCircle));
    LineConnectComboBox->addItem(tr("PlusCircle￼"),static_cast<int>(QCPScatterStyle::ssPlusCircle));
    LineConnectComboBox->addItem(tr("Peace￼"),static_cast<int>(QCPScatterStyle::ssPeace));
    LineConnectComboBox->setCurrentIndex(Allstatic::indexConnect);
    connect(LineConnectComboBox,SIGNAL(activated(int)),this,SLOT(ShowLineConnect(int)));

    LineWidthLabel=new QLabel(tr("Width:"));
    LineWidthComboBox=new QComboBox;
    LineWidthLabel->setAlignment(Qt::AlignCenter);
    LineWidthComboBox->addItem(tr("0.5"));
    LineWidthComboBox->addItem(tr("1"));
    LineWidthComboBox->addItem(tr("2"));
    LineWidthComboBox->addItem(tr("3"));
    LineWidthComboBox->addItem(tr("4"));
    LineWidthComboBox->addItem(tr("5"));
    LineWidthComboBox->setCurrentIndex(1);
    penWidth=LineWidthComboBox->currentText().toFloat();
    connect(LineWidthComboBox,SIGNAL(activated(int)),this,SLOT(ShowLineWidth()));

    LineColorLabel=new QLabel(tr("Color:"));
    LineColorBtn=new QPushButton(tr("Change"));
    LineColorFrame=new QFrame;
    LineColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    LineColorFrame->setAutoFillBackground(true);
    color=Allstatic::indexColor;
    LineColorFrame->setPalette(color);
    LineColorLabel->setAlignment(Qt::AlignCenter);
    connect(LineColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowLineColor()));

    LineSettingOk=new QPushButton(tr("OK"));
    connect(LineSettingOk,SIGNAL(clicked(bool)),this,SLOT(ShowOk()));

    LineSettingCancel=new QPushButton(tr("Cancel"));
    connect(LineSettingCancel,SIGNAL(clicked(bool)),this,SLOT(ShowCancel()));

    LineSettingLayout=new QGridLayout;
    LineSettingLayout->addWidget(LineStyleLabel,0,0);
    LineSettingLayout->addWidget(LineStyleComboBox,0,1);
    LineSettingLayout->addWidget(LineConnectLabel,1,0);
    LineSettingLayout->addWidget(LineConnectComboBox,1,1);
    LineSettingLayout->addWidget(LineWidthLabel,2,0);
    LineSettingLayout->addWidget(LineWidthComboBox,2,1);
    LineSettingLayout->addWidget(LineColorLabel,3,0);
    LineSettingLayout->addWidget(LineColorBtn,3,2);
    LineSettingLayout->addWidget(LineColorFrame,3,1);

    LineSettingBtnLayout=new QHBoxLayout;
    LineSettingBtnLayout->addStretch(2);
    LineSettingBtnLayout->addWidget(LineSettingOk);
    LineSettingBtnLayout->addWidget(LineSettingCancel);
    LineSettingBtnLayout->addStretch(1);

    mainLayout=new QVBoxLayout;
    mainLayout->addLayout(LineSettingLayout);
    mainLayout->addLayout(LineSettingBtnLayout);
    mainLayout->setSpacing(30);
    mainLayout->setMargin(40);
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->setLayout(mainLayout);

}

void CurveSetting::ShowLineStyle(int styleValue)
{
     style =Qt::PenStyle(LineStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());
     Allstatic::indexStyle=LineStyleComboBox->currentIndex();
}

void CurveSetting::ShowLineWidth()
{
    penWidth=LineWidthComboBox->currentText().toFloat();

}
void CurveSetting::ShowOk()
{
    this->close();
    emit sendData(color,penWidth,style,connectStyle);
}
void CurveSetting::ShowLineColor()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    LineColorFrame->setPalette(QPalette(color));
    Allstatic::indexColor=color;
}
void CurveSetting::ShowCancel()
{
    this->close();
}
void CurveSetting::ShowLineConnect(int connectValue)
{
    connectStyle =QCPScatterStyle::ScatterShape(LineConnectComboBox->itemData(connectValue,Qt::UserRole).toInt());
    Allstatic::indexConnect=LineConnectComboBox->currentIndex();
}


