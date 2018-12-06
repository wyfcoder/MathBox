#include"MainGauss.h"
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;

void MainGauss::change(int now)
{
	int k = now;
	int j = now;
	double max = a[now][now];
	for (int i = now; i<size; i++)
		for (int m = now; m<size; m++)
			if (fabs(max) < fabs(a[i][m]))
			{
				max = a[i][m];
				k = i;
				j = m;
			}
	double c;
	if (k != now)
		for (int i = 0; i < size + 1; i++)
		{
			c = a[k][i];
			a[k][i] = a[now][i];
			a[now][i] = c;
		}
	if (j != now)
	{
		for (int i = 0; i < size; i++)
		{
			c = a[i][j];
			a[i][j] = a[i][now];
			a[i][now] = c;
		}
		int c = answer[j];
		answer[j] = answer[now];
		answer[now] = c;
	}
}

QList<double> MainGauss::get()
{
	for (int i = 0; i < size; i++)
	{
		answerR.append(n[i]);
	}
	return answerR;
}

MainGauss::MainGauss(int size)
{
	ifstream in("data.txt");
	if (!in.is_open())
	{
		exit(0);
	}
    isTrue=true;
	this->size = size;
	this->answer = new int[size];
	this->a = new double*[size];
	this->n = new double[size];
    for (int i = 0; i < size; i++)
	{
		a[i] = new double[size + 1];
		answer[i] = i;
	}
	    for (int i = 0; i < size; i++)
		for (int j = 0; j < size + 1; j++)
			in >> a[i][j];
      for (int i = 0; i < size - 1; i++)
	{
        change(i);
		for (int k = i + 1; k < size; k++)
		{
            double rat;
            if(a[i][i]!=0)
             rat= a[k][i] / a[i][i];
            else
            {
                isTrue=false;
                return;
            }
			for (int m = i; m < size + 1; m++)
			{
				a[k][m] -= rat*a[i][m];
			}
		}
	}

	for (int i = size - 1; i >= 0; i--)
	{
		double rat2 = a[i][i];
		for (int k = i; k < size + 1; k++)
		{
            if(rat2!=0)
			a[i][k] /= rat2;
            else
            {
                isTrue=false;
                return;
            }
		}
        for (int m = i + 1; m < size; m++)
        {
            double rat = a[i][m];
            for (int q = m; q < size + 1; q++)
            {
                a[i][q] -= rat*a[m][q];
            }
        }
	}
	for (int l = 0; l < size; l++)
	{
		n[answer[l]] = a[l][size];
	}
}

MainGauss::~MainGauss()
{
	delete[]answer;
	delete[] n;
	for (int i = 0; i < size; i++)
		delete[]a[i];
	delete[]a;
}

MainGauss::MainGauss()
{
    ifstream in("data.txt");
    this->isTrue=true;
    if (!in.is_open())
    {
        exit(0);
    }
    in>>this->size;
    this->answer = new int[size];
    this->a = new double*[size];
    this->n = new double[size];
    for (int i = 0; i < size; i++)
    {
        a[i] = new double[size + 1];
        answer[i] = i;
    }
        for (int i = 0; i < size; i++)
        for (int j = 0; j < size + 1; j++)
            in >> a[i][j];
    for (int i = 0; i < size - 1; i++)
    {
        change(i);
        for (int k = i + 1; k < size; k++)
        {    double rat;
            if(a[i][i]!=0)
             rat = a[k][i] / a[i][i];
            else
            {
                isTrue=false;
                break;
            }
            for (int m = i; m < size + 1; m++)
            {
                a[k][m] -= rat*a[i][m];
            }
        }
    }
    for (int i = size - 1; i >= 0; i--)
    {
        double rat2 = a[i][i];
        for (int k = i; k < size + 1; k++)
        {
            if(rat2!=0)
            a[i][k] /= rat2;
            else
            {
                isTrue=false;
                return;
            }
        }
        for (int m = i + 1; m < size; m++)
        {
            double rat = a[i][m];
            for (int q = m; q < size + 1; q++)
            {
                a[i][q] -= rat*a[m][q];
            }
        }
    }
    for (int l = 0; l < size; l++)
    {
        n[answer[l]] = a[l][size];
    }
}


//------------------------------------------------------------
MainGauss::MainGauss(Matrix m)
{
    size=m.m;
    this->answer = new int[size];
    this->a = new double*[size];
    this->n = new double[size];
    this->isTrue=true;
    for (int i = 0; i < size; i++)
    {
        a[i] = new double[size + 1];
        answer[i] = i;
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size + 1; j++)
           a[i][j]= m.arrays[i][j];
    for (int i = 0; i < size - 1; i++)
    {
        change(i);
        for (int k = i + 1; k < size; k++)
        {
            double rat;
            if(fabs(a[i][i])>0.00000000001)
             rat= a[k][i] / a[i][i];
            else
            {
                isTrue=false;
                return;
            }
            for (int m = i; m < size + 1; m++)
            {
                a[k][m] -= rat*a[i][m];
            }
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        double rat2 = a[i][i];
        for (int k = i; k < size + 1; k++)
        {
            if(fabs(rat2)>0.00000000001)
            a[i][k] /= rat2;
            else
            {
                isTrue=false;
                return;
            }
        }
        for (int m = i + 1; m < size; m++)
        {
            double rat = a[i][m];
            for (int q = m; q < size + 1; q++)
            {
                a[i][q] -= rat*a[m][q];
            }
        }
    }
    new_matrix.setMN(size,1);
    for (int l = 0; l < size; l++)
    {
        new_matrix.arrays[answer[l]][0] = a[l][size];
    }
}
