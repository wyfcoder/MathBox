#ifndef LINEAREQUATIONSSOLVING_ITERATIONW_H
#define LINEAREQUATIONSSOLVING_ITERATIONW_H
#include"matrix.h"
#include<vector>
class linearequationssolving_iterationW
{
public:
    linearequationssolving_iterationW(Matrix m,double w,double dx,double max);
    Matrix answer;
    bool isOk;
private:
    double max_time;
    double w;//松弛因子
    double dx;//误差接受范围
    vector<double> x_new;
};

#endif // LINEAREQUATIONSSOLVING_ITERATIONW_H
