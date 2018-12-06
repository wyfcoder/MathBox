#ifndef MATRIXCHECK_H
#define MATRIXCHECK_H


class MatrixCheck
{
public:
    MatrixCheck();
    int m;
    int n;
    void operator =(MatrixCheck m);
    bool operator ==(MatrixCheck m);
    bool operator !=(MatrixCheck m);
    void set(int a,int b);
};

#endif // MATRIXCHECK_H
