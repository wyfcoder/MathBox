#ifndef STEPSIMPSON_H
#define STEPSIMPSON_H
#include"dealparams.h"
#include"function.h"
using namespace std;
class StepSimpson
{
public:
    StepSimpson();
    int count(Dealparams p);
public:
  double  exp;
  double  start;
  double  end;
  bool    has_save;
  int  save_position;
  bool    isOk;
  double  answer;
  Function f;
private:
  void    simpson();
  int n;
  double  interval,t1,t2,s,s1,dataeps;
};

#endif // STEPSIMPSON_H
