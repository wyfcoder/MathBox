#include "xaxis.h"

xAxis::xAxis(QWidget *parent) : QWidget(parent)
{
    xAxisFromLabel=new QLabel(tr("From:"));
    xAxisToLabel=new QLabel(tr("To:"));
    xAxisFromEdit=new QLineEdit;
    xAxisToEdit=new QLineEdit;
    xAxisColorLabel=new QLabel(tr("Color:"));
    xAxisFontLabel=new QLabel(tr("Font:"));
    xAxisColorFrame=new QFrame;
    xAxisColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    xAxisColorFrame->setAutoFillBackground(true);
    color=Allstatic::xAxisColor;
    xAxisColorFrame->setPalette(color);
    xAxisFontEdit=new QLineEdit;
    xAxisFontEdit->setText(Allstatic::xAxisFontString);
    xAxisSizeEdit=new QLineEdit;
    xAxisSizeEdit->setText(Allstatic::xAxisFontSize);
    xAxisSizeLabel=new QLabel(tr("Size:"));
    xAxisColorBtn=new QPushButton(tr("Change"));
    xAxisFontBtn=new QPushButton(tr("Change"));

    QGridLayout *xAxisGridLayout1=new QGridLayout;
    xAxisGridLayout1->addWidget(xAxisFromLabel,0,0);
    xAxisGridLayout1->addWidget(xAxisFromEdit,0,1);
    xAxisGridLayout1->addWidget(xAxisToLabel,1,0);
    xAxisGridLayout1->addWidget(xAxisToEdit,1,1);

    QGridLayout *xAxisGridLayout2=new QGridLayout;
    xAxisGridLayout2->addWidget(xAxisColorLabel,0,0);
    xAxisGridLayout2->addWidget(xAxisColorFrame,0,1);
    xAxisGridLayout2->addWidget(xAxisColorBtn,0,2);
    xAxisGridLayout2->addWidget(xAxisFontLabel,1,0);
    xAxisGridLayout2->addWidget(xAxisFontEdit,1,1);
    xAxisGridLayout2->addWidget(xAxisFontBtn,1,2);
    xAxisGridLayout2->addWidget(xAxisSizeLabel,2,0);
    xAxisGridLayout2->addWidget(xAxisSizeEdit,2,1);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(xAxisGridLayout1);
    mainLayout->addLayout(xAxisGridLayout2);
    mainLayout->setSpacing(20);
    mainLayout->setMargin(40);
    this->setLayout(mainLayout);
    connect(xAxisFontBtn,SIGNAL(clicked(bool)),this,SLOT(ShowFontDialog()));
    connect(xAxisColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorDialog()));
    connect(xAxisFromEdit,SIGNAL(textChanged(QString)),this,SLOT(getFromEdit()));
    connect(xAxisToEdit,SIGNAL(textChanged(QString)),this,SLOT(getToEdit()));

}

void xAxis::ShowFontDialog()
{
    bool ok;
    font=QFontDialog::getFont(&ok);
    if(ok)
    {
        QString fontName=font.family();
        size=font.pointSize();
        QString fontSize=QString::number(size);
        xAxisFontEdit->setText(fontName);
        xAxisSizeEdit->setText(fontSize);
        Allstatic::xAxisFontString=fontName;
        Allstatic::xAxisFontSize=fontSize;
    }
    Allstatic::xAxisFont=font;
}
void xAxis::ShowColorDialog()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    xAxisColorFrame->setPalette(QPalette(color));
    Allstatic::xAxisColor=color;
}

void xAxis::getFromEdit()
{

   fromEdit=xAxisFromEdit->text().toDouble();
   Allstatic:: xAxisFromEdit=fromEdit;
}

void xAxis::getToEdit()
{
    toEdit=xAxisToEdit->text().toDouble();
    Allstatic:: xAxisToEdit=toEdit;
}
