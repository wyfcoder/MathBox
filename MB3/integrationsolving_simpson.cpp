#include "integrationsolving_simpson.h"

IntegrationSolving_Simpson::IntegrationSolving_Simpson()
{
    a=0;
    b=0;
    has_save=false;
    save_position=0;
    return;
}

int IntegrationSolving_Simpson::count(Dealparams p)
{

    if(p.isNull) return 12;
    unsigned size=p.types.size();
    if(size==3||size==4)
    {
        if(p.types[0].type!=3) return 12;
        if(p.types[0].new_function.virtualSize!=1) return 12;
        f=p.types[0].new_function;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        a=p.types[1].number;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        b=p.types[2].number;
        if(size==3)
        {
          simpson();
        }
        else
        {
            if(p.types[3].type!=1) return 12;
            has_save=true;
            save_position=p.types[3].position;
            simpson();
        }
    }
    return 0;
}

void IntegrationSolving_Simpson::simpson()
{
    vector<double> m;
    bool signal=true;
    if(b<a)
    {
        signal=false;
        double k=b;
        b=a;
        a=k;
    }
    n=10000*(b-a);
    if(n>10000000)
      n=10000000;
    interval=(b-a)/n;
    half_interval=interval/2.0;
    sum_even=0.0;
    sum_odd=0.0;
    for(int k=0;k<n;k++)
    {
       x=a+k*interval;
       m.push_back(x);
       sum_even+=f.calculate(m)*half_interval;
       m.pop_back();
       m.push_back(x+half_interval);
       sum_odd+=f.calculate(m)*half_interval;
       m.pop_back();
    }
    m.push_back(a);
    double l1=f.calculate(m)*half_interval;
    m.pop_back();
    m.push_back(b);
    double l2=f.calculate(m)*half_interval;
    m.pop_back();
    integration=( 2.0*sum_even+ 4.0*sum_odd-l1+l2 )/3.0;
    if(!signal)
    integration*=-1.0;
}
