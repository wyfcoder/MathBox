#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QToolBar>
#include<QAction>
#include<QFileDialog>
#include<QFile>
#include<QMenu>
#include<QMenuBar>
#include<QToolButton>
#include<QDockWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QTextBrowser>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QWidget>
#include<QLabel>
#include<QTreeView>
#include<QListView>
#include<QFileSystemModel>
#include<QStringList>
#include<QTreeWidget>
#include<QTreeWidgetItem>

#include<vector>
#include<QCompleter>

#include"number.h"
#include"function.h"
#include"matrix.h"
#include"classexplor.h"
#include"randcount.h"
#include"parmtype.h"
#include"dealparams.h"

#include"plot2dwidget.h"
#include"plotpolar.h"
#include"timecountwidget.h"
using namespace  std;
static const int EXIT_CODE_REBOOT = -123456789;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void creatMenus();//创建菜单栏
    void createActions();//创建动作
    void createToolBars();//创建工具栏


    ~MainWindow();
//+++++++++++++++++++++++++++
signals:
    void closeWindow();
    void closePolarWindow();
protected slots:
    void Search();
    void ShowTime();
    void Delete();
    void Paint();
    //*******************
    void ShowHelp(QTreeWidgetItem *item);//对应搜索栏树形结构
    void ShowHelpActionConnect();
    //--------------------
    void change();
    void find();
    //+++++++++++++++
    void close();
    void close2();
private:
    Ui::MainWindow *ui;

    //菜单栏
    QMenu *EditMenu;
    QMenu *PaintMenu;
    QMenu *HelpMenu;

    //工具栏
    QToolBar *MainTool;


    //工具栏动作
    QAction *ShowTimeAction;
    QAction *DeleteAction;
    QAction *PaintAction;
    QAction *HelpAction;

    //搜索窗口的部件
    QDockWidget *SearchDock;
    QLineEdit *SearchLineEdit;
    QPushButton *SearchBtn;
    QGridLayout *SearchMainLayout;
    QWidget *SearchWidget;
    //*********************
    QStringList WordList;
    QCompleter *SearchCompleter;
    QTreeWidget *HelpTree;

    //下列注释为type值
    QTreeWidgetItem *Matrix_TreeItem;
    QTreeWidgetItem *Matrix_Main_TreeItem;//1
    QTreeWidgetItem *Pro_MatrixDet_TreeItem;//2
    QTreeWidgetItem *Pro_MatrixPow_TreeItem;//3
    QTreeWidgetItem *Pro_MatrixtoDownTriangel_TreeItem;//4
    QTreeWidgetItem *Pro_MatrixtoLadder_TreeItem;//5
    QTreeWidgetItem *Pro_MatrixtoUpTriangle_TreeItem;//6
    QTreeWidgetItem *Pro_MatrixTrace_TreeItem;//7
    QTreeWidgetItem *Pro_MatrixTransform_TreeItem;//8

    QTreeWidgetItem *Number_TreeItem;
    QTreeWidgetItem *Number_Main_TreeItem;//9

    QTreeWidgetItem *Function_TreeItem;
    QTreeWidgetItem *Function_Main_TreeItem;//10

    QTreeWidgetItem *Plot2D_TreeItem;
    QTreeWidgetItem *MathBox_Plot_TreeItem;//11
    QTreeWidgetItem *Pro_Plot2D_TreeItem;//12

    QTreeWidgetItem *Rand_TreeItem;
    QTreeWidgetItem *Pro_Rand_TreeItem;//13
    QTreeWidgetItem *Pro_RandMatrix_TreeItem;//14
    QTreeWidgetItem *Pro_RandFunction_TreeItem;//15

    QTreeWidgetItem *Regression_TreeItem;
    QTreeWidgetItem *Pro_Regression_MultipleVirtualsRegression_TreeItem;//16
    QTreeWidgetItem *Pro_Regression_PlecrveRegression_TreeItem;//17
    QTreeWidgetItem *Pro_Regression_UnifiedRegression_TreeItem;//18

    QTreeWidgetItem *Integration_TreeItem;
    QTreeWidgetItem *Pro_IntegrationSolving_GuassFivePoint_TreeItem;//19
    QTreeWidgetItem *Pro_IntegrationSolving_Romberg_TreeItem;//20
    QTreeWidgetItem *Pro_IntegrationSolving_Simpson_TreeItem;//21
    QTreeWidgetItem *Pro_IntegrationSolving_StepSimpson_TreeItem;//22

    QTreeWidgetItem *EquationSolving_TreeItem;
    QTreeWidgetItem *Pro_EquationSolving_TreeItem;//23

    QTreeWidgetItem *LinearEquations_TreeItem;
    QTreeWidgetItem *Pro_LinearDiagonalEquationsSolving_TreeItem;//24
    QTreeWidgetItem *Pro_LinearEquationsSolving_TreeItem;//25
    QTreeWidgetItem *Pro_LinearEquationsSolving_Iteration_TreeItem;//26
    QTreeWidgetItem *Pro_LinearEquationsSolving_MainGuass_TreeItem;//27

    QTreeWidgetItem *Input_and_Output_TreeItem;
    QTreeWidgetItem *Pro_OutputMatrix_TreeItem;//28
    QTreeWidgetItem *Pro_InputMatrix_TreeItem;//29

    QTreeWidgetItem *Normal_Operator_TreeItem;
    QTreeWidgetItem *Pro_SetDigit_TreeItem;//30
    QTreeWidgetItem *Result_TreeItem;//31
    QTreeWidgetItem *Pro_Clear_TreeItem;//32
    QTreeWidgetItem *Pro_Eraser_TreeItem;//33


    //数据情况窗口
    QLabel* dataLabel;

    //主要部分
    QWidget *mainWidget;
    QTextBrowser *coder_paper;
    QLineEdit *input;
    QVBoxLayout *mainLayout;
    QLabel *outputLabel;
    QLabel *inputLabel;
    //******************
    QTextBrowser *AnalyzeBrowser;
    QDockWidget *AnalyzeDock;
    QVBoxLayout *AnalyzeLayout;
    QWidget *AnalyzeWidget;


    //时间显示窗口
    TimeCountWidget* showTime;
    QLabel* timeLabel;

