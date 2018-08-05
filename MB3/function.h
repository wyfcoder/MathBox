#ifndef FUNCTION_H
#define FUNCTION_H
#include<QString>
#include<vector>
using namespace std;
class Function
{
public:
    Function(QString message);
    QString function;
    int virtualSize;
    vector<QString> virtualNames;
    vector<double> virtualValues;
    void setParms(double v);
    void setParms(vector<double> values);
};

#endif // FUNCTION_H
