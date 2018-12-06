#ifndef SPECIALFUNCTION_BEZIER_H
#define SPECIALFUNCTION_BEZIER_H
#include<math.h>
#include"matrix.h"
class specialFunction_Bezier
{
public:
    specialFunction_Bezier(int n,double min,double max,double dx);
    int n;
    Matrix m;
    public:
    double integration;
    private:
    void simpson(double x);
    double function(double x,double theata);
    const double PI=atan(1.)*4.;
};

#endif // SPECIALFUNCTION_BEZIER_H
