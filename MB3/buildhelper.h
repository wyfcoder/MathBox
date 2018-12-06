#ifndef BUILDHELPER_H
#define BUILDHELPER_H

#include<QString>
#include<QVector>
#include<vector>
#include"number.h"
#include"matrix.h"
#include "c.h"
using namespace std;
class buildhelper
{
public:
    buildhelper();

    int getClassMode(QString message);//获得类的种类

    void inputText(QString text);

    QString checkVirtulName();

    bool helpNumberBuilder(vector<Number>);//帮助构建数字类

    double value;
    bool isExpresson;
    int position;        
    vector<C> saves;
private:
    //-----------------------------------------------
    QVector<QString> className;
    QVector<QString> commands;
    vector<QString> functionName;
    vector<Number> numbers;
    QString Null;
    int virtualPosition;
    //----------------------------------------------
    QString text;

    QString virtualName;
    //----------------------------------------------------Number
        bool isNumberExit();
        QString getName();
        bool save();
        C returnMode(QChar m);
        bool isOpertate(QChar m);
        bool isfunction(QString);
        bool isNumber();

        bool isWrong();//对构建好的数组进行查错
        bool PreNC(C next);
        bool PreFU(C next);
        bool PreOP(C pre,C next);
        bool PowCheck(unsigned& position);


        void dealHeader();//对开头的符号进行处理
        double counter(unsigned start, unsigned end);//计算数，将检查过的list计算即可
        int blockEnd(unsigned position);//获得一个块的结尾
        int smallBolckEnd(unsigned position, unsigned end);//获取一个最小块的位置

        double counter_bolck(unsigned start,unsigned end);//计算一个块的程序
        double count_smallBlock(unsigned start,unsigned end);//计算一个小小块

        double saveNumber;
};

#endif // BUILDHELPER_H
