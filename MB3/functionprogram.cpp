#include "functionprogram.h"
#include"functionbuildhelper.h"
#include<iostream>
using namespace std;
FunctionProgram::FunctionProgram()
{

}
Function FunctionProgram::RandFunction(int params)
{
    rand.rand();
    functions="";
    functions.append("Function f(");
    for(int i=0;i<params;i++)
    {
        functions.append("x"+QString::number(i));
        if(i!=params-1) functions.append(",");
        else functions.append(")=");
    }

    for(int i=0;i<100;i++) rand.rand();//预热处理

    int size=100*rand.rand();

    while (size<1)
    {
        size=100*rand.rand();
    }

    int count=1;

    bool is_operate=randBool();
    if(is_operate)
    {
        if(randBool()) functions.append("+");else functions.append("-");
        is_operate=false;
    }
    while (count<size)
    {
        if(is_operate)
        {
            randOp();
            is_operate=false;
        }
        else
        {
            randCount(params);
            is_operate=true;
        }
        count++;
    }
    if(!is_operate)
    {
        randCount(params);
    }
    count=0;
    size=5*rand.rand();

    while(count<size)
    {
        int code=12*rand.rand();
        if(code>11)
             addK();
        else
        {
            addK(addF(code));
        }
             count++;     
    }

    functions.append(";");

    FunctionBuildHelper helper(functions);

    vector<Function>fs;

    bool isOk=helper.helperBuilderFunction(fs);

    if(!isOk)
    {
      cout<<functions.toStdString()<<endl;
    }
    Function f=helper.new_function;

    return f;
}

int FunctionProgram::addF(int style)
{
    int end= functions.size();
    int start=end*rand.rand();
    do
    {
         start=end*rand.rand();
         if(start>1&&functions[start-1]=='=') break;
    }
    while(start>=end-1||!isOp(start-1)||functions[start]==',');

    switch (style)
    {
    case 0:
    {
        functions.insert(start,'S');
        functions.insert(start+1,'i');
        functions.insert(start+2,'n');
        functions.insert(start+3,'(');
        start+=3;
    }
        break;
    case 1:
    {
        functions.insert(start,'C');
        functions.insert(start+1,'o');
        functions.insert(start+2,'s');
        functions.insert(start+3,'(');
        start+=3;
    }
        break;
   case 2:
    {
        functions.insert(start,'T');
        functions.insert(start+1,'a');
        functions.insert(start+2,'n');
        functions.insert(start+3,'(');
        start+=3;
    }
        break;
    case 3:
     {
        functions.insert(start,'C');
        functions.insert(start+1,'o');
        functions.insert(start+2,'t');
        functions.insert(start+3,'(');
        start+=3;
     }
         break;
    case 4:
     {
         functions.insert(start,'A');
         functions.insert(start+1,'s');
         functions.insert(start+2,'i');
         functions.insert(start+3,'n');
         functions.insert(start+4,'(');
         start+=4;
     }
         break;
    case 5:
     {
        functions.insert(start,'A');
        functions.insert(start+1,'c');
        functions.insert(start+2,'o');
        functions.insert(start+3,'s');
        functions.insert(start+4,'(');
        start+=4;
     }
         break;
    case 6:
     {
        functions.insert(start,'A');
        functions.insert(start+1,'t');
        functions.insert(start+2,'a');
        functions.insert(start+3,'n');
        functions.insert(start+4,'(');
        start+=4;
     }
         break;
    case 7:
     {
        functions.insert(start,'A');
        functions.insert(start+1,'c');
        functions.insert(start+2,'o');
        functions.insert(start+3,'t');
        functions.insert(start+4,'(');
        start+=4;
     }
         break;
    case 8:
     {
        functions.insert(start,'L');
        functions.insert(start+1,'n');
        functions.insert(start+2,'(');
        start+=2;
     }
         break;
    case 9:
     {
        functions.insert(start,'L');
        functions.insert(start+1,'o');
        functions.insert(start+2,'g');
        functions.insert(start+3,'(');
        start+=3;
     }
         break;
    case 10:
    {
        functions.insert(start,'E');
        functions.insert(start+1,'x');
        functions.insert(start+2,'p');
        functions.insert(start+3,'(');
        start+=3;
    }
        break;
    default:
    {
        functions.insert(start,'S');
        functions.insert(start+1,'q');
        functions.insert(start+2,'r');
        functions.insert(start+3,'t');
        functions.insert(start+4,'(');
        start+=4;
    }
        break;
    }
    return start;
}


bool FunctionProgram::randBool()
{
    if(rand.rand()>0.5) return true;
    else return false;
}
void FunctionProgram::randOp()
{
    if(randBool())
    {
        if(randBool())
        {
            functions.append("+");
        }
        else
        {
            functions.append("*");
        }
    }
    else
    {
        if(randBool())
        {
            functions.append("/");
        }
        else
        {
            functions.append("-");
        }
    }
}
void FunctionProgram::randCount(int params)
{
    int kind=3*rand.rand();
    if(kind<1)
    {
        double a=1000*rand.rand();
        functions.append(QString::number(a));
    }
    else
    {
        int a=params*rand.rand();
        functions.append("x"+QString::number(a));
    }
}
bool FunctionProgram::isOp(int position)
{
    if(position<0) return false;
    if(functions[position]=='+'||functions[position]=='-'||functions[position]=='*'||functions[position]=='/')
        return true;
    return false;
}

void FunctionProgram::addK()
{
    int end= functions.size();
    int start=end*rand.rand();
    do
    {
         start=end*rand.rand();
         if(start>1&&functions[start-1]=='=') break;
    }
    while(start>=end-1||!isOp(start-1));

    functions.insert(start,'(');

    addK(start);
}


void FunctionProgram::addK(int start)
{
    int end=functions.size();

    if(start==end-2) functions.append(")");

    int endK;

    do
    {
        endK=(end+1)*rand.rand();
        if(endK>=end)
        {
            functions.append(')');
            return;
        }
        if(endK>0)
        {
            if(functions[endK-1]=='(') endK++;
        }
    }
    while(endK<start||!isOp(endK));

    functions.insert(endK,')');
}
