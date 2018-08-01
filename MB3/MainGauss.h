#include <QtWidgets/QApplication>
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
    bool isTrue;
    QList<double> get();
    int size;
    ~MainGauss();
};
