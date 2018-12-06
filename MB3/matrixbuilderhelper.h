#ifndef MATRIXBUILDERHELPER_H
#define MATRIXBUILDERHELPER_H
#include<QString>
#include<number.h>
#include<vector>
#include"matrix.h"
#include"c.h"
#include"matrixcheck.h"
using namespace std;
class MatrixBuilderHelper
{
public:
    MatrixBuilderHelper();
    bool helpBuildMatrix(QString text,QString name,vector<Number> numbers,vector<Matrix> matrixs);//一个完整的添加新的变量
    bool helpBuildExpression(QString text,vector<Number> numbers,vector<Matrix> matrixs);//用表达去计算一个新的变量
    QString text;
    Matrix newMatrix;
    vector<C> saves;
private:
    vector<Number> numbers;
    vector<QString> functionName;
    int position;
    bool setMN();//解析获取矩阵的横纵
    bool numberBuilder();//数字表达式赋值
    int m,n;
    //------------------------------------表达式编译类
    void makeVector();
    vector<Matrix> matrixs;
    //--------------------------------------
    bool save();
    C returnMode(QChar m);
    bool isNumber();
    double saveNumber;
    bool isOpertate(QChar m);
    QString getName();
    //---------------------------------------检查错误
    MatrixCheck check1(vector<C> lists);
    MatrixCheck check2(vector<C> lists);
    MatrixCheck returnfalse();
    vector<C> makeList(vector<C> list,int strat,int end);
    int returnPosition(vector<C> list,int start);
    //-----------------------------------------计算式
    Matrix count1(vector<C> list);
    Matrix count2(vector<C> list);
};

#endif // MATRIXBUILDERHELPER_H
