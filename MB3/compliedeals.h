//编译的一些方法
#include<QString>
#include<QVector>
#include<vector>
#include"number.h"
#include"matrix.h"
using namespace std;
class ComplieDeals
{
public:
    ComplieDeals();
    QVector<QString> className;
    QVector<QString> commands;

    bool isExpression();//检查是否只是一个表达式

    QString checkVirtulName();//检查变量名的合法性

    int getClassMode(QString message);//获得类的种类

    QString setVirtualName();//获取表达式的变量名

    void inputText(QString text);

    QString getName();//获得类名

    bool helpNumberBuilder(vector<Number>);//帮助构建数字类

    void helpCountNumberExpression(QString text);//计算数字表达式
    QString text;
    double value;
    int position;
 //-------------------------------------------------------
    //存储结构
    class C
{
    public:
    int mode;
    /*
    function:4
    number:1
    charNumber:3
    operator:2
    */
    double number;
    int x;
    QChar chars;
    bool isTrue;
};
    class p
{
    public:
    int end;
    bool isOk;
};
    vector<C> saves;
    vector<Number> numbers;
    vector<QString> functionName;
    double saveNumber;
    QString virtualName;
    int virtualPosition;
    bool isExit();
    C returnMode(QChar m);
    bool save();
    bool isOpertate(QChar m);
    bool is_function(QString);
    bool isNumber();


    bool isWrong();//对构建好的数组进行查错
    bool PreNC(C next);
    bool PreFU(C next);
    bool PreOP(C pre,C next);
    bool PowCheck(unsigned& position);

    double counter(unsigned start, unsigned end);//计算数，将检查过的list计算即可
    int blockEnd(unsigned position);//获得一个块的结尾
    int smallBolckEnd(unsigned position, unsigned end);//获取一个最小块的位置

    double counter_bolck(unsigned start,unsigned end);//计算一个块的程序
    double count_smallBlock(unsigned start,unsigned end);//计算一个小小块
    void dealHeader();//对开头的符号进行处理
//----------------------------------------------------------------------
Matrix cMatrix;//保存的矩阵类
vector<Matrix> matrixs;
int helpMatrixBuilder(vector<Matrix> matrixs);//构建矩阵类
bool matrix_exist();
bool getMatrixNumber();
bool dealMatrixExpression();
};
