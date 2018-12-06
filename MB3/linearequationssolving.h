#ifndef LINEAREQUATIONSSOLVING_H
#define LINEAREQUATIONSSOLVING_H
#include"dealparams.h"
#include"matrix.h"
class LinearEquationsSolving
{
public:
    LinearEquationsSolving();
    bool solving(Dealparams p);
    unsigned position;
    bool isSaved;
    Matrix new_matrix;
    bool isTrue;
};

#endif // LINEAREQUATIONSSOLVING_H
