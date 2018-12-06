#include "specialfunction_bezier.h"
#include<vector>
using namespace std;
specialFunction_Bezier::specialFunction_Bezier(int n,double min,double max,double dx)
{
    this->n=n;
    m.n=2;
    while (min<max)
    {
        simpson(min);
        vector<double> pair;
        pair.push_back(min);
        pair.push_back(integration/PI);
        m.arrays.push_back(pair);
        min+=dx;
    }
    m.m=m.arrays.size();
}


void specialFunction_Bezier::simpson(double x)
{
    double start=0;
    double step=0.001;
    int    count=1;
    integration=1.0/3.0*function(x,start)*step;
    while(start<=PI)
    {
        if(count%2==1) integration+=4.0/3.0*function(x,start)*step;
        else           integration+=2.0/3.0*function(x,start)*step;
        count++;
        start+=step;
    }
    if(count%2==1) integration-=function(x,start-step)*step;
    else   integration-=1.0/3.0*function(x,start-step)*step;
}

double specialFunction_Bezier::function(double x,double theata)
{
    return cos(x*sin(theata)-n*theata);
}
