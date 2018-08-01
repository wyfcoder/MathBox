#include "classexplor.h"
#include<qheaderview.h>
#include<QVBoxLayout>

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

void ClassExplor::Change(vector<Matrix> matrixes)
{
    if(oldMatrix.size()==0)
    {
        for(unsigned i=0;i<matrixes.size();i++)
          {
             oldMatrix.push_back(matrixes[i]);
             addMatrixTableItem(matrixes[i]);
         }
    }
    else
    {
        if(matrixes.size()>oldMatrix.size())
        {
            oldMatrix.push_back(matrixes[matrixes.size()-1]);
            addMatrixTableItem(matrixes[matrixes.size()-1]);
        }
        else
        for(unsigned i=0;i<matrixes.size();i++)
        {
            if(!(matrixes[i]==oldMatrix[i]))
            {
                changeTableItem(matrixes[i],i);
                oldMatrix[i]=matrixes[i];
            }
        }
    }
}

void ClassExplor::addMatrixTableItem(Matrix m)
{
     classes one;
     one.className="Matrix";
     one.size=m.n*m.m;
     one.name=m.name;
     all_virtual.push_back(one);
     QTableWidgetItem *item0,*item1,*item2,*item3;
     table->setRowCount(table->rowCount()+1);
     int row=table->rowCount()-2;
     item0=new QTableWidgetItem;
     item1=new QTableWidgetItem;
     item2=new QTableWidgetItem;
     item3=new QTableWidgetItem;
     item0->setText("Matrix");
     item1->setText(m.name);
     int size=m.n*m.m;
     item2->setText(QString::number(size));
     table->setItem(row,0,item0);
     table->setItem(row,1,item1);
     table->setItem(row,2,item2);
     QString v;
     int sum=0;
     v.append("[");
        for(int i=0;i<m.m;i++)
      {
         for(int j=0;j<m.n;j++)
         {
             v.append(QString::number(m.arrays[i][j]));
              if(sum>15)
              {
                  v.append("...");
                  item3->setText(v);
                  table->setItem(row,3,item3);
                  return;
              }
             v.append(" ");
             sum++;
         }
         if(i!=m.m-1)
         v.append(";");
         else
         v.push_back("]");
         }
         item3->setText(v);
         table->setItem(row,3,item3);
}

void ClassExplor::changeTableItem(Matrix m, int row)
{
    QTableWidgetItem *item0,*item1,*item2,*item3;
    item0=new QTableWidgetItem;
    item1=new QTableWidgetItem;
    item2=new QTableWidgetItem;
    item3=new QTableWidgetItem;
    item0->setText("Matrix");
    item1->setText(m.name);
    int size=m.n*m.m;
    item2->setText(QString::number(size));
    table->setItem(row,0,item0);
    table->setItem(row,1,item1);
    table->setItem(row,2,item2);
    QString v;
    int sum=0;
    v.append("[");
        for(int i=0;i<m.m;i++)
     {
        for(int j=0;j<m.n;j++)
        {
            v.append(QString::number(m.arrays[i][j]));
             if(sum>15)
             {
                 v.append("...");
                 item3->setText(v);
                 table->setItem(row,3,item3);
                 return;
             }
            v.append(" ");
            sum++;
        }
        if(i!=m.m-1)
        v.append(";");
        else
        v.append("]");
        }
        item3->setText(v);
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
