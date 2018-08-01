#include "matrix.h"
#include"MainGauss.h"
#include"mathi.h"
#include"mi.h"
#include<fstream>
#include<math.h>
#include<fstream>
#include<algorithm>
using namespace std;
Matrix::Matrix(int a,int b)
{
    m=a;
    n=b;
    for(int i=0;i<a;i++)
    {
        vector<double> s;
        arrays.push_back(s);
        for(int k=0;k<b;k++)
        arrays[i].push_back(0);
    }
}

void Matrix::zeroMatrix()
{
    if(arrays.size()!=0)
      arrays.clear();
    for(int i=0;i<m;i++)
    {
        vector<double> s;
        arrays.push_back(s);
        for(int k=0;k<n;k++)
        arrays[i].push_back(0);
    }
}
Matrix::Matrix(int a)
{
    n=a;
}
Matrix::Matrix()
{
    ifstream in("Matrix.txt");
    if (!in.is_open())
    {
        exit(0);
    }
    in>>m;
    in>>n;
    for(int i=0;i<m;i++)
    {
        vector<double> s;
        arrays.push_back(s);
        for(int k=0;k<n;k++)
        {
            double m;
            in>>m;
            arrays[i].push_back(m);
        }
    }
}
Matrix operator +(Matrix a,Matrix b)
{
       for(int i=0;i<a.m;i++)
         for(int k=0;k<a.n;k++)
             a.arrays[i][k]+=b.arrays[i][k];
       return a;
}
Matrix operator -(Matrix a,Matrix b)
{
    for(int i=0;i<a.m;i++)
      for(int k=0;k<a.n;k++)
          a.arrays[i][k]-=b.arrays[i][k];
    return a;
}

Matrix operator *(Matrix a,double b)
{
    for(int i=0;i<a.m;i++)
      for(int k=0;k<a.n;k++)
          a.arrays[i][k]*=b;
    return a;
}

Matrix operator *(double b,Matrix a)
{
    for(int i=0;i<a.m;i++)
      for(int k=0;k<a.n;k++)
          a.arrays[i][k]*=b;
    return a;
}

Matrix operator /(Matrix a,double b)
{
    for(int i=0;i<a.m;i++)
      for(int k=0;k<a.n;k++)
          a.arrays[i][k]/=b;
    return a;
}

Matrix operator *(Matrix a,Matrix b)
{
    Matrix c(a.m,b.n);
    for(int i=0;i<c.m;i++)
    {
        for(int j=0;j<c.n;j++)
        {
            double pluss=0;
            for(int m=0;m<a.n;m++)
            pluss+=a.arrays[i][m]*b.arrays[m][j];
            c.arrays[i][j]=pluss;
        }
    }
    return c;
}

void Matrix::operator =(Matrix c)
{
    this->m=c.m;
    this->n=c.n;
    if(arrays.size()==0)
    {
        for(int i=0;i<m;i++)
        {
            vector<double> s;
            arrays.push_back(s);
            for(int k=0;k<n;k++)
            arrays[i].push_back(c.arrays[i][k]);
        }
    }
    else
    {
        arrays.clear();
        for(int i=0;i<m;i++)
        {
            vector<double> s;
            arrays.push_back(s);
            for(int k=0;k<n;k++)
            arrays[i].push_back(c.arrays[i][k]);
        }
    }
}

bool Matrix::operator ==(Matrix c)
{
    if(this->n!=c.n)
        return false;
    if(this->m!=c.m)
        return false;
    if(QString::compare(this->name,c.name)!=0)
        return false;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(arrays[i][j]!=c.arrays[i][j])
                return false;
    return true;
}

Matrix Matrix::T()
{
    Matrix c(n,m);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            c.arrays[j][i]=arrays[i][j];
    return c;
}

Matrix Matrix::pow(int times)
{
    Matrix d(m,m);
    Matrix p(m,m);
    if(times==0)
    {
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                p.arrays[i][j]=1;
        return p;
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
            d.arrays[i][j]=arrays[i][j];
            p.arrays[i][j]=arrays[i][j];
        }
    for(int i=1;i<times;i++)
    {
        p=p*d;
    }
    return p;
}

double Matrix::traceOfMatrix()
{
        int sum=0;
        for(int i=0;i<m;i++)
            sum+=arrays[i][i];
        return sum;
}

