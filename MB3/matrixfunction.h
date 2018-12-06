#ifndef MATRIXFUNCTION_H
#define MATRIXFUNCTION_H
#include"matrix.h"
namespace  MatrixFunction
{
Matrix Sin(Matrix);
Matrix Cos(Matrix);
Matrix Tan(Matrix);
Matrix Cot(Matrix);
Matrix ASin(Matrix);
Matrix ACos(Matrix);
Matrix ATan(Matrix);
Matrix ACot(Matrix);
Matrix Exp(Matrix);
Matrix Log(Matrix);
Matrix Ln(Matrix);
Matrix Sqrt(Matrix);
}
Matrix MatrixFunction::Sin(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=sin(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Cos(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=cos(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Tan(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=tan(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Cot(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=1.0/tan(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::ACos(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=acos(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::ACot(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=atan(1.0/m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::ASin(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=asin(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::ATan(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=atan(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Exp(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=exp(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Ln(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=log(m.arrays[i][j]);
    return m;
}
Matrix MatrixFunction::Log(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=log(m.arrays[i][j])/log(10);
    return m;
}
Matrix MatrixFunction::Sqrt(Matrix m)
{
    for(unsigned i=0;i<m.m;i++)
        for(unsigned j=0;j<m.n;j++)
            m.arrays[i][j]=sqrt(m.arrays[i][j])/log(10);
    return m;
}
#endif // MATRIXFUNCTION_H
