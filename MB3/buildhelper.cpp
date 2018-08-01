#include "buildhelper.h"

buildhelper::buildhelper()
{
    className.append("Matrix");//0
    className.append("Number");//1
    className.append("Function");//2
    functionName.push_back("Sin");
    functionName.push_back("Cos");
    functionName.push_back("Tan");
    functionName.push_back("Cot");
    functionName.push_back("Asin");
    functionName.push_back("Acos");
    functionName.push_back("Atan");
    functionName.push_back("Acot");
    functionName.push_back("Ln");
    functionName.push_back("Log");
    functionName.push_back("Exp");
    functionName.push_back("Pow");
    functionName.push_back("Sqrt");
}
int buildhelper::getClassMode(QString message)
{
    int classMode=-1;
    position=0;
    inputText(text);
    for(int i=0;i<className.size();i++)//匹配，确定类的种类
    {
        int m;
        for(m=0;m<className[i].size();m++)
        {
         if(text[m]!=className[i][m]&&m<text.size())
             break;
        }
        if(m==className[i].size()&&text[m]==' '&&text.size()>m)
        {
            classMode=i;
            position=m;
            break;
        }
    }
    return classMode;
}

void buildhelper::inputText(QString text)
{
    this->text=text;
}
