#ifndef CLASSEXPLOR_H
#define CLASSEXPLOR_H
//可视化变量的表
#include <QWidget>
#include<vector>
#include"matrix.h"
#include<QTableWidget>
#include"number.h"
using namespace std;
class ClassExplor : public QWidget
{
    Q_OBJECT
public:
    explicit ClassExplor(QWidget *parent = nullptr);
    void Change(vector<Matrix> matrixes);
    void addNumberTableItem(Number n);
    void changeTableItem(Number n);
    class classes
    {
    public:
        QString className;
        QString name;
        int size;
    };
private:
    vector<Matrix> oldMatrix;

    vector<classes> all_virtual;

    QTableWidget* table;
    void addMatrixTableItem(Matrix m);
    void changeTableItem(Matrix m,int position);
    int changPosition;
};

#endif // CLASSEXPLOR_H
