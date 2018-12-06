#include "linearequationssolving.h"
#include"MainGauss.h"
#include"dealparams.h"
LinearEquationsSolving::LinearEquationsSolving()
{
    isSaved=false;
    isTrue=false;
    position=-1;
}

bool LinearEquationsSolving::solving(Dealparams p)
{
    if(p.isNull) return false;
    if(p.types.size()>3) return false;
    if(p.types.size()==1)
    {
        if(p.types[0].type==5)
        {
            Matrix m=p.types[0].new_matrix;
            if(m.m-m.n==-1)
            {
                MainGauss guass(m);
                if(guass.isTrue)
                {
                    new_matrix=guass.new_matrix;
                    isTrue=true;
                }
                  return true;
            }
        }
    }
    else if(p.types.size()==2)
    {
        if(p.types[0].type==5&&p.types[1].type==5)
        {
            Matrix m=p.types[0].new_matrix;
            isSaved=true;
            if(m.m-m.n==-1)
            {
                MainGauss guass(m);
                if(guass.isTrue)
                {
                    new_matrix=guass.new_matrix;
                    position=p.types[1].position;
                    isTrue=true;
                }
                   return true;
            }
        }
    }
    return false;
}


