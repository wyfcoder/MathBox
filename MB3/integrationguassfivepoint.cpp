#include "integrationguassfivepoint.h"
#include<vector>
using namespace std;
IntegrationGuassFivePoint::IntegrationGuassFivePoint()
{
    w[0]=0.2369269;
    w[1]=0.4786287;
    w[2]=0.5688889;
    w[3]=0.4786287;
    w[4]=0.2369269;
    t[0]=-0.90617985;
    t[1]=-0.53846931;
    t[2]=0.0;
    t[3]=0.53846931;
    t[4]=0.90617985;
}

int IntegrationGuassFivePoint::count(Dealparams p)
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
          GaussFivePointsIntegration();
        }
        else
        {
            if(p.types[3].type!=1) return 12;
            has_save=true;
            save_position=p.types[3].position;
            GaussFivePointsIntegration();
        }
    }
    return 0;
}

void IntegrationGuassFivePoint::GaussFivePointsIntegration()
{
    integration=0.0;
    vector<double> m;
    for(int i=0;i<5;i++)
    {
        x=(t[i]*(b-a)+b+a)/2.0;
        m.push_back(x);
        integration+=w[i]*f.calculate(m);
        m.pop_back();
    }
    integration*=(b-a)/2;
}
