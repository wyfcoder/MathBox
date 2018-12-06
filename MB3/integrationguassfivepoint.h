#ifndef INTEGRATIONGUASSFIVEPOINT_H
#define INTEGRATIONGUASSFIVEPOINT_H
#include"function.h"
#include"dealparams.h"
class IntegrationGuassFivePoint
{
public:
    IntegrationGuassFivePoint();
    int count(Dealparams p);
private:
    double a,b,x,w[5],t[5];
public:
    double integration;
    bool   has_save;
    int    save_position;
private:
   void GaussFivePointsIntegration();
   Function f;
};

#endif // INTEGRATIONGUASSFIVEPOINT_H
