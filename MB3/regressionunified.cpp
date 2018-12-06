#include "regressionunified.h"
#include"functionbuildhelper.h"
#include<math.h>
using namespace std;
regressionUnified::regressionUnified(int id,Matrix matrix)
{
    sum_x=sum_y=sum_xx=sum_xy=rr_num=rr_denom=0.0;
    a=b=0.0;
    ok=true;
    m=matrix.m;
    n=id;
    ok=true;
    for(unsigned i=0;i<matrix.m;i++)
    {
        x.push_back(matrix.arrays[i][0]);
        y.push_back(matrix.arrays[i][1]);
    }
     for(unsigned i=0;i<m;i++)
     {
         y_model.push_back(0);
     }
     ShowRegression();
     if(ok)
     {
         buildFunction();
     }
}

void regressionUnified::buildFunction()
{
    QString messages="";
    switch (n)
    {
    case 1:
        messages="Function y(x)="+QString::number(a,10,6)+"*x+"+QString::number(b,10,6)+";";
        break;
    case 2:
        messages="Function y(x)="+QString::number(a,10,6)+"*Pow("+QString::number(b,10,6)+",x)"+";";
        break;
    case 3:
        messages="Function y(x)="+QString::number(a,10,6)+"*Exp("+QString::number(b,10,6)+"*x)"+";";
        break;
    case 4:
        messages="Function y(x)="+QString::number(a,10,6)+"*Exp(x)+"+QString::number(b,10,6)+";";
        break;
     case 5:
        messages="Function y(x)="+QString::number(a,10,6)+"*Pow(x,"+QString::number(b,10,6)+");";
        break;
     case 6:
        messages="Function y(x)="+QString::number(a,10,6)+"*Ln(x)"+QString::number(b,10,6)+";";
        break;
     case 7:
        messages="Function y(x)="+QString::number(a,10,6)+"*Pow(x,0.5)"+QString::number(b,10,6)+";";
        break;
     case 8:
        messages="Function y(x)="+QString::number(a,10.6)+"*Pow(x,0.33)*"+QString::number(b,10,6)+";";
        break;
     case 9:
        messages="Function y(x)="+QString::number(a,10.6)+"/x+"+QString::number(b,10,6)+";";
        break;
    default:
        break;
    }
    vector<Function> fs;
    FunctionBuildHelper helper(messages);
    helper.helperBuilderFunction(fs);
    f=helper.new_function;
}

void regressionUnified::ShowRegression()
{
    switch(n)
  {
    case 1:
    {
        sline();
    }
        break;
    case 2:
    {
       exp1();
    }
        break;
    case 3:
    {
        exp2();
    }
        break;
    case 4:
    {
        exp3();
    }
        break;
    case 5:
    {
        power();
    }
        break;
    case 6:
    {
        logarithmic();
    }
        break;
    case 7:
    {
        square_root();
    }
        break;
    case 8:
    {
        one_third();
    }
        break;
    case 9:
    {
        inverse();
    }
        break;

  }
}

void regressionUnified::sline()
{
        summations();
        a=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        b=(sum_y-a*sum_x)/m;
}


void regressionUnified::exp1()
{
    for(i=0;i<m;i++)
    {
       if(y[i]<=0.0)
       {
           ok=false;
       }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            y[i]=log(y[i]);
        }
        summations();
        b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        a=(sum_y-b*sum_x)/m;
        a=exp(a);
        b=exp(b);
        for(i=0;i<m;i++)
        {
            y_model[i]=log(b)*x[i]+log(a);
        }
        r_sq();
    }
}

void regressionUnified::exp2()
{
    for(i=0;i<m;i++)
    {
       if(y[i]<=0.0)
       {
           ok=false;
       }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            y[i]=log(y[i]);
        }
        summations();
        b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        a=(sum_y-b*sum_x)/m;
        a=exp(a);
        for(i=0;i<m;i++)
        {
            y_model[i]=b*x[i]+log(a);
        }
        r_sq();
    }
}

void regressionUnified::exp3()
{
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            x[i]=exp(x[i]);
        }
        summations();
        a=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        b=(sum_y-a*sum_x)/m;
        for(i=0;i<m;i++)
        {
            y_model[i]=a*x[i]+b;
        }
        r_sq();
    }
}

void regressionUnified::power()
{
    for(i=0;i<m;i++)
    {
        if((y[i]<=0.0)||(x[i]<=0.0))
        {
            ok=false;
        }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            y[i]=log(y[i]);
            x[i]=log(x[i]);
        }
        summations();
        b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        a=(sum_y-b*sum_x)/m;
        a=exp(a);
        for(i=0;i<m;i++)
        {
            y_model[i]=b*x[i]+log(a);
        }
        r_sq();
    }
}

void regressionUnified::logarithmic()
{
    for(i=0;i<m;i++)
    {
        if(x[i]<=0.0)
        {
            ok=false;
        }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            x[i]=log(x[i]);
        }
        summations();
        b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        a=(sum_y-b*sum_x)/m;
        for(i=0;i<m;i++)
        {
            y_model[i]=a*x[i]+b;
        }
        r_sq();
    }

}

void regressionUnified::square_root()
{
    for(i=0;i<m;i++)
    {
        if(x[i]<0.0)
        {
            ok=false;
        }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            x[i]=sqrt(x[i]);
        }
        summations();
        a=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        b=(sum_y-b*sum_x)/m;
        for(i=0;i<m;i++)
        {
            y_model[i]=a*x[i]+b;
        }
        r_sq();
    }
}

void regressionUnified::one_third()
{
    for(i=0;i<m;i++)
    {
        if(x[i]<0.0)
        {
            ok=false;
        }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            x[i]=pow(x[i],0.33);
        }
        summations();
        a=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        b=(sum_y-b*sum_x)/m;
        for(i=0;i<m;i++)
        {
            y_model[i]=a*x[i]+b;
        }
        r_sq();
    }
}

void regressionUnified::inverse()
{
    for(i=0;i<m;i++)
    {
        if(x[i]==0.0)
        {
            ok=false;
        }
    }
    if(ok)
    {
        for(i=0;i<m;i++)
        {
            x[i]=1.0/x[i];
        }
        summations();
        a=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-pow(sum_x,2));
        b=(sum_y-b*sum_x)/m;
        for(i=0;i<m;i++)
        {
            y_model[i]=a*x[i]+b;
        }
        r_sq();
    }
}

void regressionUnified::summations()
{
    for(i=0;i<m;i++)
    {
        sum_x+=x[i];
        sum_y+=y[i];
        sum_xx+=pow(x[i],2);
        sum_xy+=x[i]*y[i];
    }
}

void regressionUnified::r_sq()
{
    for(i=0;i<m;i++)
    {
        rr_num+=pow((y_model[i]-sum_y/m),2);
        rr_denom+=pow((y[i]-sum_y/m),2);
    }
    rr=rr_num/rr_denom;
}
