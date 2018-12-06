#ifndef SPECIALFUNCTION_HERMITE_H
#define SPECIALFUNCTION_HERMITE_H

#include"matrix.h"
#include<vector>
//提供返回函数的服务，用户指定下厄米多项式的阶数后，返回该函数就行。
class specialFunction_Hermite
{
public:
    specialFunction_Hermite(int n,double min,double max,double dx);
    specialFunction_Hermite(int n);
    Matrix answer;
    double count(double x);
    vector<double> function;
private:
    void suit(int n);
    vector<double> multi2x(vector<double> list);
    vector<double> multi(vector<double> list,int n);
    vector<double> pluss(vector<double> list1,vector<double> list2);
};

#endif // SPECIALFUNCTION_HERMITE_H
