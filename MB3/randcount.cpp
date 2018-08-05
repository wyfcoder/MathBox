#include"randcount.h"
#include<time.h>
using namespace std;
RandCount::RandCount()
{
        M = time(0)/100;
        C =M/10;
        v = 40;
        x = M /10;

}
double RandCount::rand()
{
    x = (v*x + C) % M;
    return 1.0*x / M*(b-a)+a;
}

void RandCount::setRange(double min, double max)
{
    a=min;
    b=max;
}



