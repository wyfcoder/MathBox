#ifndef REGRESSIONUNIFIED_H
#define REGRESSIONUNIFIED_H
#include<vector>
#include"matrix.h"
#include"function.h"
using namespace std;
class regressionUnified
{
public:
    regressionUnified(int id,Matrix m);
private:
    int  i,n,m;
    double sum_x,sum_y,sum_xx,sum_xy,rr,rr_num,rr_denom;
    vector<double> x,y,y_model;
public:
    double a,b;
    bool ok;
    void ShowRegression();
    void buildFunction();
    void sline();
    void exp1();
    void exp2();
    void exp3();
    void power();
    void logarithmic();
    void square_root();
    void one_third();
    void inverse();
    void summations();
    void r_sq();
    Function f;
};

#endif // REGRESSIONUNIFIED_H
