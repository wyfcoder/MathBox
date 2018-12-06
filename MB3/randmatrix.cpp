#include "randmatrix.h"
#include"randcount.h"
RandMatrix::RandMatrix()
{

}

bool RandMatrix::rand(Dealparams p, RandCount &r)
{
    this->r=r;
    if(p.isNull) return false;
    else if(p.types.size()==1)
    {
        if(p.types[0].type!=5) return false;
        else
        {
            new_Matrix.setMN(p.types[0].new_matrix.m,p.types[0].new_matrix.n);
            position=p.types[0].position;
            for(unsigned i=0;i<new_Matrix.m;i++)
                for(unsigned j=0;j<new_Matrix.n;j++)
                {
                    new_Matrix.arrays[i][j]=r.rand();
                    for(unsigned k=0;k<100;k++) r.rand();
                }
            return true;
        }
    }
    else if(p.types.size()==2)
    {
        if(!(p.types[0].type==0||p.types[0].type==1)) return false;
        if(!(p.types[1].type==0||p.types[1].type==1)) return false;
        if(p.types[0].number<1) return false;
        if(p.types[1].number<1) return false;
        new_Matrix.setMN(p.types[0].number,p.types[1].number);
        new_Matrix.name="Result";
        for(unsigned i=0;i<new_Matrix.m;i++)
            for(unsigned j=0;j<new_Matrix.n;j++)
            {
                new_Matrix.arrays[i][j]=r.rand();
                for(unsigned k=0;k<100;k++) r.rand();
            }
        return true;
    }
    else if(p.types.size()==3)
    {
        if(!(p.types[0].type==0||p.types[0].type==1)) return false;
        if(!(p.types[1].type==0||p.types[1].type==1)) return false;
        if(p.types[0].number<1) return false;
        if(p.types[1].number<1) return false;
        if(p.types[2].type!=5) return false;
        new_Matrix.setMN(p.types[0].number,p.types[1].number);
        position=p.types[2].position;
        for(unsigned i=0;i<new_Matrix.m;i++)
            for(unsigned j=0;j<new_Matrix.n;j++)
            {
                new_Matrix.arrays[i][j]=r.rand();
                for(unsigned k=0;k<100;k++) r.rand();
            }
        return  true;
    }
    return false;
}
