#ifndef DEALPARAMS_H
#define DEALPARAMS_H
#include<vector>
#include"matrix.h"
#include"function.h"
#include"number.h"
#include"parmtype.h"
using namespace std;
class Dealparams
{
public:
    Dealparams(QString text,vector<Number> n,vector<Function> f,vector<Matrix> m);
    bool isTrue;
    bool isNull;
    vector<ParmType> types;
private:
    bool dealOneParam(QString text);
    int  class_mode(QString name);
    unsigned  position;
    vector<Number> numbers;
    vector<Function> functions;
    vector<Matrix> matrixs;
};

#endif // DEALPARAMS_H
