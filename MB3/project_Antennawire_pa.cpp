#include "project_Antennawire_pa.h"

projectAntennaWirePA::projectAntennaWirePA(double k,double d,int n,double theata)
{
    double angle=-3.1415926;//采用弧度制
    save.n=2;
    while (angle<3.1415926)
    {
        vector<double> s;
        double a=0;
        s.push_back(angle*180./3.1415926);
        if(fabs(angle)!=0)
        a=sin(n*0.5*k*d*(cos(angle)-cos(theata)))/(sin(0.5*k*d*(cos(angle)-cos(theata)))*n*1.0);
        else a=1;
        if(a<0) a*=-1.0;
        s.push_back(a);
        save.arrays.push_back(s);
        angle+=0.001;
    }
    save.m=save.arrays.size();
}
