#include "regressionmultiple.h"
#include"matrix.h"
#include"MainGauss.h"
#include"functionbuildhelper.h"
regressionMultiple::regressionMultiple(Matrix matrix)
{
    n=matrix.m;
    m=matrix.n-1;
    a.resize(m);
    x.resize(m);
    for(i=0;i<m;i++)
    {
        for(j=0;j<=m;j++)
        {
            a[i].push_back(0);
        }
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            x[i].push_back(matrix.arrays[j][i]);
        }
        b.push_back(0);
    }
    for(i=0;i<n;i++)
         y.push_back(matrix.arrays[i][m]);
    MultipleRegressionCurveFitting();
}

void regressionMultiple::MultipleRegressionCurveFitting()
{
    for(i=0;i<m;i++)
       {
           for(j=0;j<m;j++)
           {
               sum1=0;
               sum2=0;
               sum3=0;
               sum4=0;
               sum5=0;
               for(k=0;k<n;k++)
               {
                   sum1+=x[i][k]*x[j][k];
                   sum2+=x[i][k];
                   sum3+=x[j][k];
                   sum4+=x[i][k]*y[k];
                   sum5+=y[k];
               }
                  a[i][j]=sum1-sum2*sum3/(1.0*n);
           }
           a[i][m]=sum4-sum2*sum5/(1.0*n);
       }
        Gauss();
        if(isTrue)
        {
            QString message="Function f(";
            for(i=0;i<m;i++)
            {
                message.append("x"+QString::number(i));
                if(i==m-1)
                    message.append(")");
                else
                    message.append(",");
            }
            message.append("=");

            for(i=0;i<m+1;i++)
            {
              if(i==0) message.append(QString::number(s,10,6));
              else
              {
                  if(b[i-1]>0)
                  {
                      message.append("+");
                  }
                  message.append(QString::number(b[i-1],10,6)+"*x"+QString::number(i-1));
              }
            }
            message.append(";");
            vector<Function> fs;
            FunctionBuildHelper helper(message);
            helper.helperBuilderFunction(fs);
            function=helper.new_function;
        }

}

void regressionMultiple::Gauss()
{
    isTrue=true;
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
    sum1=0.0;
    for(i=0;i<m;i++)
    {
        sum2=0;
        for(k=0;k<n;k++)
        {
            sum2+=x[i][k];
        }
        sum1+=b[i]*sum2;
    }
    s=(sum5-sum1)/n;
}
