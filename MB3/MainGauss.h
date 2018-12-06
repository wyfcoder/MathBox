#include <QtWidgets/QApplication>
#include"matrix.h"
class MainGauss
{
private:
    double** a;
    void change(int);
    int  *answer;
    double *n;
	QList<double> answerR;
public:
    MainGauss(int size);
    MainGauss();

    //-----------------------
    MainGauss(Matrix m);
    Matrix new_matrix;

    //-----------------------
    bool isTrue;
    QList<double> get();
    int size;
    ~MainGauss();
};
