#include "xaxislable.h"

xAxisLable::xAxisLable(QWidget *parent) : QWidget(parent)
{

    xAxisLabelColorLabel=new QLabel(tr("Color:"));
    xAxisLabelColorFrame=new QFrame;
    xAxisLabelColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    xAxisLabelColorFrame->setAutoFillBackground(true);
    xAxisLabelColorBtn=new QPushButton(tr("Change"));
    color=Allstatic::xAxisLabelColor;
    xAxisLabelColorFrame->setPalette(color);

    xAxisLabelFontLabel=new QLabel(tr("Font:"));
    xAxisLabelFontBtn=new QPushButton(tr("Change"));
    xAxisLabelFontEdit=new QLineEdit;
    xAxisLabelFontEdit->setText(Allstatic::xAxisLabelFontString);

    xAxisLabelSizeLabel=new QLabel(tr("Size:"));
    xAxisLabelSizeEdit=new QLineEdit;
    xAxisLabelSizeEdit->setText(Allstatic::xAxisLabelFontSize);

    xAxisLabelLayout=new QGridLayout;
    xAxisLabelLayout->addWidget(xAxisLabelColorLabel,1,0);
    xAxisLabelLayout->addWidget(xAxisLabelColorFrame,1,1);
    xAxisLabelLayout->addWidget(xAxisLabelColorBtn,1,2);
    xAxisLabelLayout->addWidget(xAxisLabelFontLabel,2,0);
    xAxisLabelLayout->addWidget(xAxisLabelFontEdit,2,1);
    xAxisLabelLayout->addWidget(xAxisLabelFontBtn,2,2);
    xAxisLabelLayout->addWidget(xAxisLabelSizeLabel,3,0);
    xAxisLabelLayout->addWidget(xAxisLabelSizeEdit,3,1);

    mainLayout=new QVBoxLayout;
    mainLayout->addLayout(xAxisLabelLayout);
    mainLayout->setSpacing(20);
    mainLayout->setMargin(40);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(mainLayout);

    connect(xAxisLabelFontBtn,SIGNAL(clicked(bool)),this,SLOT(ShowFontDialog()));
    connect(xAxisLabelColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorDialog()));
}

void xAxisLable::ShowFontDialog()
{
    bool ok;
    font=QFontDialog::getFont(&ok);
    if(ok)
    {
        QString fontName=font.family();
        size=font.pointSize();
        QString fontSize=QString::number(size);
        xAxisLabelFontEdit->setText(fontName);
        xAxisLabelSizeEdit->setText(fontSize);
        Allstatic::xAxisLabelFontString=fontName;
        Allstatic::xAxisLabelFontSize=fontSize;
    }
    Allstatic::xAxisLabelFont=font;
}
void xAxisLable::ShowColorDialog()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    xAxisLabelColorFrame->setPalette(QPalette(color));
    Allstatic::xAxisLabelColor=color;
}