private:
 //-------------------------------------建立窗口的函数
    QVBoxLayout *centerLayout;
    QVBoxLayout *left_layout;
    QVBoxLayout *right_layout;

    void buildCenterWindow();
    void buildLeftWindow();
    void buildRightWindow();
    void buildBottomWindow();
    void buildWindw();
//-------------------------------------------------
     QCompleter* completer;
     ClassExplor* classExplor;
     RandCount randcount;
 //----------------------------------------------------
     QString null;
//-----------------------------------------------------UI
    void setFonts();
    QString redColor(QString);
    QString greenColor(QString);
    QString blueColor(QString);
    QString blackColor(QString);
    QString lightSkyBlue(QString);
    QString lightGreen(QString);
    QString lightGray(QString);

    QString outputNormalColor(QString);
    QString outputNumberColor(QString);
    QString virtualNameColor(QString);
    QString outputClassNameColor(QString);
//------------------------------------------------------
    void initVecor();
    void initProgrameTable();
    vector<QString> classNames;
    vector<QString> programTable;
    QStringList names;
    vector<Number> numbers;
    vector<Matrix> matrixs;
    vector<Function> functions;
//------------------------------------------------------
     void MakeCompleter();
//------------------------------------------------------
     int  check(QString text);
     void dealWrong(int number);
     int  class_mode(QString name);
     bool find_newName(QString name);
//--------------------------------------------------------函数编程
     int getFunctionCode(QString name);
//---------------------------------------------------------UI响应
     void addNewNumber(Number number);
     void rewriteNumber(QString name, double value);
     void rewriteNumber(int position, double value);
     void addNewFunction(Function function);
     void rewriteFunction(QString name,Function new_function);
     void rewriteFunction(int position,Function new_function);
     void addNewMatrix(Matrix matrix);
     void rewriteMatrix(unsigned position,Matrix new_matrix);
     void showMatrix(Matrix m);
 //----------------------------------------------------------测试程序
     void test();
 //----------------------------------------------------------算法函数调用
     int randFunction(Dealparams p);
     int randNumber(Dealparams p);
     int randMatrix(Dealparams p);
     int equationSolving(Dealparams p);
     int integration_simpson(Dealparams p);
     int integration_setpSimpson(Dealparams p);
     int integration_romberg(Dealparams p);
     int integration_gaussFivePoint(Dealparams p);
     //-------------------------------------数值求方程组
     int linearEquationSolving(Dealparams p);
     int linearEquationSolvingW(Dealparams p);//超松弛算法
     int linearEquationDigitalSolving(Dealparams p);//对角阵的解法
     //--------------------------------------------
     int clearWindow(Dealparams p);
     int eraserVirtual(Dealparams p);
     void eraser(int type,int position);

     int matrixTransform(Dealparams p);
     int matrixPow(Dealparams p);
     int matrixTrace(Dealparams p);
     int matrixDet(Dealparams p);
     int matrixRank(Dealparams p);
     int matrixtoLadder(Dealparams p);
     int matrixtoUpTriangle(Dealparams p);
     int matrixtoDownTriangel(Dealparams p);
     //+++++++++++++++++++++++++++++++++++++++
     int plot2d(Dealparams p);
     int plotPolar(Dealparams p);
     bool isPlaceExit;
     bool isPolarExit;
     Plot2DWidget* plotPlace;
     plotpolar*    plot2DPolar;
     //+++++++++++++++++++++++++++++++++++++++
     int matrixOutput(Dealparams p);
     int matrixInput(Dealparams p);
     //++++++++++++++++++++++++++++++++++++++++设置长度
     int setDigit(Dealparams p);
     //++++++++++++++++++++++++++++++++++++++++++拟合算法
     int regressionUnifiedRegression(Dealparams p);
     int regressionPlecrve(Dealparams p);
     int regressionMultipleRegression(Dealparams p);
 //-----------------------------------------------------------result 变量的使用
     bool isCreate;
     int style;
     double valueOfResult;
     Function functionOfResult;
     Matrix matrixOfResult;
     void addNumberResult(double a);
     void addFunctionResult(Function f);
     void addMatrixResult(Matrix m);
     int dealResult(QString text);

  //--------------------------------------------------------------整体性工具代码
     //int window_mode; ----窗口模式
     vector<QString> commandBox;
     vector<QString>::iterator commandPointer;
     void keyPressEvent(QKeyEvent *event);
     void addCommand(QString);//增加一条命令时
     void downOperater();//上一条命令
     void upOperater();//下一条命令
     void addCode();//--------------------------统一添加代码函数
     void addResult(QString s);//------------------------统一结果添加函数
     //计时工具
     long time_start;
     LARGE_INTEGER litmp;
     LONGLONG QPart1,QPart2;
     double dfMinus,dfFreq,dfTim;
     void endTime();
     void startTime();

     //数的保留位数变量
     int saveNumberCount;

     //天线工程应用函数
     int antennaWireSSA(Dealparams p);
     int antennaWireOEA(Dealparams p);
     int antennaWireTEA(Dealparams p);
     int antennaWirePA(Dealparams p);

     //特殊函数
     int specialFunction(Dealparams p,int mode);
     int specialFunction_Besier(Dealparams p);
};
#endif // MAINWINDOW_H
