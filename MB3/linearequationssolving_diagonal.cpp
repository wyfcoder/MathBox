#include "linearequationssolving_diagonal.h"
#include<vector>
Linearequationssolving_diagonal::Linearequationssolving_diagonal(Matrix m)
{
    n.setMN(m.m,1);
    vector<double> b,y;
    b.push_back(m.arrays[0][0]);
    y.push_back(m.arrays[0][m.m]/b[0]);
    for(unsigned i=1;i<m.m;i++)
    {
        b.push_back(m.arrays[i][i]-m.arrays[i][i-1]*m.arrays[i-1][i]/b[i-1]);
        y.push_back((m.arrays[i][m.m]-m.arrays[i][i-1]*y[i-1])/b[i]);
    }
    n.arrays[m.m-1][0]=y[m.m-1];
    for(int i=m.m-2;i>=0;i--)
        n.arrays[i][0]=y[i]-m.arrays[i][i+1]*n.arrays[i+1][0]/b[i];
}
