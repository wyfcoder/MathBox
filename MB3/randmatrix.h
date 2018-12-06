#ifndef RANDMATRIX_H
#define RANDMATRIX_H
#include"matrix.h"
#include"dealparams.h"
#include"randcount.h"
class RandMatrix
{
public:
    RandMatrix();
    bool rand(Dealparams p,RandCount& r);
    Matrix new_Matrix;
    unsigned position;
private:
   RandCount r;
};

#endif // RANDMATRIX_H
