#include "specialfunction_legendre.h"
#include"functionbuildhelper.h"
specialFunction_Legendre::specialFunction_Legendre(int n,double min,double max,double dx)
{
    QString message="";
    vector<double> function;
    vector<double> near;
    vector<double> far;
    if(n<=5)
    {
        switch (n)
        {
        case 0:
            function.push_back(1);
            function.push_back(0);
            break;
        case 1:
            function.push_back(1);
            function.push_back(1);
            break;
        case 2:
            function.push_back(1.5);
            function.push_back(2);
            function.push_back(-0.5);
            function.push_back(0);
            break;
        case 3:
            function.push_back(2.5);
            function.push_back(3);
            function.push_back(-1.5);
            function.push_back(1);
            break;
        case 4:
            function.push_back(4.375);
            function.push_back(4);
            function.push_back(-3.75);
            function.push_back(2);
            function.push_back(0.375);
            function.push_back(0);
            break;
        case 5:
            function.push_back(7.875);
            function.push_back(5);
            function.push_back(-8.75);
            function.push_back(3);
            function.push_back(1.875);
            function.push_back(1);
            break;
        }
    }
    else
    {
        far.push_back(4.375);
        far.push_back(4);
        far.push_back(-3.75);
        far.push_back(2);
        far.push_back(0.375);
        far.push_back(0);

        near.push_back(7.875);
        near.push_back(5);
        near.push_back(-8.75);
        near.push_back(3);
        near.push_back(1.875);
        near.push_back(1);

      int i=6;
      while (i<=n)
      {
       near=multix(near,i-1);
       far=multi(far,i-1);
       function=pluss(near,far);
       far=near;
       near=function;
       i++;
      }
    }

    while (min<max)
    {
        double sum=0;
        vector<double> pair;
        for(unsigned i=0;i<function.size();i+=2)
        sum+=function[i]*pow(min,function[i+1]);
        pair.push_back(min);
        pair.push_back(sum);
        answer.arrays.push_back(pair);
        min+=dx;
    }

    answer.m=answer.arrays.size();
    answer.n=2;
}


vector<double> specialFunction_Legendre::multix(vector<double> list,int l)
{
    double div=l/(l+1)+1;
    for(unsigned i=0;i<list.size();i+=2)
    {
        list[i]*=div;
        list[i+1]+=1;
    }
    return list;
}

vector<double> specialFunction_Legendre::multi(vector<double> list,int l)
{
    double div=-l/(l+1);
    for(unsigned i=0;i<list.size();i+=2)
    {
        list[i]*=div;
    }
    return list;
}

vector<double> specialFunction_Legendre::pluss(vector<double> list1,vector<double> list2)
{
    vector<double> answer;
    double max;
    double min;
    double save;
    if(list1[1]>list2[1])
    {
        max=list1[1];
    }
    else max=list2[1];
    if(list1[list1.size()-1]>list2[list2.size()-1])
    {
        min=list2[list2.size()-1];
    }
    else min=list1[list1.size()-1];
    save=max;
    while(min<=save||fabs(min-save)<0.0001)
    {
        answer.push_back(0);
        answer.push_back(save);
        save-=1;
    }
    for(unsigned i=0;i<list1.size();i+=2)
    {
        answer[2*(max-list1[i+1])]+=list1[i];
    }
    for(unsigned i=0;i<list2.size();i+=2)
    {
        answer[2*(max-list2[i+1])]+=list2[i];
    }
    return answer;
}
