#ifndef FUNCTIONBUILDHELPER_H
#define FUNCTIONBUILDHELPER_H
#include<QString>
#include<vector>
#include<function.h>
using namespace std;
class FunctionBuildHelper
{
public:
    FunctionBuildHelper(QString m);
    bool helperBuilderFunction(vector<Function> lists);
    //------------------------------
    QString function;
    Function new_function;
    vector<Function> functions;
    int position;
    //------------------------------
    bool getVirtualName();
    bool dealHeader();
    bool checkName(QString name);
    bool centerDeal();
    //------------------------------
    bool save();
    C returnMode(QChar m);
    bool isNumber();
    bool isOpertate(QChar m);
    QString getName();
    double saveNumber;
    int combinedFunctionSize;
    bool has_operator;
    vector<QString> functionName;
    //-------------------------------
    bool isWrong();//对构建好的数组进行查错
    bool PreNC(C next);
    bool PreFU(C next);
    bool PreOP(C pre,C next);
    bool PowCheck(unsigned& position);
    void dealCHeader();//对开头的符号进行处理

    //-------------------------合并类赋值
    bool dealExpression();
    bool combideExpression();
    int checkVirtulName();
    void cleanExpression();
    vector<int> signal;
    //-------------------------表达式的处理
    bool isExpression();
    bool is_expression;
    bool dealFunctionExpression(vector<Function> f);
    //-------------------------处理计算
};

#endif // FUNCTIONBUILDHELPER_H
