#include "project_Antennawire_ssa.h"
#include<vector>
#include<math.h>
using namespace std;
antennaWire_SSA::antennaWire_SSA(double k,double d,int n)
{
    double angle=-3.1415926;//采用弧度制
    saves.n=2;
    while (angle<3.1415926)
    {
        vector<double> s;
        double a=0;
        s.push_back(angle*180./3.1415926);
        if(fabs(angle)!=0)
        a=sin(n*0.5*k*d*cos(angle))/(sin(0.5*k*d*cos(angle))*n*1.0);
        else a=1;
        if(a<0) a*=-1.0;
        s.push_back(a);
        saves.arrays.push_back(s);
        angle+=0.001;
    }
    saves.m=saves.arrays.size();
}
