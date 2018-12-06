#ifndef FUNCTIONCALCULATE_H
#define FUNCTIONCALCULATE_H
#include<vector>
#include"number.h"
#include"function.h"
using namespace std;
class FunctionCalculate
{
public:
    FunctionCalculate(Function f,QString text);
    bool buildCaluclate(vector<Number> numbers);
    double calculate();
    bool isSaved;
    int saved_number;
private:
    vector<double> numbers;
    Function function;
    vector<Number> number_list;
    QString text;
};

#endif // FUNCTIONCALCULATE_H
