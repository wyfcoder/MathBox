#ifndef INTEGRATIONSOLVING_ROMBERG_H
#define INTEGRATIONSOLVING_ROMBERG_H
#include<math.h>
#include"function.h"
#include"dealparams.h"
using namespace std;
class IntegrationSolving_Romberg
{
public:
    IntegrationSolving_Romberg();
    int count(Dealparams p);
 private:
int n;
double a,b,interval,t1,t2,s,s1,s2,c1,c2,r1,eps,dataeps;
public:
double integration;
bool   has_save;
bool   isOk;
int    save_position;
private:
void Romberg();
Function f;
};
#endif // INTEGRATIONSOLVING_ROMBERG_H
