#include "yaxis.h"

yAxis::yAxis(QWidget *parent) : QWidget(parent)
{
    yAxisFromLabel=new QLabel(tr("From:"));
    yAxisToLabel=new QLabel(tr("To:"));
    yAxisFromEdit=new QLineEdit;
    yAxisToEdit=new QLineEdit;
    yAxisColorLabel=new QLabel(tr("Color:"));
    yAxisFontLabel=new QLabel(tr("Font:"));
    yAxisColorFrame=new QFrame;
    yAxisColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    yAxisColorFrame->setAutoFillBackground(true);
    color=Allstatic::xAxisColor;
    yAxisColorFrame->setPalette(color);
    yAxisFontEdit=new QLineEdit;
    yAxisFontEdit->setText(Allstatic::yAxisFontString);
    yAxisSizeEdit=new QLineEdit;
    yAxisSizeEdit->setText(Allstatic::yAxisFontSize);
    yAxisSizeLabel=new QLabel(tr("Size:"));
    yAxisColorBtn=new QPushButton(tr("Change"));
    yAxisFontBtn=new QPushButton(tr("Change"));

    QGridLayout *yAxisGridLayout1=new QGridLayout;
    yAxisGridLayout1->addWidget(yAxisFromLabel,0,0);
    yAxisGridLayout1->addWidget(yAxisFromEdit,0,1);
    yAxisGridLayout1->addWidget(yAxisToLabel,1,0);
    yAxisGridLayout1->addWidget(yAxisToEdit,1,1);

    QGridLayout *yAxisGridLayout2=new QGridLayout;
    yAxisGridLayout2->addWidget(yAxisColorLabel,0,0);
    yAxisGridLayout2->addWidget(yAxisColorFrame,0,1);
    yAxisGridLayout2->addWidget(yAxisColorBtn,0,2);
    yAxisGridLayout2->addWidget(yAxisFontLabel,1,0);
    yAxisGridLayout2->addWidget(yAxisFontEdit,1,1);
    yAxisGridLayout2->addWidget(yAxisFontBtn,1,2);
    yAxisGridLayout2->addWidget(yAxisSizeLabel,2,0);
    yAxisGridLayout2->addWidget(yAxisSizeEdit,2,1);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(yAxisGridLayout1);
    mainLayout->addLayout(yAxisGridLayout2);
    mainLayout->setSpacing(20);
    mainLayout->setMargin(40);
    this->setLayout(mainLayout);
    connect(yAxisFontBtn,SIGNAL(clicked(bool)),this,SLOT(ShowFontDialog()));
    connect(yAxisColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorDialog()));
    connect(yAxisFromEdit,SIGNAL(textChanged(QString)),this,SLOT(getFromEdit()));
    connect(yAxisToEdit,SIGNAL(textChanged(QString)),this,SLOT(getToEdit()));

}

void yAxis::ShowFontDialog()
{
    bool ok;
    font=QFontDialog::getFont(&ok);
    if(ok)
    {
        QString fontName=font.family();
        size=font.pointSize();
        QString fontSize=QString::number(size);
        yAxisFontEdit->setText(fontName);
        yAxisSizeEdit->setText(fontSize);
        Allstatic::yAxisFontString=fontName;
        Allstatic::yAxisFontSize=fontSize;
    }
    Allstatic::xAxisFont=font;
}
void yAxis::ShowColorDialog()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    yAxisColorFrame->setPalette(QPalette(color));
    Allstatic::yAxisColor=color;
}

void yAxis::getFromEdit()
{

   fromEdit=yAxisFromEdit->text().toDouble();
   Allstatic:: yAxisFromEdit=fromEdit;
}

void yAxis::getToEdit()
{
    toEdit=yAxisToEdit->text().toDouble();
    Allstatic:: yAxisToEdit=toEdit;
}

