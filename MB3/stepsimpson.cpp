#include "stepsimpson.h"

StepSimpson::StepSimpson()
{
    exp=0.000000001;
    start=0;
    end=0;
    has_save=false;
    save_position=0;
    isOk=false;
    return;
}

int StepSimpson::count(Dealparams p)
{
    if(p.isNull) return 12;
    unsigned size=p.types.size();
    if(size==3||size==4)
    {
        if(p.types[0].type!=3) return 12;
        if(p.types[0].new_function.virtualSize!=1) return 12;
        f=p.types[0].new_function;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        start=p.types[1].number;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        end=p.types[2].number;
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

void StepSimpson::simpson()
{
    answer=0;
    n=1;
    interval=end-start;
    vector<double> a;
    vector<double> b;
    a.push_back(start);
    b.push_back(end);
    t1=interval/2.0*(f.calculate(a)+f.calculate(b));
    int count=0;
    while(count<1000000)
    {
        s=0;
        for(int i=1;i<=n;i++)
        {
           a.pop_back();
           a.push_back(start+(i-0.5)*interval);
           s+=f.calculate(a);
        }
        count+=n;
        t2=t1/2.0+interval/2.0*s;
        answer=t2+(t2-t1)/3.0;
        if(n!=1)
        {
            if(fabs(answer)>1)
                dataeps=fabs((answer-s1)/answer);
            else
                dataeps=fabs(answer-s1);
            if(dataeps<exp)
                break;
        }
        n*=2;
        interval/=2;
        t1=t2;
        s1=answer;
    }
    if(count>=1000000)
        isOk=false;
    else
        isOk=true;
}
