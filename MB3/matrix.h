#ifndef MATRIX_H
#define MATRIX_H
#include<QString>
#include<vector>
using namespace std;
class Matrix
{
public:
    Matrix(unsigned a,unsigned b);//构造零矩阵
    Matrix(unsigned a);//构造文件输入型矩阵
    Matrix();
    void zeroMatrix();//零矩阵
    void setMN(unsigned i,unsigned j);
    QString name;
    int times;
    unsigned m,n;//行与列
    vector<vector<double>> arrays;//矩阵的系数
    void operator =(Matrix c);
    bool operator ==(Matrix a);
    //-------------------------------------基本函数
    Matrix T();
    Matrix pow(unsigned times);
    double det();
    double traceOfMatrix();//矩阵求迹
    Matrix upTriangle();//线性变化使矩阵变为上三角矩阵
    Matrix downTriangle();//线性变化为下三角矩阵
    Matrix ladder();//求阶梯矩阵
    Matrix inversofMatrix();//矩阵求逆
    Matrix IMatrix(unsigned n);//返回一个n阶的单位矩阵
    unsigned rankOfMatrix();//求矩阵的秩
    friend  Matrix operator+(Matrix,Matrix);
    friend  Matrix operator*(double,Matrix);
    friend  Matrix operator*(Matrix,double);
    friend  Matrix operator-(Matrix,Matrix);
    friend  Matrix operator*(Matrix,Matrix);
    friend Matrix operator /(Matrix,double);
    //-----------------------------------------------算数函数
};
#endif // MATRIX_H
