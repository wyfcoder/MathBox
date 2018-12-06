#include "number.h"
Number::Number(double a, QString n)
{
    this->value=a;
    this->name=n;
}

Number::Number()
{
    this->name="";
    this->value=0;
}
