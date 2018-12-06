#ifndef PARMTYPE_H
#define PARMTYPE_H
#include<QString>
#include<function.h>
#include"matrix.h"
class ParmType
{
public:
    ParmType();
 public:
    int type;
    int position;
    bool isTrue;
    double number;
    int n;
    QString name;
    Function new_function;
    Matrix new_matrix;
};


//NumberExpression 0
//Number 1
//FunctionExpression 2
//Function 3
//MatrixExpression 4
//Matrix 5
#endif // PARMTYPE_H
