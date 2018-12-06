#ifndef INTEGRATIONSOLVING_SIMPSON_H
#define INTEGRATIONSOLVING_SIMPSON_H

#include"function.h"
#include"dealparams.h"
using namespace std;
class IntegrationSolving_Simpson
{
public:
    IntegrationSolving_Simpson();
    int count(Dealparams p);
private:
    int n;
    double a,b,interval,half_interval,sum_even,sum_odd,x;
public:
    double integration;
    bool    has_save;
    int  save_position;
    double  answer;
    Function f;
private:
  void  simpson();
};

#endif // INTEGRATIONSOLVING_SIMPSON_H
