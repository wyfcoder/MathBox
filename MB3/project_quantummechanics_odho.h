#ifndef PROJECT_QUANTUMMECHANICS_ODHO_H
#define PROJECT_QUANTUMMECHANICS_ODHO_H
#include"matrix.h"

class project_QuantumMechanics_ODHO
{
public:
    project_QuantumMechanics_ODHO(double m,double w,int n,double min,double max,double dx);
    Matrix answer;
};

#endif // PROJECT_QUANTUMMECHANICS_ODHO_H
