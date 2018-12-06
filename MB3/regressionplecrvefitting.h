#ifndef REGRESSIONPLECRVEFITTING_H
#define REGRESSIONPLECRVEFITTING_H
#include <iostream>
#include <math.h>
#include <vector>
#include"matrix.h"
#include"function.h"
using namespace std;
class regressionPlecrvefitting
{
public:
    regressionPlecrvefitting(int number,Matrix m);
    Function new_function;
    bool isTrue;
private:
    int i,j,k,n;
    double s;
    vector<double>x,y,d,b,data;
    vector<vector<double>>c,a,t;
    void MultipleCurveFitting();
    void Gauss();
    int m;
};

#endif // REGRESSIONPLECRVEFITTING_H
