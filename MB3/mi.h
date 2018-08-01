#ifndef MI_H
#define MI_H
#include<vector>
#include"mathi.h"
using namespace  std;
class MI
{
public:
    MI();
    vector<MathI> allAnswers();
    int times;
private:
    int size;
    struct ff
    {
       double f1;
       double f2;
    };
    vector<double> function;
    vector<double> function2;
    vector<MathI> answer;
    MathI getM(double a,double b);
    ff countF(double x);
    double rAnswer();
    ff iAnswer();
    void XY(double);
    double exps;
    bool isStartI;
    int maxTime=100000000;
};

#endif // MI_H
