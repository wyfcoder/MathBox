#include "axissetting.h"

AxisSetting::AxisSetting(QWidget *parent):QFrame(parent)
{
    this->setWindowTitle("Axis Setting");
    stack=new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel|QFrame::Raised);
    xaxis=new xAxis();
    yaxis=new yAxis();
    xaxislable=new xAxisLable();
    yaxislable=new yAxisLable();
    stack->addWidget(xaxis);
    stack->addWidget(xaxislable);
    stack->addWidget(yaxis);
    stack->addWidget(yaxislable);
    OkBtn=new QPushButton(tr("Ok"));
    CancelBtn=new QPushButton(tr("Cancel"));

    splitter=new QSplitter(Qt::Horizontal,0);
    splitter->setOpaqueResize(true);
    list=new QListWidget(splitter);
    list->insertItem(0,tr("xAxis"));
    list->insertItem(2,tr("yAxis"));
    list->insertItem(1,tr("xAxisLable"));
    list->insertItem(3,tr("yAxisLable"));
    list->sizeAdjustPolicy();

    QHBoxLayout *BtnLayout=new QHBoxLayout;
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(OkBtn);
    BtnLayout->addWidget(CancelBtn);
    QVBoxLayout *RightLayout=new QVBoxLayout;
    RightLayout->setMargin(10);
    RightLayout->setSpacing(10);
    RightLayout->addWidget(stack);
    RightLayout->addLayout(BtnLayout);

    mainLayout=new QHBoxLayout;
    mainLayout->addWidget(list);
    mainLayout->addLayout(RightLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
    this->setLayout(mainLayout);


    connect(OkBtn,SIGNAL(clicked(bool)),this,SLOT(ShowOk()));
    connect(CancelBtn,SIGNAL(clicked(bool)),this,SLOT(ShowCancel()));
}

void AxisSetting::ShowOk()
{
   this->close();
   emit sendAxis(Allstatic::xAxisLabelColor,Allstatic::xAxisLabelFont,
                 Allstatic::yAxisLabelColor,Allstatic::yAxisLabelFont,
                 Allstatic::xAxisFromEdit,Allstatic::xAxisToEdit,
                 Allstatic::xAxisColor,Allstatic::xAxisFont,
                 Allstatic::yAxisFromEdit,Allstatic::yAxisToEdit,
                 Allstatic::yAxisColor,Allstatic::yAxisFont);
}
void AxisSetting::ShowCancel()
{
    this->close();
}
