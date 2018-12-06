#include "regressionplecrvefitting.h"
#include"MainGauss.h"
#include"functionbuildhelper.h"
regressionPlecrvefitting::regressionPlecrvefitting(int number,Matrix matrix)
{
    n=matrix.m;
    m=number;
       for(i=0;i<n;i++)
       {
        x.push_back(matrix.arrays[i][0]);
        y.push_back(matrix.arrays[i][1]);
       }
    vector<double> s1;

    for(i=0;i<m;i++)
    {
        c.push_back(s1);
        for(j=0;j<m;j++)
        {
            c[i].push_back(0);
        }
    }
    for(i=0;i<m;i++)
    {
        a.push_back(s1);
        for(j=0;j<=m;j++)
        a[i].push_back(0);
    }
    for(i=0;i<m;i++)
    {
        b.push_back(0);
        d.push_back(0);
    }
    MultipleCurveFitting();
}

void regressionPlecrvefitting::MultipleCurveFitting()
{
    for(i=0;i<m;i++)
      {
        for(j=0;j<m;j++)
        {
            c[i][j]=0;
            for(k=0;k<n;k++)
                c[i][j]+=pow(x[k],i+j);

        }
        d[i]=0;
        for(k=0;k<n;k++)
            d[i]+=y[k]*pow(x[k],i);

      }
    Gauss();
    if(!isTrue) return;
    QString message="Function f(x)=";
    for(i=0;i<m;i++)
    {
        if(i==0)
            message.append(QString::number(b[0],10,6));
        else
        {
             if(b[i]>0) message.append("+");
             if(i==1) message.append(QString::number(b[1],10,6)+"*x");
             else message.append(QString::number(b[i],10,6)+"*Pow(x,"+QString::number(i)+")");
        }
    }
    message.append(";");
    vector<Function> fs;
    FunctionBuildHelper helper(message);
    helper.helperBuilderFunction(fs);
    new_function=helper.new_function;
}

void regressionPlecrvefitting::Gauss()
{
    isTrue=true;
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
            a[i][j]=c[i][j];
    }
    for(i=0;i<m;i++)
       a[i][m]=d[i];
    Matrix f;
    f.setMN(m,m+1);
    for(i=0;i<m;i++)
    for(j=0;j<=m;j++)
        f.arrays[i][j]=a[i][j];
    MainGauss guass(f);
    if(!guass.isTrue)
    {
        isTrue=false;
        return;
    }
    for(int i=0;i<m;i++)
        b[i]=guass.new_matrix.arrays[i][0];
}