Matrix Matrix::ladder()
{
    Matrix c(m,n);
    c.times=0;
    for(int j=0;j<m;j++)
       {
          for(int i=0;i<n;i++)
          c.arrays[j][i]=arrays[j][i];
    }
    int c1;
    if(m>n)
        c1=n;
    else
        c1=m;
    for(int k=0;k<c1;k++)
    {
        if(k!=n-1)
       {
          int maxM=k;
          int maxN=k;
          for(int j=k;j<m;j++)
        {
          for(int i=k;i<n;i++)
          {
              if(fabs(c.arrays[j][i])>fabs(c.arrays[maxM][maxN]))
              {
                  maxM=j;
                  maxN=i;
              }
          }
        }

        if(maxM!=k||maxN!=k)
        {
            double m1;
            if(maxM!=k)
            {
                c.times++;
            for(int i=0;i<n;i++)
            {
                m1=c.arrays[k][i];
                c.arrays[k][i]=c.arrays[maxM][i];
                c.arrays[maxM][i]=m1;
            }
}
            if(maxN!=k)
            {
                c.times++;
                for(int i=0;i<m;i++)
                {
                    m1=c.arrays[i][k];
                    c.arrays[i][k]=c.arrays[i][maxN];
                    c.arrays[i][maxN]=m1;
                }
            }
        }
        if(c.arrays[k][k]!=0)
        for(int i=k+1;i<m;i++)
        {
            double rat=-c.arrays[i][k]/c.arrays[k][k];
            for(int j=0;j<n;j++)
            {
               c.arrays[i][j]+=c.arrays[k][j]*rat;
            }
        }
        else
        {
            return c;
        }
       }
   }
    return c;
}

Matrix Matrix::downTriangle()
{
    Matrix c(n,n);
    c.times=0;
    for(int j=0;j<n;j++)
       {
          for(int i=0;i<n;i++)
          c.arrays[j][i]=arrays[j][i];
    }
    for(int k=n-1;k>=0;k--)
    {
        if(k!=0)
       {
          int maxM=k;
          int maxN=k;
          for(int j=k;j>=0;j--)
        {
          for(int i=k;i>=0;i--)
          {
              if(fabs(c.arrays[j][i])>fabs(c.arrays[maxM][maxN]))
              {
                  maxM=j;
                  maxN=i;
              }
          }
        }

        if(maxM!=k||maxN!=k)
        {
            double m1;
            if(maxM!=k)
            {
                c.times++;
            for(int i=0;i<n;i++)
            {
                m1=c.arrays[k][i];
                c.arrays[k][i]=c.arrays[maxM][i];
                c.arrays[maxM][i]=m1;
            }
}
            if(maxN!=k)
            {
                c.times++;
                for(int i=0;i<n;i++)
                {
                    m1=c.arrays[i][k];
                    c.arrays[i][k]=c.arrays[i][maxN];
                    c.arrays[i][maxN]=m1;
                }
            }
        }

        if(c.arrays[k][k]!=0)
        for(int i=k-1;i>=0;i--)
        {
            double rat=-c.arrays[i][k]/c.arrays[k][k];
            for(int j=0;j<n;j++)
            {
               c.arrays[i][j]+=c.arrays[k][j]*rat;
            }
        }
        else
        {
            return c;
        }
       }
    }
    return c;
}

Matrix Matrix::upTriangle()
{
    Matrix c=ladder();
    return c;
}

double Matrix::det()
{
    Matrix a=upTriangle();
    double m=1;
    for(int i=0;i<n;i++)
        m*=a.arrays[i][i];
    if(a.times%2!=0)
    {
        m*=-1;
    }
    return m;
}

int Matrix::rankOfMatrix()
{
    Matrix a=ladder();
    int a1=0;
    int n2;
    if(n>m)
        n2=m;
    else
        n2=n;

    for(int i=0;i<n2;i++)
        if(fabs(a.arrays[i][i])>=0.0000000001)
            a1++;
    return a1;
}

Matrix Matrix::inversofMatrix()
{
    vector<vector<double>> matrixs;
    matrixs.resize(n);
    for(int i=0;i<n;i++)
        matrixs[i].resize(2*n);
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<2*n;k++)
        {
            if(k<n)
                matrixs[i][k]=arrays[i][k];
            else
            {
            if(i==k-n)
                matrixs[i][k]=1;
            else
                matrixs[i][k]=0;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        int maxM=i;
        for(int k=i;k<n;k++)
                if(matrixs[k][i]>matrixs[maxM][i])
                    maxM=k;

        if(maxM!=i)
        {
            double cen;
            if(maxM!=i)
            {
                for(int k=0;k<2*n;k++)
                {
                    cen=matrixs[i][k];
                    matrixs[i][k]=matrixs[maxM][k];
                    matrixs[maxM][k]=cen;
                }
            }
        }
        double rat=matrixs[i][i];
        for(int k=i;k<2*n;k++)
        {
            matrixs[i][k]/=rat;
        }

        if(i<n-1)
        {
            for(int j=i+1;j<n;j++)
            {
                double rat=-matrixs[j][i];
                for(int k=i;k<2*n;k++)
                {
                      matrixs[j][k]+=rat*matrixs[i][k];
                }
            }
        }
    }
    for(int i=n-1;i>=0;i--)
    {
        if(i==n-1)
            continue;
        else
        {
            for(int j=n-1;j!=i;j--)
            {
                double rat=-matrixs[i][j]/matrixs[j][j];
                for(int m=0;m<2*n;m++)
                    matrixs[i][m]+=rat*matrixs[j][m];
            }
        }
    }
    Matrix c(n,n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            c.arrays[i][j]=matrixs[i][j+n];
    return c;
}

Matrix Matrix::IMatrix(int n)
{
    Matrix i(n,n);
    for(int j=0;j<n;j++)
        i.arrays[j][j]=1;
    return i;
}



