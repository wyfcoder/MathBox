#include "classexplor.h"
#include<qheaderview.h>
#include<QVBoxLayout>
#include"function.h"
using namespace std;
ClassExplor::ClassExplor(QWidget *parent) : QWidget(parent)
{
    table=new QTableWidget(1,4);
    QStringList headerLable;
    headerLable<<"Type"<<"Name"<<"Size"<<"Values";
    table->setHorizontalHeaderLabels(headerLable);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout* box=new QVBoxLayout;
    box->addWidget(table);
    this->setLayout(box);
}



void  ClassExplor::addFunctiontableItem(Function f)
{
    classes one;
    one.className="Function";
    one.size=1;
    one.name=f.virtualName;
    all_virtual.push_back(one);
    QTableWidgetItem *item0,*item1,*item2,*item3;
    table->setRowCount(table->rowCount()+1);
    item0=new QTableWidgetItem;
    item1=new QTableWidgetItem;
    item2=new QTableWidgetItem;
    item3=new QTableWidgetItem;
    item0->setText("Function");
    item1->setText(f.virtualName);
    item2->setText(QString::number(f.function.size()));
    item3->setText(f.function);
    int row=table->rowCount()-2;
    table->setItem(row,0,item0);
    table->setItem(row,1,item1);
    table->setItem(row,2,item2);
    table->setItem(row,3,item3);
}

void ClassExplor::addMatrixtableItem(Matrix m)
{
    classes one;
    one.className="Matrix";
    one.size=m.m*m.n;
    one.name=m.name;
    all_virtual.push_back(one);
    QTableWidgetItem *item0,*item1,*item2,*item3;
    table->setRowCount(table->rowCount()+1);
    item0=new QTableWidgetItem;
    item1=new QTableWidgetItem;
    item2=new QTableWidgetItem;
    item3=new QTableWidgetItem;
    item0->setText("Matrix");
    item1->setText(m.name);
    item2->setText(QString::number(m.m*m.n));
    QString message="[";
    for(unsigned i=0;i<m.m;i++)
     {
        for(unsigned j=0;j<m.n;j++)
        {
            message.append(QString::number(m.arrays[i][j]));
            message.append(" ");
        }

        if(i!=m.m-1)
            message.append(";");
        else
            message.append("]");
        if(message.size()>100) break;
     }
    item3->setText(message);
    int row=table->rowCount()-2;
    table->setItem(row,0,item0);
    table->setItem(row,1,item1);
    table->setItem(row,2,item2);
    table->setItem(row,3,item3);
}


void ClassExplor::addNumberTableItem(Number n)
{
  classes one;
  one.className="Number";
  one.size=1;
  one.name=n.name;
  all_virtual.push_back(one);
  QTableWidgetItem *item0,*item1,*item2,*item3;
  table->setRowCount(table->rowCount()+1);
  item0=new QTableWidgetItem;
  item1=new QTableWidgetItem;
  item2=new QTableWidgetItem;
  item3=new QTableWidgetItem;
  item0->setText("Number");
  item1->setText(n.name);
  item2->setText(QString::number(1));
  item3->setText(QString::number(n.value));
  int row=table->rowCount()-2;
  table->setItem(row,0,item0);
  table->setItem(row,1,item1);
  table->setItem(row,2,item2);
  table->setItem(row,3,item3);
}

void ClassExplor::changeTableItem(Number n)
{
    for(unsigned i=0;i<all_virtual.size();i++)
    {
        if(all_virtual[i].name==n.name)
        {
            QTableWidgetItem *item0,*item1,*item2,*item3;
            item0=new QTableWidgetItem;
            item1=new QTableWidgetItem;
            item2=new QTableWidgetItem;
            item3=new QTableWidgetItem;
            item0->setText("Number");
            item1->setText(n.name);
            item2->setText(QString::number(1));
            item3->setText(QString::number(n.value));
            table->setItem(i,0,item0);
            table->setItem(i,1,item1);
            table->setItem(i,2,item2);
            table->setItem(i,3,item3);
        }
    }
}

void ClassExplor::changeTableItem(Function f)
{
    for(unsigned i=0;i<all_virtual.size();i++)
    {
        if(f.virtualName==all_virtual[i].name)
        {
            QTableWidgetItem *item0,*item1,*item2,*item3;
            item0=new QTableWidgetItem;
            item1=new QTableWidgetItem;
            item2=new QTableWidgetItem;
            item3=new QTableWidgetItem;
            item0->setText("Function");
            item1->setText(f.virtualName);
            item2->setText(QString::number(f.function.size()));
            item3->setText(f.function);
            table->setItem(i,0,item0);
            table->setItem(i,1,item1);
            table->setItem(i,2,item2);
            table->setItem(i,3,item3);
        }
    }
}

void ClassExplor::changeTableItem(Matrix m)
{
    for(unsigned i=0;i<all_virtual.size();i++)
    {
        if(m.name==all_virtual[i].name)
        {
            QTableWidgetItem *item0,*item1,*item2,*item3;
            item0=new QTableWidgetItem;
            item1=new QTableWidgetItem;
            item2=new QTableWidgetItem;
            item3=new QTableWidgetItem;
            QString message="[";
            for(unsigned i=0;i<m.m;i++)
             {
                for(unsigned j=0;j<m.n;j++)
                {
                    message.append(QString::number(m.arrays[i][j]));
                    message.append(" ");
                }
                if(i!=m.m-1)
                    message.append(";");
                else
                    message.append("]");
             }
            item0->setText("Matrix");
            item1->setText(m.name);
            item2->setText(QString::number(m.m*m.n));
            item3->setText(message);
            table->setItem(i,0,item0);
            table->setItem(i,1,item1);
            table->setItem(i,2,item2);
            table->setItem(i,3,item3);
        }
    }
}

void ClassExplor::delet(QString name)
{
    for(unsigned i=0;i<all_virtual.size();i++)
    {
        if(name==all_virtual[i].name)
        {//有待修改
            table->removeRow(i);
            vector<classes>::iterator it=all_virtual.begin();
            for(unsigned a=0;a<i;a++)
                it++;
            all_virtual.erase(it);
        }
    }
}
