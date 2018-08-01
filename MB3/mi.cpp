#include "mi.h"
#include<fstream>
#include<math.h>
using namespace std;
MI::MI()
{
 ifstream in("data.txt");
 if (!in.is_open())
 {
     exit(0);
 }
 in>>size;
 in>>exps;
 for(int j=0;j<=size;j++)
 {
     double a;
     in>>a;
     function.push_back(a);
 }
 for(int j=0;j<size;j++)
 {
     function2.push_back(function[j]*(size-j));
 }
}
vector<MathI> MI::allAnswers()
{
    int at=0;
    vector<MathI> answers;
    int number=size;
    while (at<number&&times<100000000)
    {
        times=0;
        if(!isStartI)
        {
            double x=rAnswer();
            if(!isStartI)
            {
            MathI xi(x,0);
            answers.push_back(xi);
            at++;
            XY(x);
            }
        }
        else
        {
           double n=function[0];
           if(n!=1)
           for(int i=0;i<size;i++)
           {
               if(i==0)
                   function[i]=1;
               else
                   function[i]/=n;
           }
           if(size==2)
           {
               answers.push_back(getM(function[1],function[2]));
               MathI i(answers[at].r,-answers[at].i);
               at++;
               answers.push_back(i);
               at++;
           }
           else
           {
               ff f=iAnswer();
               answers.push_back(getM(f.f1,f.f2));
               MathI i(answers[at].r,-answers[at].i);
               at++;
               answers.push_back(i);
               at++;
           }
        }
    }
    return answers;
}

MI::ff MI::countF(double x)
{
    ff a;
    a.f1=0;
    a.f2=0;
    for(int i=0;i<=size;i++)
    {
       a.f1+=pow(x,size-i)*function[i];
    }
    for(int i=0;i<=size-1;i++)
    {
        a.f2+=pow(x,size-1-i)*function2[i];
    }
    return a;
}

double MI::rAnswer()
{
    double xold=0;
    double xnew;
    ff a;
    int times=0;
    do
    {
        a=countF(xold);
        if(a.f2!=0)
        xnew=xold-a.f1/a.f2;
        else
        {
            xnew=0;
            break;
        }
        xold=xnew;
        times++;
        if(times>maxTime)
        {
            isStartI=true;
            break;
        }
    }
    while(fabs(a.f1)>exps);
    return xnew;
}

MI::ff MI::iAnswer()
{
    vector<double> b(size-1);
    double r1,r2;
    ff f;
    f.f1=-1;
    f.f2=1;
    b[0]=1;
    do
    {
      for(int i=1;i<=size-2;i++)
      {
          if(i==1)
            b[1]=function[1]-f.f1*b[0];
          else
            b[i]=function[i]-f.f1*b[i-1]-f.f2*b[i-2];
      }
      r1=function[size-1]-f.f1*b[size-2]-f.f2*b[size-3];
      r2=function[size]-f.f2*b[size-2];
      f.f2=function[size]/b[size-2];
      f.f1=(function[size-1]-f.f2*b[size-3])/(b[size-2]);
      times++;
      if(times>100000000)
          break;
    }
    while(fabs(r1)>exps||fabs(r2)>exps);
    size-=2;
    function.clear();
    function=b;
    return f;
}
void MI::XY(double x)
{
   vector<double> newf;
   for(int i=0;i<size;i++)
   {
       if(i==0)
       {
           newf.push_back(function[i]);
       }
       else
       {
           newf.push_back(function[i]+newf[i-1]*x);
       }
   }
   function.clear();
   function=newf;
   size--;
   function2.clear();
   for(int j=0;j<size;j++)
   {
       function2.push_back(function[j]*(size-j));
   }
}
MathI MI::getM(double a, double b)
{
    MathI i(0,0);
    i.r=-a/2.0;
    i.i=pow(b-i.r*i.r,0.5);
    return i;
}

