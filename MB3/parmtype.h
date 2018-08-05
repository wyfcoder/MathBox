#ifndef PARMTYPE_H
#define PARMTYPE_H
#include<QString>
// 1-> 数字类 2->矩阵类 3->函数类 4->整数 5->double
class ParmType
{
public:
    ParmType();
    int type;
    int position;
    bool isTrue;
    double number;
    int n;
    QString name;
};

#endif // PARMTYPE_H
