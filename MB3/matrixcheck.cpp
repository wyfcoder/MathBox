#include "matrixcheck.h"

MatrixCheck::MatrixCheck()
{

}

void MatrixCheck::operator=(MatrixCheck m)
{
    this->m=m.m;
    this->n=m.n;
}

bool MatrixCheck::operator==(MatrixCheck m)
{
    if(m.m==this->m&&m.n==this->n)return true;
    return false;
}

bool MatrixCheck::operator!=(MatrixCheck m)
{
    return !operator==(m);
}

void MatrixCheck::set(int a,int b)
{
    this->m=a;
    this->n=b;
}

