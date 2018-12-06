#include "yaxislable.h"

yAxisLable::yAxisLable(QWidget *parent) : QWidget(parent)
{
    yAxisLabelColorLabel=new QLabel(tr("Color:"));
    yAxisLabelColorFrame=new QFrame;
    yAxisLabelColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    yAxisLabelColorFrame->setAutoFillBackground(true);
    yAxisLabelColorBtn=new QPushButton(tr("Change"));
    color=Allstatic::xAxisLabelColor;
    yAxisLabelColorFrame->setPalette(color);

    yAxisLabelFontLabel=new QLabel(tr("Font:"));
    yAxisLabelFontBtn=new QPushButton(tr("Change"));
    yAxisLabelFontEdit=new QLineEdit;
    yAxisLabelFontEdit->setText(Allstatic::yAxisLabelFontString);

    yAxisLabelSizeLabel=new QLabel(tr("Size:"));
    yAxisLabelSizeEdit=new QLineEdit;
    yAxisLabelSizeEdit->setText(Allstatic::yAxisLabelFontSize);

    yAxisLabelLayout=new QGridLayout;
    yAxisLabelLayout->addWidget(yAxisLabelColorLabel,1,0);
    yAxisLabelLayout->addWidget(yAxisLabelColorFrame,1,1);
    yAxisLabelLayout->addWidget(yAxisLabelColorBtn,1,2);
    yAxisLabelLayout->addWidget(yAxisLabelFontLabel,2,0);
    yAxisLabelLayout->addWidget(yAxisLabelFontEdit,2,1);
    yAxisLabelLayout->addWidget(yAxisLabelFontBtn,2,2);
    yAxisLabelLayout->addWidget(yAxisLabelSizeLabel,3,0);
    yAxisLabelLayout->addWidget(yAxisLabelSizeEdit,3,1);



    mainLayout=new QVBoxLayout;
    mainLayout->addLayout(yAxisLabelLayout);
    mainLayout->setSpacing(20);
    mainLayout->setMargin(40);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(mainLayout);

    connect(yAxisLabelFontBtn,SIGNAL(clicked(bool)),this,SLOT(ShowFontDialog()));
    connect(yAxisLabelColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorDialog()));

}
void yAxisLable::ShowFontDialog()
{
    bool ok;
    font=QFontDialog::getFont(&ok);
    if(ok)
    {
        QString fontName=font.family();
        size=font.pointSize();
        QString fontSize=QString::number(size);
        yAxisLabelFontEdit->setText(fontName);
        yAxisLabelSizeEdit->setText(fontSize);
        Allstatic::yAxisLabelFontString=fontName;
        Allstatic::yAxisLabelFontSize=fontSize;
    }
    Allstatic::yAxisLabelFont=font;
}
void yAxisLable::ShowColorDialog()
{
    color=QColorDialog::getColor(static_cast<int>(Qt::blue));
    yAxisLabelColorFrame->setPalette(QPalette(color));
    Allstatic::yAxisLabelColor=color;
}
