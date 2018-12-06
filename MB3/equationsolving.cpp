#include "equationsolving.h"
#include"dealparams.h"
#include<mathi.h>
//求解方程根的算法式
EquationSolving::EquationSolving()
{
    exp=0.0000001;
    start=0;
    end=0;
    has_save=false;
    save_position=0;
    isOk=false;
    return;
}

int EquationSolving::count(Dealparams p)
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
            twoPoint();
        }
        else
        {
            if(p.types[3].type!=1) return 12;
            has_save=true;
            save_position=p.types[3].position;
            twoPoint();
        }
    }
    else if(size==1||size==2)
    {
        if(p.types[0].type!=3) return 12;
        if(p.types[0].new_function.virtualSize!=1) return 12;
        f=p.types[0].new_function;
        if(size==1)
        {
            NewTon();
        }
        else
        {
            if(p.types[2].type!=1) return 12;
            has_save=true;
            save_position=p.types[2].position;
            NewTon();
        }
    }
    else
    {
        return 12;
    }
    return 0;
}

void EquationSolving::twoPoint()
{
    if(start>=end)
    {
        isOk=false;
        return;
    }
    double e=start,s=end;
    double center;
    double counter=0;
    vector<double> x;
    x.push_back(start);
    if(fabs(f.calculate(x))<exp)
    {
        isOk=true;
        answer=start;
        return;
    }
    do
    {
        center=(e+s)/2;
        if(x.size()!=0) x.pop_back();
        x.push_back(e);
        double a=f.calculate(x);
        x.pop_back();
        x.push_back(center);
        double b=f.calculate(x);
        if(a*b<0)
        {
            s=center;
        }
        else if(a*b>0)
        {
            e=center;
        }
        else
        {
            break;
        }
        x.pop_back();
        x.push_back(center);
        counter++;
    }
    while (fabs(f.calculate(x))>exp&&counter<1000000);
    if(counter>=1000000) isOk=false;
    else
    {
        isOk=true;
        answer=center;
    }
}

double EquationSolving::getF1(double x)
{
    vector<double> a1;
    a1.push_back(x);
    double f1=f.calculate(a1);
    a1.pop_back();
    a1.push_back(x+0.00000000001);
    double f2=f.calculate(a1);
    return (f2-f1)/(0.00000000001);
}

void EquationSolving::NewTon()
{
    double x0=0.5;
    vector<double> a1;
    a1.push_back(x0);
    double f1=f.calculate(a1);
    a1.pop_back();
    int counter=0;
    while(fabs(f1)>exp&&counter<1000000)
    {
        double m=getF1(x0);
        if(fabs(m-0)<exp)
        {
            isOk=false;
            return;
        }
        x0=x0-f1/m;
        a1.push_back(x0);
        f1=f.calculate(a1);
        a1.pop_back();
        counter++;
    }
    if(counter>=1000000) isOk=false;
    else
    {
        isOk=true;
        answer=x0;
    }
}
