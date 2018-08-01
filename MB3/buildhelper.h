#ifndef BUILDHELPER_H
#define BUILDHELPER_H

#include<QString>
#include<QVector>
#include<vector>
#include"number.h"
#include"matrix.h"
using namespace std;
class buildhelper
{
public:
    buildhelper();
    int getClassMode(QString message);//获得类的种类
    void inputText(QString text);
private:
    QVector<QString> className;
    QVector<QString> commands;
    vector<QString> functionName;

    //----------------------------------------------
    QString text;
    double value;
    int position;


};

#endif // BUILDHELPER_H
