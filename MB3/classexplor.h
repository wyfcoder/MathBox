#ifndef CLASSEXPLOR_H
#define CLASSEXPLOR_H
//可视化变量的表
#include <QWidget>
#include<vector>
#include"matrix.h"
#include<QTableWidget>
#include"number.h"
#include"function.h"
using namespace std;
class ClassExplor : public QWidget
{
    Q_OBJECT
public:
    explicit ClassExplor(QWidget *parent = nullptr);
    void Change(vector<Matrix> matrixes);
    void addNumberTableItem(Number n);
    void addFunctiontableItem(Function f);
    void addMatrixtableItem(Matrix m);
    void changeTableItem(Number n);
    void changeTableItem(Function f);
    void changeTableItem(Matrix m);
    void delet(QString name);
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
    int changPosition;
};

#endif // CLASSEXPLOR_H
