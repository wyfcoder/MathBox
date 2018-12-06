#ifndef SPECIALFUNCTION_LEGENDRE_H
#define SPECIALFUNCTION_LEGENDRE_H
#include"matrix.h"
#include<vector>
//提供返回函数的服务，用户指定下厄米多项式的阶数后，返回该函数就行。
class specialFunction_Legendre
{
public:
    specialFunction_Legendre(int n,double min,double max,double dx);
    Matrix answer;
private:
    vector<double> multix(vector<double> list,int l);
    vector<double> multi(vector<double> list,int l);
    vector<double> pluss(vector<double> list1,vector<double> list2);
};

#endif // SPECIALFUNCTION_LEGENDRE_H
