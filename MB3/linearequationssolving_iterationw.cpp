#include "linearequationssolving_iterationw.h"
#include<math.h>
#include<cstdio>
#include<cfloat>
linearequationssolving_iterationW::linearequationssolving_iterationW(Matrix m,double w,double dx,double max)
{
    this->w=w;
    this->dx=dx;
    this->max_time=max;
    vector<double> x_old;
    x_new.resize(m.m);
    x_old.resize(m.m);
    int time=0;
    double sum;

    while (time<max_time)
    {
        isOk=true;
        for(unsigned i=0;i<m.m;i++)
        {
            sum=0;
            x_old[i]=x_new[i];
            for(unsigned j=0;j<m.m;j++)
            {
                if(j!=i)
                {
                   sum-=m.arrays[i][j]*x_new[j];
                }
            }
            x_new[i]=(sum+m.arrays[i][m.m])/m.arrays[i][i];
        }
        for(unsigned i=0;i<m.m;i++)
        {
            x_new[i]=(1-w)*x_old[i]+w*x_new[i];
        }
        for(unsigned i=0;i<m.m;i++)
        {
            if(_finite(x_new[i])!=1)
            {
                isOk=false;
                break;
            }
            if(fabs(x_new[i]-x_old[i])>dx)
            {
                isOk=false;
                break;
            }
        }
        if(isOk) break;
         time++;
    }

    if(isOk)
    {
        answer.setMN(m.m,1);
        for(unsigned i=0;i<m.m;i++) answer.arrays[i][0]=x_new[i];
    }

}


