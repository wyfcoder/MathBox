#include "specialfunction_hermite.h"
#include"functionbuildhelper.h"
#include<vector>
using namespace std;

specialFunction_Hermite::specialFunction_Hermite(int n,double min,double max,double dx)
{
    suit(n);
    while (min<max)
    {
        vector<double> pair;
        pair.push_back(min);
        pair.push_back(count(min));
        answer.arrays.push_back(pair);
        min+=dx;
    }
    answer.m=answer.arrays.size();
    answer.n=2;
}

specialFunction_Hermite::specialFunction_Hermite(int n)
{
    suit(n);
}

void specialFunction_Hermite::suit(int n)
{
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
            function.push_back(2);
            function.push_back(1);
            break;
        case 2:
            function.push_back(4);
            function.push_back(2);
            function.push_back(2);
            function.push_back(0);
            break;
        case 3:
            function.push_back(8);
            function.push_back(3);
            function.push_back(-12);
            function.push_back(1);
            break;
        case 4:
            function.push_back(16);
            function.push_back(4);
            function.push_back(-48);
            function.push_back(2);
            function.push_back(12);
            function.push_back(0);
            break;
        case 5:
            function.push_back(32);
            function.push_back(5);
            function.push_back(-160);
            function.push_back(3);
            function.push_back(120);
            function.push_back(1);
            break;
        }
    }
    else
    {
        far.push_back(16);
        far.push_back(4);
        far.push_back(-48);
        far.push_back(2);
        far.push_back(12);
        far.push_back(0);

        near.push_back(32);
        near.push_back(5);
        near.push_back(-160);
        near.push_back(3);
        near.push_back(120);
        near.push_back(1);
      int i=6;
      while (i<=n)
      {
       near=multi2x(near);
       far=multi(far,i-1);
       function=pluss(near,far);
       far=near;
       near=function;
       i++;
      }
    }
}

double specialFunction_Hermite::count(double x)
{
    double sum=0;
    for(unsigned i=0;i<function.size();i+=2)
    sum+=function[i]*pow(x,function[i+1]);
    return sum;
}

vector<double> specialFunction_Hermite::multi(vector<double> list,int n)
{
    for(unsigned i=0;i<list.size();i++)
    {
        if(i%2==0)list[i]*=-2*n;
    }
    return list;
}

vector<double> specialFunction_Hermite::multi2x(vector<double> list)
{
   for(unsigned i=0;i<list.size();i++)
   {
       if(i%2==0)list[i]*=2;
       else      list[i]+=1;
   }
   return list;
}

vector<double> specialFunction_Hermite::pluss(vector<double> list1,vector<double> list2)
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

