#include "integrationsolving_romberg.h"
#include<vector>
using namespace std;
IntegrationSolving_Romberg::IntegrationSolving_Romberg()
{
    a=0;
    b=0;
    isOk=false;
    has_save=false;
    eps=0.00000001;
    save_position=0;
    return;
}
int IntegrationSolving_Romberg::count(Dealparams p)
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
          Romberg();
        }
        else
        {
            if(p.types[3].type!=1) return 12;
            has_save=true;
            save_position=p.types[3].position;
            Romberg();
        }
    }
    return 0;
}

void IntegrationSolving_Romberg::Romberg()
{
    interval=b-a;
    n=1;
    vector<double> x1;
    vector<double> x2;
    x1.push_back(a);
    x2.push_back(b);
    t1=interval/2.0*(f.calculate(x1)+f.calculate(x2));
    int count=0;
    while(count<1000000)
    {
         s=0.0;
         for(int i=1;i<=n;i++)
         {
             x1.pop_back();
             x1.push_back(a+(i-0.5)*interval);
             s+=f.calculate(x1);
         }
         count+=n;
         t2=t1/2.0+interval/2.0*s;
         s2=t2+(t2-t1)/3.0;
         if(n!=1)
         {
             c2=s2+(s2-s1)/15.0;
             if(n!=2)
             {
                 integration=c2+(c2-c1)/63;
                 if(n!=4)
                 {
                     if(fabs(integration)>1.0)
                         dataeps=fabs((integration-r1)/integration);
                     else
                         dataeps=fabs(integration-r1);
                     if(dataeps<eps)
                         break;
                 }
                 r1=integration;
             }
             c1=c2;
         }
         n*=2;
         interval/=2;
         t1=t2;
         s1=s2;
    }
    if(count>1000000)
        isOk=false;
    else
        isOk=true;
}
