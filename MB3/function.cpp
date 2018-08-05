#include "function.h"

Function::Function(QString messages)
{
    this->function=messages;
}

void Function::setParms(double v)
{
    virtualValues[0]=v;
}


void Function::setParms(vector<double> values)
{
    for(int i=0;i<virtualSize;i++)
        virtualValues[i]=values[i];
}
