#include "functioncalculate.h"
#include"buildhelper.h"
#include<vector>
using namespace std;
FunctionCalculate::FunctionCalculate(Function f,QString text)
{
    function=f;
    this->text=text;
    this->isSaved=false;
    this->saved_number=0;
}

bool FunctionCalculate::buildCaluclate(vector<Number> numbers)
{
    int position=1;
    int dot_count=0;
    QString number_expression="";
    do
    {
        if(text[position]==',')
        {
            number_expression.append(";");
            buildhelper help;
            help.inputText(number_expression);
            if(!help.helpNumberBuilder(numbers)) return false;
            this->numbers.push_back(help.value);
            dot_count++;
            number_expression="";
        }
        else
        {
            number_expression.append(text[position]);
        }
        position++;
    }
        while(position<text.size()-2);

        if(dot_count==function.virtualSize)
        {
            for(unsigned i=0;i<numbers.size();i++)
            {
                if(number_expression==numbers[i].name)
                {
                    this->isSaved=true;
                    saved_number=i;
                }
            }
            if(!isSaved) return false;
            else return true;
        }
        else if(dot_count==function.virtualSize-1)
        {
            number_expression.append(";");
            buildhelper help;
            help.inputText(number_expression);
            if(!help.helpNumberBuilder(numbers)) return false;
            this->numbers.push_back(help.value);
            return true;
        }
        else
        {
            return false;
        }
}

double FunctionCalculate::calculate()
{
    return function.calculate(numbers);
}

