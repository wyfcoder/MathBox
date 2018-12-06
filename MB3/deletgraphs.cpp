#include "deletgraphs.h"
#include<QCheckBox>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMessageBox>
using namespace std;
DeletGraphs::DeletGraphs(QWidget *parent) : QWidget(parent)
{

}

void DeletGraphs::init()
{
    setMinimumWidth(300);
    setWindowTitle("Delet Graph");
    setFont(QFont("sans",10));
}


void DeletGraphs::deletButoonClick()
{
    QList<QAbstractButton*> buttons=group->buttons();
    for(int i=0;i<buttons.size();i++)
    {
        if(buttons[i]->isChecked())
        {
            selectNames.push_back(allNames[i]);
        }
    }
    if(selectNames.size()==0)
    {
         QMessageBox::critical(this, "Warming", "No graph is selected !", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else
    {
        for(unsigned i=0;i<selectNames.size();i++)
        emit sendData(selectNames[i]);
        exit();
    }
}

void DeletGraphs::setName(vector<QString> names)
{
    group=new QButtonGroup(this);
    QVBoxLayout* layout=new QVBoxLayout();
    QLabel* t=new QLabel();
    t->setText("Select graph to delete");
    layout->addWidget(t);
    allNames=names;
    for(unsigned i=0;i<names.size();i++)
    {
        QCheckBox* box=new QCheckBox();
        box->setText(names[i]);
        layout->addWidget(box);
        group->addButton(box,i);
    }
    group->setExclusive(false);
    QHBoxLayout* hLayout=new QHBoxLayout();
    deletButton=new QPushButton();
    exitButton=new QPushButton();

    deletButton->setText("Delete");
    exitButton->setText("Cancel");

    exitButton->connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(exit()));
    deletButton->connect(deletButton,SIGNAL(clicked(bool)),this,SLOT(deletButoonClick()));

    hLayout->addWidget(deletButton);
    hLayout->addWidget(exitButton);
    layout->addLayout(hLayout);
    this->setLayout(layout);
    init();
}

void DeletGraphs::exit()
{
    this->close();
}


