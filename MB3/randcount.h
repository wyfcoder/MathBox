#ifndef RANDCOUNT_H
#define RANDCOUNT_H


class RandCount
{
public:
    RandCount();
    double rand();
    void setRange(double min,double max);
    unsigned long int M;
    unsigned long int C;
    unsigned long int v;
    unsigned long int x;
    double a=0;
    double b=1;
};

#endif // RANDCOUNT_H
