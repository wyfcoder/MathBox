#ifndef EQUATIONSOLVING_H
#define EQUATIONSOLVING_H
#include"dealparams.h"
#include"function.h"
using namespace std;
class EquationSolving
{
public:
    EquationSolving();
    int count(Dealparams p1);
    bool isOk;
    bool has_save;
    int save_position;
    double answer;
private:
    Function f;
    double exp;
    double start;
    double end;
    void twoPoint();
    double getF1(double);
    void NewTon();
};

#endif // EQUATIONSOLVING_H
