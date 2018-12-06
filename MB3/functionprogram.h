#ifndef FUNCTIONPROGRAM_H
#define FUNCTIONPROGRAM_H
#include<vector>
#include"function.h"
#include"randcount.h"
using namespace std;
class FunctionProgram
{
public: FunctionProgram();

public: Function RandFunction(int params);
private:
    QString functions;
    RandCount rand;
    bool randBool();//二次随机判决
    void randOp();//返回随机的操作符
    void randCount(int params);//返回随机算式
    void addK();//随机的加括号
    void addK(int start);//有开头的括号
    int  addF(int style);//添加一个函数
    bool isOp(int position);
    vector<QString> parms;//表示给定的自变量名
};

#endif // FUNCTIONPROGRAM_H
