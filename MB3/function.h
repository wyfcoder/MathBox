#ifndef FUNCTION_H
#define FUNCTION_H
#include<QString>
#include<vector>
#include"c.h"
using namespace std;
class Function
{
public:
    Function();
    QString function;
    QString virtualName;
    int virtualSize;
    vector<QString> virtualNames;
    vector<double> virtualValues;
    vector<C> saves;
    double calculate(vector<double> v);
    void setParms(double v);
    void setParms(vector<double> values);

    double counter(unsigned start, unsigned end);//计算数，将检查过的list计算即可
    int blockEnd(unsigned position);//获得一个块的结尾
    int smallBolckEnd(unsigned position, unsigned end);//获取一个最小块的位置

    double counter_bolck(unsigned start,unsigned end);//计算一个块的程序
    double count_smallBlock(unsigned start,unsigned end);//计算一个小小块

};

#endif // FUNCTION_H
