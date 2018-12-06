#ifndef REGRESSIONMULTIPLE_H
#define REGRESSIONMULTIPLE_H
#include"matrix.h"
#include"function.h"
#include<vector>
using namespace std;
class regressionMultiple
{
public:
    regressionMultiple(Matrix m);
    bool isTrue;
    Function function;
private:
    int i,j,k,n;
    double sum1,sum2,sum3,sum4,sum5;
    vector<double>y,b;
    vector<vector<double>>a,x;
    void MultipleRegressionCurveFitting();
    void Gauss();
    int m;
    double s;
};

#endif // REGRESSIONMULTIPLE_H
