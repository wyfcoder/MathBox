#include "mainwindow.h"
#include<QStringListModel>
#include<QKeyEvent>
#include<windows.h>
#include<time.h>
#include<fstream>
#include<QSpacerItem>
#include"mucic.h"
#include "ui_mainwindow.h"
#include"buildhelper.h"
#include"functionbuildhelper.h"
#include"matrixbuilderhelper.h"
#include"functioncalculate.h"
#include"dealparams.h"
#include"parmtype.h"
#include"functionprogram.h"
#include"showhelpdoc.h"
#include"plot2dwidget.h"
#include"plotpolar.h"
#include"timecountwidget.h"
#include"equationsolving.h"
#include"stepsimpson.h"
#include"integrationsolving_simpson.h"
#include"integrationsolving_romberg.h"
#include"integrationguassfivepoint.h"
#include"randmatrix.h"
#include"linearequationssolving.h"
#include"linearequationssolving_iterationw.h"
#include"linearequationssolving_diagonal.h"
#include"regressionunified.h"
#include"regressionplecrvefitting.h"
#include"regressionmultiple.h"
#include"project_Antennawire_ssa.h"
#include"project_Antennawire_oea.h"
#include"project_Antennawire_pa.h"
#include"project_Antennawire_tea.h"

#include"specialfunction_hermite.h"
#include"specialfunction_legendre.h"
#include"specialfunction_bezier.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this ->setWindowTitle("MathBox");
    this->setMinimumSize(900,600);
    this -> setWindowIcon(QPixmap(":/picture/mathbox1.png"));

    createActions();
    creatMenus();
    createToolBars();
    mainWidget = new QWidget;
    buildCenterWindow();
    buildLeftWindow();
    buildRightWindow();
    buildBottomWindow();
    buildWindw();

//-----------------------------------------------------------------------------
     null="NULL";
     for(int i=0;i<100;i++)
     randcount.rand();
     initVecor();
     initProgrameTable();
     AnalyzeBrowser ->append(greenColor(">>Welecome to MathBox."));
     AnalyzeBrowser->append("");
     MakeCompleter();
     connect(input,SIGNAL(returnPressed()),this,SLOT(change()));
     connect(input,SIGNAL(textChanged(QString)),this,SLOT(find()));
     isCreate=false;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     setFonts();
     isPlaceExit=false;
     saveNumberCount=3;
//-----------------------------------------------------------------------------
    // Music m;
}

void MainWindow::test()
{
    FunctionProgram program;
    program.RandFunction(3);
    program.RandFunction(2);
    program.RandFunction(5);
    program.RandFunction(3);
    program.RandFunction(4);
    program.RandFunction(2);
    program.RandFunction(10);
    program.RandFunction(50);


     QueryPerformanceFrequency(&litmp);
     //   获得计数器的时钟频率
     dfFreq=(double)litmp.QuadPart;

     QueryPerformanceCounter(&litmp);
     //   获得初始值
     QPart1=litmp.QuadPart;

     QueryPerformanceCounter(&litmp);
     //   获得终止值
     QPart2=litmp.QuadPart;
     dfMinus=(double)(QPart2-QPart1);
     dfTim=dfMinus/dfFreq;
     //   获得对应的时间值
    return;
}

void MainWindow::buildCenterWindow()
{
    input = new QLineEdit(mainWidget);
    coder_paper = new QTextBrowser(mainWidget);
    inputLabel = new QLabel("Input:",mainWidget);
    outputLabel = new QLabel("CodePaper:",mainWidget);
    centerLayout=new QVBoxLayout;
    centerLayout->addWidget(outputLabel);
    centerLayout->addWidget(coder_paper);
    centerLayout->addWidget(inputLabel);
    centerLayout->addWidget(input);
}

void MainWindow::buildLeftWindow()
{
    SearchDock = new QDockWidget("Search");
    SearchDock ->setMinimumSize(200,300);
    SearchDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
    SearchWidget = new QWidget;
    SearchLineEdit = new QLineEdit(SearchWidget);
    SearchLineEdit ->setPlaceholderText("Please input...");
    WordList <<"Matrix_Main"
             <<"Pro_MatrixDet"
             <<"Pro_MatrixPow"
             <<"Pro_MatrixtoDownTriangel"
             <<"Pro_MatrixtoLadder"
             <<"Pro_MatrixtoUpTriangle"
             <<"Pro_MatrixTrace"
             <<"Pro_MatrixTransform"

             <<"Number_Main"

             <<"Function_Main"

             <<"MathBox_Plot"
             <<"Pro_Plot2D"

             <<"Pro_Rand"
             <<"Pro_Plot2D"
             <<"Pro_RandMatrix"
             <<"Pro_RandFunction"

             <<"Pro_Regression_MultipleVirtualsRegression"
             <<"Pro_Regression_PlecrveRegression"
             <<"Pro_Regression_UnifiedRegression "

             <<"Pro_IntegrationSolving_GuassFivePoint"
             <<"Pro_IntegrationSolving_Romberg"
             <<"Pro_IntegrationSolving_Simpson"
             <<"Pro_IntegrationSolving_StepSimpson"

             <<"Pro_EquationSolving"

             <<"Pro_LinearDiagonalEquationsSolving"
             <<"Pro_LinearEquationsSolving"
             <<"Pro_LinearEquationsSolving_Iteration"
             <<"Pro_LinearEquationsSolving_MainGuass"

             <<"Pro_OutputMatrix"
             <<"Pro_InputMatrix"

             <<"Pro_SetDigit"
             <<"Result"
             <<"Pro_Clear"
             <<"Pro_Eraser";




    SearchCompleter = new QCompleter(WordList,this);
    SearchLineEdit ->setCompleter(SearchCompleter);
    SearchBtn = new QPushButton("Search",SearchWidget);
    connect(SearchBtn,SIGNAL(clicked(bool)),this,SLOT(Search()));
    //******************************************************************
    HelpTree = new QTreeWidget(SearchWidget);
    HelpTree ->setHeaderLabel("Help");

    Matrix_TreeItem = new QTreeWidgetItem(HelpTree);
    Matrix_TreeItem ->setText(0,"Matrix");
    Matrix_Main_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,1) ;//1
    Matrix_Main_TreeItem ->setText(0,"Matrix_Main");
    Pro_MatrixDet_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,2);//2
    Pro_MatrixDet_TreeItem ->setText(0,"Pro_MatrixDet");
    Pro_MatrixPow_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,3);//3
    Pro_MatrixPow_TreeItem ->setText(0,"Pro_MatrixPow");
    Pro_MatrixtoDownTriangel_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,4);//4
    Pro_MatrixtoDownTriangel_TreeItem ->setText(0,"Pro_MatrixtoDownTriangel");
    Pro_MatrixtoLadder_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,5) ;//5
    Pro_MatrixtoLadder_TreeItem ->setText(0,"Pro_MatrixtoLadder");
    Pro_MatrixtoUpTriangle_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,6) ;//6
    Pro_MatrixtoUpTriangle_TreeItem ->setText(0,"Pro_MatrixtoUpTriangle");
    Pro_MatrixTrace_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,7) ;//7
    Pro_MatrixTrace_TreeItem ->setText(0,"Pro_MatrixTrace");
    Pro_MatrixTransform_TreeItem = new QTreeWidgetItem(Matrix_TreeItem,8) ;//8
    Pro_MatrixTransform_TreeItem ->setText(0,"Pro_MatrixTransform");


    Number_TreeItem = new QTreeWidgetItem(HelpTree);
    Number_TreeItem ->setText(0,"Number");
    Number_Main_TreeItem = new QTreeWidgetItem(Number_TreeItem,9);//9
    Number_Main_TreeItem ->setText(0,"Number_Main");

    Function_TreeItem= new QTreeWidgetItem(HelpTree);
    Function_TreeItem ->setText(0,"Function");
    Function_Main_TreeItem= new QTreeWidgetItem(Function_TreeItem,10);//10
    Function_Main_TreeItem ->setText(0,"Function_Main");

    Plot2D_TreeItem= new QTreeWidgetItem(HelpTree);
    Plot2D_TreeItem ->setText(0,"Plot2D");
    MathBox_Plot_TreeItem= new QTreeWidgetItem(Plot2D_TreeItem,11);//11
    MathBox_Plot_TreeItem ->setText(0,"MathBox_Plot");
    Pro_Plot2D_TreeItem= new QTreeWidgetItem(Plot2D_TreeItem,12);//12
    Pro_Plot2D_TreeItem ->setText(0,"Pro_Plot2D");

    Rand_TreeItem = new QTreeWidgetItem(HelpTree);
    Rand_TreeItem ->setText(0,"Rand");
    Pro_Rand_TreeItem = new QTreeWidgetItem(Rand_TreeItem,13);//13
    Pro_Rand_TreeItem ->setText(0,"Pro_Rand");
    Pro_RandMatrix_TreeItem = new QTreeWidgetItem(Rand_TreeItem,14);//14
    Pro_RandMatrix_TreeItem ->setText(0,"Pro_RandMatrix");
    Pro_RandFunction_TreeItem = new QTreeWidgetItem(Rand_TreeItem,15);//15
    Pro_RandFunction_TreeItem->setText(0,"Pro_RandFunction");

    Regression_TreeItem = new QTreeWidgetItem(HelpTree);
    Regression_TreeItem ->setText(0,"Regression");
    Pro_Regression_MultipleVirtualsRegression_TreeItem = new QTreeWidgetItem(Regression_TreeItem,16);//16
    Pro_Regression_MultipleVirtualsRegression_TreeItem ->setText(0,"Pro_Regression_MultipleVirtualsRegression");
    Pro_Regression_PlecrveRegression_TreeItem = new QTreeWidgetItem(Regression_TreeItem,17);//17
    Pro_Regression_PlecrveRegression_TreeItem ->setText(0,"Pro_Regression_PlecrveRegression");
    Pro_Regression_UnifiedRegression_TreeItem = new QTreeWidgetItem(Regression_TreeItem,18);//18
    Pro_Regression_UnifiedRegression_TreeItem ->setText(0,"Pro_Regression_UnifiedRegression");

    Integration_TreeItem = new QTreeWidgetItem(HelpTree);
    Integration_TreeItem ->setText(0,"Integration");
    Pro_IntegrationSolving_GuassFivePoint_TreeItem = new QTreeWidgetItem(Integration_TreeItem,19);//19
    Pro_IntegrationSolving_GuassFivePoint_TreeItem ->setText(0,"Pro_IntegrationSolving_GuassFivePoint");
    Pro_IntegrationSolving_Romberg_TreeItem = new QTreeWidgetItem(Integration_TreeItem,20);//20
    Pro_IntegrationSolving_Romberg_TreeItem ->setText(0,"Pro_IntegrationSolving_Romberg");
    Pro_IntegrationSolving_Simpson_TreeItem = new QTreeWidgetItem(Integration_TreeItem,21);//21
    Pro_IntegrationSolving_Simpson_TreeItem ->setText(0,"Pro_IntegrationSolving_Simpson");
    Pro_IntegrationSolving_StepSimpson_TreeItem = new QTreeWidgetItem(Integration_TreeItem,22);//22
    Pro_IntegrationSolving_StepSimpson_TreeItem ->setText(0,"Pro_IntegrationSolving_StepSimpson");


    EquationSolving_TreeItem = new QTreeWidgetItem(HelpTree);
    EquationSolving_TreeItem ->setText(0,"EquationSolving");
    Pro_EquationSolving_TreeItem = new QTreeWidgetItem(EquationSolving_TreeItem,23);//23
    Pro_EquationSolving_TreeItem ->setText(0,"Pro_EquationSolving");

    LinearEquations_TreeItem = new QTreeWidgetItem(HelpTree);
    LinearEquations_TreeItem ->setText(0,"LinearEquations");
    Pro_LinearDiagonalEquationsSolving_TreeItem = new QTreeWidgetItem(LinearEquations_TreeItem,24);//24
    Pro_LinearDiagonalEquationsSolving_TreeItem ->setText(0,"Pro_LinearDiagonalEquationsSolving");
    Pro_LinearEquationsSolving_TreeItem = new QTreeWidgetItem(LinearEquations_TreeItem,25);//25
    Pro_LinearEquationsSolving_TreeItem ->setText(0,"Pro_LinearEquationsSolving");
    Pro_LinearEquationsSolving_Iteration_TreeItem = new QTreeWidgetItem(LinearEquations_TreeItem,26);//26
    Pro_LinearEquationsSolving_Iteration_TreeItem ->setText(0,"Pro_LinearEquationsSolving_Iteration");
    Pro_LinearEquationsSolving_MainGuass_TreeItem = new QTreeWidgetItem(LinearEquations_TreeItem,27);//27
    Pro_LinearEquationsSolving_MainGuass_TreeItem ->setText(0,"Pro_LinearEquationsSolving_MainGuass");

    Input_and_Output_TreeItem = new QTreeWidgetItem(HelpTree);
    Input_and_Output_TreeItem ->setText(0,"Input_and_Output");
    Pro_OutputMatrix_TreeItem = new QTreeWidgetItem(Input_and_Output_TreeItem,28);//28
    Pro_OutputMatrix_TreeItem ->setText(0,"Pro_OutputMatrix");
    Pro_InputMatrix_TreeItem = new QTreeWidgetItem(Input_and_Output_TreeItem,29);//29
    Pro_InputMatrix_TreeItem ->setText(0,"Pro_InputMatrix");

    Normal_Operator_TreeItem = new QTreeWidgetItem(HelpTree);
    Normal_Operator_TreeItem ->setText(0,"Normal_Operator");
    Pro_SetDigit_TreeItem = new QTreeWidgetItem(Normal_Operator_TreeItem,30);//30
    Pro_SetDigit_TreeItem ->setText(0,"Pro_SetDigit");
    Result_TreeItem = new QTreeWidgetItem(Normal_Operator_TreeItem,31);//31
    Result_TreeItem ->setText(0,"Result");
    Pro_Clear_TreeItem = new QTreeWidgetItem(Normal_Operator_TreeItem,32);//32
    Pro_Clear_TreeItem ->setText(0,"Pro_Clear");
    Pro_Eraser_TreeItem = new QTreeWidgetItem(Normal_Operator_TreeItem,33);//33
    Pro_Eraser_TreeItem ->setText(0,"Pro_Eraser");

    connect(HelpTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(ShowHelp(QTreeWidgetItem*)));

    left_layout=new QVBoxLayout;
    SearchMainLayout = new QGridLayout(SearchWidget);
    SearchMainLayout ->addWidget(SearchLineEdit,0,0);
    SearchMainLayout ->addWidget(SearchBtn,0,1);
    SearchMainLayout ->addWidget(HelpTree,1,0,1,2);
    SearchDock ->setWidget(SearchWidget);
    SearchWidget ->setLayout(SearchMainLayout);
    left_layout->addWidget(SearchWidget);
}

void MainWindow::buildRightWindow()
{
    right_layout=new QVBoxLayout;
    timeLabel=new QLabel("Time Analyze");
    showTime=new TimeCountWidget;
    dataLabel=new QLabel("Data");
    classExplor=new ClassExplor(this);
    right_layout->addWidget(dataLabel);
    right_layout->addWidget(classExplor);
    right_layout->addWidget(timeLabel);
    right_layout->addWidget(showTime);
}

void MainWindow::buildBottomWindow()
{
    //分析窗部分
    AnalyzeDock = new QDockWidget("Output",this);
    AnalyzeDock ->setMaximumHeight(150);
    AnalyzeDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
    AnalyzeWidget = new QWidget(AnalyzeDock);
    AnalyzeLayout = new QVBoxLayout(AnalyzeDock);
    AnalyzeBrowser = new QTextBrowser(mainWidget);
    AnalyzeLayout ->addWidget(AnalyzeBrowser);
    AnalyzeWidget ->setLayout(AnalyzeLayout);
    AnalyzeDock ->setWidget(AnalyzeWidget);
}

void MainWindow::buildWindw()
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(left_layout);
    mainLayout->addLayout(centerLayout);
    mainLayout->addLayout(right_layout);
    mainWidget ->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea,AnalyzeDock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{

    ShowTimeAction = new QAction(QIcon(":/picture/time.png"),("ShowTime"),this);
    ShowTimeAction ->setStatusTip("ShowTime");
    connect(ShowTimeAction,SIGNAL(triggered(bool)),this,SLOT(ShowTime()));

    DeleteAction = new QAction(QIcon(":/picture/delete2.png"),("Delete"),this);
    DeleteAction ->setStatusTip("Delete Input Show");
    connect(DeleteAction,SIGNAL(triggered(bool)),this,SLOT(Delete()));

    PaintAction = new QAction(QIcon(":/picture/plot.png"),("Paint"),this);
    PaintAction ->setStatusTip("Paint Data Line");
    connect(PaintAction,SIGNAL(triggered(bool)),this,SLOT(Paint()));

    HelpAction = new QAction(QIcon(":/picture/file.png"),("Help"),this);
    HelpAction ->setStatusTip("Help");
    connect(HelpAction,SIGNAL(triggered(bool)),this,SLOT(ShowHelpActionConnect()));

}
void MainWindow::creatMenus()
{
    EditMenu = menuBar()->addMenu("Edit");
    EditMenu->addAction(DeleteAction);

    PaintMenu =menuBar()->addMenu("Paint");
    PaintMenu->addAction(PaintAction);

    HelpMenu = menuBar()->addMenu("Help");
    HelpMenu ->addAction(HelpAction);

}

void MainWindow::createToolBars()
{
    //工具栏
    MainTool = addToolBar("Tool");
    MainTool ->addAction(ShowTimeAction);
    MainTool ->addAction(DeleteAction);
    MainTool ->addAction(PaintAction);
    MainTool ->addAction(HelpAction);
}

void MainWindow::Search()
{
    QString tr = SearchLineEdit->text();
    int type = 0;
    if(tr == "Matrix_Main") type = 1;
    if(tr == "Pro_MatrixDet") type = 2;
    if(tr == "Pro_MatrixPow") type = 3;
    if(tr == "Pro_MatrixtoDownTriangel") type = 4;
    if(tr == "Pro_MatrixtoLadder") type = 5;
    if(tr == "Pro_MatrixtoUpTriangle") type = 6;
    if(tr == "Pro_MatrixTrace") type = 7;
    if(tr == "Pro_MatrixTransform") type = 8;
    if(tr == "Number_Main") type = 9;
    if(tr == "Function_Main") type = 10;
    if(tr == "athBox_Plot") type = 11;
    if(tr == "Pro_Plot2D") type = 12;
    if(tr == "Pro_Rand") type = 13;
    if(tr == "Pro_RandMatrix") type = 14;
    if(tr == "Pro_RandFunction") type = 15;
    if(tr == "Pro_Regression_MultipleVirtualsRegression") type = 16;
    if(tr == "Pro_Regression_PlecrveRegression") type = 17;
    if(tr == "Pro_Regression_UnifiedRegression") type = 18;
    if(tr == "Pro_IntegrationSolving_GuassFivePoint") type = 19;
    if(tr == "Pro_IntegrationSolving_Romberg") type = 20;
    if(tr == "Pro_IntegrationSolving_Simpson") type = 21;
    if(tr == "Pro_IntegrationSolving_StepSimpson") type = 22;
    if(tr == "Pro_EquationSolving") type = 23;
    if(tr == "Pro_LinearDiagonalEquationsSolving") type = 24;
    if(tr == "Pro_LinearEquationsSolving") type = 25;
    if(tr == "Pro_LinearEquationsSolving_Iteration") type = 26;
    if(tr == "Pro_LinearEquationsSolving_MainGuass") type = 27;
    if(tr == "Pro_OutputMatrix") type = 28;
    if(tr == "Pro_InputMatrix") type = 29;
    if(tr == "Pro_SetDigit") type = 30;
    if(tr == "Result") type = 31;
    if(tr == "Pro_Clear") type = 32;
    if(tr == "Pro_Eraser") type = 33;

    if(type!=0)
    {
        ShowHelpDoc *d = new ShowHelpDoc;
        d->i = type;
        d->ShowFile(d->i,d->text);
        d->show();
    }
    else
    {
        QMessageBox::information(this,("Warn"),("The file is not exist."));
    }

}
void MainWindow::ShowHelp(QTreeWidgetItem *item)
{
    int a;
    a = item->type();
    if(!a)
        return;

    ShowHelpDoc *d = new ShowHelpDoc;
    d->i = item->type();
    d->ShowFile(d->i,d->text);
    d->show();
}
void MainWindow::ShowHelpActionConnect()
{
    ShowHelpDoc* d=new ShowHelpDoc();
    d->show();
}
void MainWindow::ShowTime()
{
    TimeCountWidget* t=new TimeCountWidget();
    t->show();
    t->addData(10);
    t->addData(12);
    t->addData(7);
    t->addData(20);
    t->addData(17);
    t->addData(13);
}
void MainWindow::Delete()
{
    AnalyzeBrowser->setPlainText("");
}
void MainWindow::Paint()
{
    Plot2DWidget * drawer=new Plot2DWidget();
    drawer->show();
}

//----------------------------------------------------------------
void MainWindow::initVecor()
{
    classNames.push_back("Matrix");//0
    classNames.push_back("Number");//1
    classNames.push_back("Function");//2
}

void MainWindow::initProgrameTable()
{
    programTable.push_back("Pro_Rand");//随机数
    programTable.push_back("Pro_RandFunction");//随机方程
    //+++++++++++++++++++++++++++++++++++++
    programTable.push_back("Pro_Plot2D");//绘图指令
    programTable.push_back("Pro_EquationSolving");//求解非线性方程的指令
    programTable.push_back("Pro_IntegrationSolving_StepSimpson");//求积分的算法
    programTable.push_back("Pro_IntegrationSolving_Simpson");
    programTable.push_back("Pro_IntegrationSolving_Romberg");
    programTable.push_back("Pro_IntegrationSolving_GuassFivePoint");
    programTable.push_back("Pro_RandMatrix");//随机矩阵

    //线性方程组求解
    programTable.push_back("Pro_LinearEquationsSolving_MainGuass");

    //内存清除指令
    programTable.push_back("Pro_Clear");
    programTable.push_back("Pro_Eraser");

    //矩阵基础方法
    programTable.push_back("Pro_MatrixTransform");
    programTable.push_back("Pro_MatrixPow");
    programTable.push_back("Pro_MatrixTrace");
    programTable.push_back("Pro_MatrixDet");
    programTable.push_back("Pro_MatrixRank");
    programTable.push_back("Pro_MatrixtoLadder");
    programTable.push_back("Pro_MatrixtoUpTriangle");
    programTable.push_back("Pro_MatrixtoDownTriangel");

    //输入输出方法
    programTable.push_back("Pro_OutputMatrix");
    programTable.push_back("Pro_InputMatrix");

    //数位转换方法
    programTable.push_back("Pro_SetDigit");

    //回归算法
    programTable.push_back("Pro_Regression_UnifiedRegression");//一元回归
    programTable.push_back("Pro_Regression_PlecrveRegression");//多项式回归
    programTable.push_back("Pro_Regression_MultipleVirtualsRegression");//多元回归

    //线性方程的迭代法
    programTable.push_back("Pro_LinearEquationsSolving_Iteration");
    programTable.push_back("Pro_LinearDiagonalEquationsSolving");

    //工程应用方法

    //天线方法
    //天线均匀直线阵列方向图
    programTable.push_back("Pro_AntennaWire_SSA");//边射阵
    programTable.push_back("Pro_AntennaWire_OEA");//原端阵
    programTable.push_back("Pro_AntennaWire_TEA");//强端阵
    programTable.push_back("Pro_AntennaWire_PA");//相控阵

    //特殊函数方法
     //厄米多项式
    programTable.push_back("Pro_SpecialFunction_Herimit");
    programTable.push_back("Pro_SpecialFunction_Legendre");
    programTable.push_back("Pro_SpecialFunction_Bezier");

    //特殊图形绘制
    //极坐标
    programTable.push_back("Pro_PlotPolar");
}

void MainWindow::setFonts()
{
    SearchLineEdit->setFont(QFont( "新宋体" , 8 ,  QFont::Normal));
    coder_paper->setFont(QFont( "Nirmala UI" , 8 ,  QFont::Normal));
    AnalyzeBrowser->setFont(QFont( "Nirmala UI" ,8,  QFont::Normal));
    outputLabel->setFont(QFont( "新宋体" , 8 ,  QFont::Normal));
    input->setFont(QFont( "Nirmala UI" , 8 ,  QFont::Normal));
    inputLabel->setFont(QFont( "新宋体" , 8 ,  QFont::Normal));
    timeLabel->setFont(QFont( "新宋体" , 8 ,  QFont::Normal));
    dataLabel->setFont(QFont( "新宋体" , 8 ,  QFont::Normal));
}


QString MainWindow::greenColor(QString s)
{
    return QObject::tr("<font color=green>%1</font>").arg(s);
}

QString MainWindow::redColor(QString s)
{
    return QObject::tr("<font color=red>%1</font>").arg(s);
}

QString MainWindow::blueColor(QString s)
{
    return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::blackColor(QString s)
{
    return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::lightSkyBlue(QString s)
{
          return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::lightGreen(QString s)
{
          return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::lightGray(QString s)
{
    return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::outputNormalColor(QString s)
{
    return QObject::tr("<font color=green>%1</font>").arg(s);
}

QString MainWindow::outputClassNameColor(QString s)
{
     return QObject::tr("<font color=green>%1</font>").arg(s);
}

QString MainWindow::outputNumberColor(QString s)
{
    return QObject::tr("<font color=blue>%1</font>").arg(s);
}

QString MainWindow::virtualNameColor(QString s)
{
     return QObject::tr("<font color=yellow>%1</font>").arg(s);
}

void MainWindow::MakeCompleter()
{
    names<<"Matrix"<<"Function";
    names<<"Number";
    names<<"Pro_";
    names<<"Result";
    names<<"Result->";
    names<<"Pro_Rand(Number save)";
    names<<"Pro_Rand()";
    names<<"Pro_RandFunction(Number virtualSize)";
    names<<"Pro_RandFunction(Number virtualSize,Function save)";
    names<<"Pro_Plot2D()";
    names<<"Pro_Plot2D(Function f)";
    names<<"Pro_Plot2D(Function f,Number min,Number max)";
    names<<"Pro_Plot2D(Matrix m)";
    names<<"Pro_EquationSolving(Function f)";
    names<<"Pro_EquationSolving(Function f,Number saved)";
    names<<"Pro_EquationSolving(Function f,Number start,Number end)";
    names<<"Pro_EquationSolving(Function f,Number start,Number end,Number save)";
    names<<"Pro_IntegrationSolving_StepSimpson(Function f,Number start,Number end)";
    names<<"Pro_IntegrationSolving_StepSimpson(Function f,Number start,Number end,Number save)";
    names<<"Pro_IntegrationSolving_Simpson(Function f,Number start,Number end)";
    names<<"Pro_IntegrationSolving_Simpson(Function f,Number start,Number end,Number saved)";
    names<<"Pro_IntegrationSolving_Romberg(Function f,Number start,Number end)";
    names<<"Pro_IntegrationSolving_Romberg(Function f,Number start,Number end,Number saved)";
    names<<"Pro_IntegrationSolving_GuassFivePoint(Function f,Number start,Number end)";
    names<<"Pro_IntegrationSolving_GuassFivePoint(Function f,Number start,Number end,Number saved)";
    names<<"Pro_RandMatrix(Matrix saved)";
    names<<"Pro_RandMatrix(Number m,Number n)";
    names<<"Pro_RandMatrix(Number m,Number n,Matrix saved)";
    names<<"Pro_LinearEquationsSolving_MainGuass(Matrix m)";
    names<<"Pro_LinearEquationsSolving_MainGuass(Matrix m,Matrix save)";
    names<<"Pro_LinearDiagonalEquationsSolving(Matrix m)";
    names<<"Pro_LinearDiagonalEquationsSolving(Matrix m,Matrix save)";
    names<<"Pro_LinearEquationsSolving_Iteration(Matrix m)";
    names<<"Pro_LinearEquationsSolving_Iteration(Matrix m,Number w)";
    names<<"Pro_LinearEquationsSolving_Iteration(Matrix m,Number w,Matrix save)";
    names<<"Pro_LinearEquationsSolving_Iteration(Matrix m,Number w,Number exp,Number n)";
    names<<"Pro_LinearEquationsSolving_Iteration(Matrix m,Number w,Number exp,Number n,Matrix save)";
    names<<"Pro_Clear()";
    names<<"Pro_Eraser(Virtual virtual)";
    names<<"Pro_MatrixTransform(Matrix m)";
    names<<"Pro_MatrixTransform(Matrix m,Matrix save)";
    names<<"Pro_MatrixPow(Matrix m,Number n)";
    names<<"Pro_MatrixPow(Matrix m,Number n,Matrix save)";
    names<<"Pro_MatrixTrace(Martrix m)";
    names<<"Pro_MatrixTrace(Matrix n,Number save)";
    names<<"Pro_MatrixDet(Matrix m)";
    names<<"Pro_MatrixDet(Matrix m,Number n)";
    names<<"Pro_MatrixRank(Matrix m)";
    names<<"Pro_MatrixRank(Matrix m,Number n)";
    names<<"Pro_MatrixtoLadder(Matrix m)";
    names<<"Pro_MatrixtoLadder(Matrix m,Matrix save)";
    names<<"Pro_MatrixtoUpTriangle(Matrix m)";
    names<<"Pro_MatrixtoUpTriangle(Matrix m,Matrix save)";
    names<<"Pro_MatrixtoDownTriangel(Matrix m)";
    names<<"Pro_MatrixtoDownTriangel(Matrix m,Matrix save)";
    names<<"Pro_OutputMatrix(Matrix m)";
    names<<"Pro_InputMatrix(Matrix m,Number a)";
    names<<"Pro_SetDigit(Number a)";
    names<<"Pro_Regression_UnifiedRegression(Number ID,Matrix data)";
    names<<"Pro_Regression_UnifiedRegression(Number ID,Matrix data,Function save)";
    names<<"Pro_Regression_PlecrveRegression(Number times,Matrix data)";
    names<<"Pro_Regression_PlecrveRegression(Number times,Matrix data,Function save)";
    names<<"Pro_Regression_MultipleVirtualsRegression(Matrix data)";
    names<<"Pro_Regression_MultipleVirtualsRegression(Matrix data,Function save)";
    names<<"Pro_AntennaWire_SSA(Number k,Number d,Number n)";
    names<<"Pro_AntennaWire_SSA(Number k,Number d,Number n,Matrix saved)";
    names<<"Pro_AntennaWire_OEA(Number k,Number d,Number n)";
    names<<"Pro_AntennaWire_OEA(Number k,Number d,Number n,Matrix saved)";
    names<<"Pro_AntennaWire_TEA(Number k,Number d,Number n)";
    names<<"Pro_AntennaWire_TEA(Number k,Number d,Number n,Matrix saved)";
    names<<"Pro_AntennaWire_PA(Number k,Number d,Number n,Number theta)";
    names<<"Pro_AntennaWire_PA(Number k,Number d,Number n,Number theta,Matrix saved)";
    names<<"Pro_SpecialFunction_Herimit(Number n,Number min,Number max,Matrix save)";
    names<<"Pro_SpecialFunction_Herimit(Number n,Number min,Number max,Number dx,Matrix save)";
    names<<"Pro_SpecialFunction_Legendre(Number n,Number min,Number max,Matrix save)";
    names<<"Pro_SpecialFunction_Legendre(Number n,Number min,Number max,Number dx,Matrix save)";
    names<<"Pro_SpecialFunction_Bezier(Number n,Number min,Number max,Matrix save)";
    names<<"Pro_SpecialFunction_Bezier(Number n,Number min,Number max,Number dx,Matrix save)";
    names<<"Pro_PlotPolar()";
    names<<"Pro_PlotPolar(Function f)";
    names<<"Pro_PlotPolar(Function f,Number start,Number end)";
    names<<"Pro_PlotPolar(Matrix datas)";
    completer=new QCompleter();
    completer->setFilterMode(Qt::MatchStartsWith);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    QStringListModel* listModel=new QStringListModel(names,this);
    completer->setModel(listModel);
    input->setCompleter(completer);
}

void MainWindow::change()
{
    QString text=input->text();
    if(text[text.size()-1]==';')
    {
         int rb=check(text);
         switch (rb)
         {
         case 0:
         {
             input->setText("");
             endTime();
             coder_paper->append(blackColor(text));
             coder_paper->append("");
         }
             break;
         default:
             dealWrong(rb);
             break;
         }
    }
}

void MainWindow::find()
{

}

void MainWindow::dealWrong(int number)
{
        switch (number)
     {
        case 1:
            AnalyzeBrowser->append(redColor(">>Undefinded Class!"));
            break;
        case 2:
            AnalyzeBrowser->append(redColor(">>Undefined variable name!"));
            break;
        case 3:
            AnalyzeBrowser->append(redColor(">>Not suitable for Matrix's style!"));
            break;
         case -1:
            AnalyzeBrowser->append(redColor(">>Fail to open file!"));
            break;
         case 4:
            AnalyzeBrowser->append(redColor(">>Matrix expression is wrong!"));
            break;
         case 5:
            AnalyzeBrowser->append(redColor(">>The command is wrong!"));
            break;
         case 6:
            AnalyzeBrowser->append(redColor(">>The matrix is singular!"));
            break;
          case 7:
            AnalyzeBrowser->append(redColor(">>Not suitable for Number's style!"));
            break;
         case 8:
            AnalyzeBrowser->append(redColor(">>Expression is not allowed."));
            break;
         case 9:
             AnalyzeBrowser->append(redColor(">>Not suitable for Function style."));
             break;
         case 10:
            AnalyzeBrowser->append(redColor(">>The name is used."));
            break;
         case 11:
            AnalyzeBrowser->append(redColor(">>Unkown expression."));
            break;
        case 12:
            AnalyzeBrowser->append(redColor(">>The Programe's params are wrong."));
            break;
        case 13:
            AnalyzeBrowser->append(redColor(">>The Pro is not exit"));
            break;
        case 14:
            AnalyzeBrowser->append(redColor(">>Can't solve this problem."));
            break;
        case 15:
            AnalyzeBrowser->append(redColor(">>The changing matrix is not a square matrix."));
            break;
        case 16:
            AnalyzeBrowser->append(redColor(">>The file's data is wrong ."));
            break;
        case 17:
            AnalyzeBrowser->append(redColor(">>The Number is not suitable for it ."));
            break;
        case 18:
            AnalyzeBrowser->append(redColor(">>The Matrix'n is not 2 ."));
            break;
       case 19:
            AnalyzeBrowser->append(redColor(">>The regression is failed."));
            break;
       case 20:
            AnalyzeBrowser->append(redColor(">>The data is not enough."));
            break;
         case 21:
            AnalyzeBrowser->append(redColor(">>The input matrix is not diagonal matrix."));
            break;
       }
        AnalyzeBrowser->append(" ");
    }

int MainWindow::check(QString text)
{
    startTime();
    if(text.size()<2)
    {
        return 5;
    }
    else
    {
          commandBox.push_back(text);
          commandPointer=commandBox.end()-1;
          buildhelper helper;
          if(text[0]=='N'||text[0]=='F'||text[0]=='M')//新变量
        {
               int mode=helper.getClassMode(text);
               if(mode==-1) return 1;
               QString name=helper.checkVirtulName();
               if(QString::compare(name,null)==0) return 2;
               if(find_newName(name)) return 10;
               switch (mode)
              {
               case 0:
               {
                   MatrixBuilderHelper helper;
                   if(!helper.helpBuildMatrix(text,name,numbers,matrixs))
                       return 3;
                   else
                   {
                       Matrix m=helper.newMatrix;
                       addNewMatrix(m);
                   }
               }
                   break;
                case 1:
                   if(!helper.helpNumberBuilder(numbers))
                       return 7;
                   else
                   {
                       Number newNumber(helper.value,name);
                       addNewNumber(newNumber);
                   }
                   break;
                case 2:
               {
                   FunctionBuildHelper function_helper(text);
                   if(!function_helper.helperBuilderFunction(functions))
                       return 9;
                   else
                   {
                       Function f=function_helper.new_function;
                       addNewFunction(f);
                   }
               }
                   break;
               default:
                   break;
               }
        }
          else if(text[0]=='R')//变量
          {
             return dealResult(text);
          }
          else if(text[0]=='P'&&text[1]=='r') //过程
        {
            QString program;
            int i=0;
            for(;i<text.size();i++)
            {
               if(text[i]=='(')
                   break;
               program.append(text[i]);
            }
            int code=getFunctionCode(program);
            if(code==-1)
            {
                return 5;
            }
            if(text[text.size()-2]!=')')
            {
                return 5;
            }
            i++;
            QString parms="";
            while(i<text.size()-1)
            {
                parms.append(text[i]);
                i++;
            }
            Dealparams p(parms,numbers,functions,matrixs);
            if(!(p.isTrue)) return 12;

            switch (code)
           {
            case 0://单个参数的情况
            {
               return randNumber(p);
            }
                break;
            case 1:
            {
                return randFunction(p);
            }
             break;
            case 2:
            {
                return plot2d(p);
            }
                break;
            case 3:
            {
               return equationSolving(p);
            }
                break;
            case 4:
            {
               return integration_setpSimpson(p);
            }
                break;
            case 5:
            {
               return integration_simpson(p);
            }
                break;
            case 6:
            {
                return integration_romberg(p);
            }
                break;
            case 7:
            {
                return integration_gaussFivePoint(p);
            }
                break;
            case 8:
            {
                return randMatrix(p);
            }
            case 9:
            {
                return linearEquationSolving(p);
            }
            case 10:
            {
                return clearWindow(p);
            }
            case 11:
            {
                return eraserVirtual(p);
            }
            case 12:
            {
                return matrixTransform(p);
            }
            case 13:
            {
                return matrixPow(p);
            }
            case 14:
            {
                return matrixTrace(p);
            }
            case 15:
            {
                return matrixDet(p);
            }
            case 16:
            {
                return matrixRank(p);
            }
            case 17:
            {
                return matrixtoLadder(p);
            }
            case 18:
            {
                return matrixtoUpTriangle(p);
            }
            case 19:
            {
                return matrixtoDownTriangel(p);
            }
            case 20:
            {
                return matrixOutput(p);
            }
            case 21:
            {
                return matrixInput(p);
            }
            case 22:
            {
                return setDigit(p);
            }
            case 23:
            {
                return regressionUnifiedRegression(p);
            }
            case 24:
            {
                return regressionPlecrve(p);
            }
            case 25:
            {
                return regressionMultipleRegression(p);
            }
            case 26:
            {
                return linearEquationSolvingW(p);
            }
            case 27:
            {
                return linearEquationDigitalSolving(p);
            }
            case 28:
            {
                return antennaWireSSA(p);
            }
            case 29:
            {
                return antennaWireOEA(p);
            }
            case 30:
            {
                return antennaWireTEA(p);
            }
            case 31:
            {
                return antennaWirePA(p);
            }
            case 32:
            {
                return specialFunction(p,0);
            }
            case 33:
            {
                return specialFunction(p,1);
            }
            case 34:
            {
                return  specialFunction(p,2);
            }
            case 35:
            {
                return plotPolar(p);
            }
            default:
            {
                return antennaWireSSA(p);
            }
                break;
           }
        }
          else if(text[0]>='a'&&text[0]<='z') //赋值或表达式
        {
            helper.inputText(text);
            QString name=helper.checkVirtulName();
            if(QString::compare(name,null)==0) return 2;
            int mode=class_mode(name);
            if(mode==-1) return 2;
            switch (mode)
           {
            case 0:
           {
                QString message="";
                bool isVirtule=false;
                unsigned position=0;
                if(text[helper.position]=='=')
                {
                    for(unsigned i=0;i<matrixs.size();i++)
                        if(matrixs[i].name==name)
                        {
                            position=i;
                        }
                    for (unsigned i=helper.position+1;i<text.size();i++)
                    {
                        message.append(text[i]);
                    }
                    isVirtule=true;
                }
                else
                {
                    message=text;
                }
                MatrixBuilderHelper helper;
                if(!helper.helpBuildExpression(message,numbers,matrixs)) return 4;
                if(!isVirtule)
                {
                    Matrix m=helper.newMatrix;
                    addMatrixResult(m);
                }
                else
                {
                    rewriteMatrix(position,helper.newMatrix);
                }
            }
                break;
             case 1:
                if(!helper.helpNumberBuilder(numbers))
                    return 7;
                if(helper.isExpresson)
                {
                    addNumberResult(helper.value);
                }
                else
                {
                    rewriteNumber(name,helper.value);
                }
                break;
            case 2:
            {
                if(text[helper.position]!='(')
              {
               FunctionBuildHelper funHelper(text);
               if(!funHelper.dealFunctionExpression(functions))
               {
                   return 9;
               }
               else
               {
                   if(funHelper.is_expression)
                   {
                         addFunctionResult(funHelper.new_function);
                   }
                   else
                   {
                       rewriteFunction(name,funHelper.new_function);
                   }
               }
               }
               else
               {
                    QString message="";
                    for(int i=helper.position;i<text.size();i++)
                        message.append(text[i]);
                    Function f;
                    for(unsigned i=0;i<functions.size();i++)
                        if(name==functions[i].virtualName)
                            f=functions[i];

                    FunctionCalculate calculate(f,message);

                    if(!calculate.buildCaluclate(numbers)) return 9;
                    double result=calculate.calculate();
                    addNumberResult(result);
                    addResult(outputNormalColor(">>The function's value is "+outputNumberColor(QString::number(result,10,saveNumberCount))));
                    if(calculate.isSaved)
                    {
                         rewriteNumber(numbers[calculate.saved_number].name,result);
                    }
               }
            }
                break;
            default:
                break;
            }
        }
          else   //对表达式的处理
       {
            QString name;
            bool isLogicalExpression=false;
            bool isFunctionExpression=false;
            bool isMatrixExpression=false;
            //bool isValuation=false;
            int mode;
            /*int position=0;
            if(text[0]>='a'&&text[0]<='z')
            {
                for(;position<text.size();position++)
                {
                    if(!((text[position]>='a'&&text[position]<='z')||(text[position]>='0'&&text[position]<='9')||text[position]=='_'))
                    {
                        break;
                    }
                    else
                    {
                        name.append(text[position]);
                        position++;
                    }
                }
                if(position==text.size())
                {
                    switch(mode)
                    {
                      case 1:

                        break;
                      case 0:

                        break;
                    case 2:

                        break;
                    default:
                        return 2;
                    }
                }
                else if()
            }*/
            for(int i=0;i<text.size();i++)
            {
                if(text[i]>='A'&&text[i]<='Z')
                {
                    do
                    {
                        i++;
                    }
                       while(i<text.size()&&text[i]!='(');
                }
                if(text[i]>='a'&&text[i]<='z')
                {
                    do
                    {
                        if(!((text[i]>='a'&&text[i]<='z')||(text[i]>='0'&&text[i]<='9')||text[i]=='_'))
                        {
                            break;
                        }
                        else
                        {
                            name.append(text[i]);
                            i++;
                        }
                    }
                        while(i<text.size());
                        mode=class_mode(name);
                        if(mode==0)
                        {
                            if(text[i]!='[')
                           {
                                isMatrixExpression=true;
                                break;
                           }
                            //预编译把内容替换结果
                        }
                        else if(mode==2)
                        {
                            if(text[i]!='(')
                           {
                                isFunctionExpression=true;
                                break;
                           }
                            //预编译计算出函数的值替代结果
                        }
                        break;
                }
                if(text[i]=='&'||text[i]=='|'||text[i]=='!'||text[i]=='>'||text[i]=='<'||text[i]=='=')
                {
                    isLogicalExpression=true;
                    break;
                }
            }
            if(isFunctionExpression)
            {
                FunctionBuildHelper funHelper(text);
                if(!funHelper.dealFunctionExpression(functions))
                {
                    return 9;
                }
                else
                {
                    addFunctionResult(funHelper.new_function);
                }
            }
            else if(isMatrixExpression)
            {
                MatrixBuilderHelper helper;
                if(!helper.helpBuildExpression(text,numbers,matrixs)) return 4;
                addMatrixResult(helper.newMatrix);
            }
            else if(isLogicalExpression)
            {

            }
            else
            {
                helper.inputText(text);
                if(!helper.helpNumberBuilder(numbers)) return 7;
                addNumberResult(helper.value);
            }

            }
    }
    return 0;
}

int MainWindow::class_mode(QString name)
{
    for(unsigned i=0;i<numbers.size();i++)
    {
        if(name==numbers[i].name)
            return 1;
    }

    for(unsigned i=0;i<matrixs.size();i++)
    {
        if(name==matrixs[i].name)
            return 0;
    }

    for(unsigned i=0;i<functions.size();i++)
        if(name==functions[i].virtualName)
            return 2;

    return -1;
}

bool MainWindow::find_newName(QString name)
{
    for(unsigned i=0;i<numbers.size();i++)
        if(numbers[i].name==name) return true;
    for(unsigned i=0;i<functions.size();i++)
        if(functions[i].virtualName==name)return true;
    for(unsigned i=0;i<matrixs.size();i++)
        if(matrixs[i].name==name) return true;
    return false;
}


//---------------------------------------------------------函数响应
int MainWindow::getFunctionCode(QString name)
{
    int code=-1;
    for(unsigned i=0;i<programTable.size();i++)
        if(name==programTable[i])
        {
            code=i;
            break;
        }
    return code;
}
//----------------------------------------------------------UI响应
void MainWindow::showMatrix(Matrix m)
{
    QString s="";
    addResult(outputNormalColor(">> ")+outputNormalColor(m.name+"="));
    unsigned l=0;
    for(unsigned i=0;i<m.m;i++)
    {
        if(l>800)
        {
          s="...";
          AnalyzeBrowser->append(s);
          s="";
          for(unsigned j=0;j<m.n;j++)
          {
              s.append(outputNumberColor(QString::number(m.arrays[m.m-1][j],10,saveNumberCount)));
              s.append(" ");
          }
          AnalyzeBrowser->append(s);
          break;
        }
        s="";
        for(unsigned j=0;j<m.n;j++)
        {
            s.append(outputNumberColor(QString::number(m.arrays[i][j],10,saveNumberCount)));
            s.append(" ");
            l++;
        }
        AnalyzeBrowser->append(s);
    }
    AnalyzeBrowser->append("");
}

void MainWindow::addNewNumber(Number number)
{
    numbers.push_back(number);
    addResult(outputNormalColor(">>New Number."));
    addResult(outputNormalColor(">> "+number.name+"=")+outputNumberColor(QString::number(number.value,10,saveNumberCount)));
    classExplor->addNumberTableItem(number);
}

void MainWindow::rewriteNumber(QString name, double value)
{
    for(unsigned i=0;i<numbers.size();i++)
    {
        if(numbers[i].name==name)
        {
            numbers[i].value=value;
            addResult(outputNormalColor(">>Rewrite Number."));
            addResult(outputNormalColor(">> "+name+"=")+outputNumberColor(QString::number(value,10,saveNumberCount)));
            classExplor->changeTableItem(numbers[i]);
        }
    }
}

void MainWindow::rewriteNumber(int position, double value)
{
    numbers[position].value=value;
    addResult(outputNormalColor(">>Rewrite Number."));
    addResult(outputNormalColor(">> "+(numbers[position].name)+"=")+outputNumberColor(QString::number(value,10,saveNumberCount)));
    classExplor->changeTableItem(numbers[position]);
}

void MainWindow::addNewFunction(Function function)
{
     functions.push_back(function);
     addResult(outputNormalColor(">>New Function."));
     addResult(outputNormalColor(">> "+function.virtualName+"=")+outputNumberColor(function.function));
     classExplor->addFunctiontableItem(function);
}

void MainWindow::rewriteFunction(QString name, Function new_function)
{
    for(unsigned i=0;i<functions.size();i++)
    {
        if(functions[i].virtualName==name)
        {
            new_function.virtualName=name;
            functions[i]=new_function;
            addResult(outputNormalColor(">>Rewrite Function."));
            addResult(outputNormalColor(">> "+name+"="+outputNumberColor(new_function.function)));
            classExplor->changeTableItem(new_function);
        }
    }
}

void MainWindow::rewriteFunction(int position, Function new_function)
{
    new_function.virtualName=functions[position].virtualName;
    functions[position]=new_function;
    addResult(outputNormalColor(">>Rewrite Function."));
    addResult(outputNormalColor(">> "+functions[position].virtualName+"="+outputNumberColor(new_function.function)));
    classExplor->changeTableItem(new_function);
}

void MainWindow::addNewMatrix(Matrix m)
 {
     matrixs.push_back(m);
     addResult(outputNormalColor(">>New Matrix."));
     showMatrix(m);
     classExplor->addMatrixtableItem(m);
 }

void MainWindow::rewriteMatrix(unsigned position,Matrix new_matrix)
{
    QString name=matrixs[position].name;
    matrixs[position]=new_matrix;
    matrixs[position].name=name;
    addResult(outputNormalColor(">>Rewrite Matrix."));
    showMatrix(matrixs[position]);
    classExplor->changeTableItem(matrixs[position]);
}
 //------------------------------------------------------------函数调用
int MainWindow::randFunction(Dealparams p)
{
    FunctionProgram programe;
   if(p.types.size()==1)
   {
       Function f;
       int size;
       if(p.types[0].type==0)
       {
           size=p.types[0].number;
       }
       else if(p.types[0].type==1)
       {
           size=numbers[p.types[0].position].value;
       }
       else
       {
           return 12;
       }
       if(size<=0) return 12;
       else
       {
           Function f=programe.RandFunction(size);
           addFunctionResult(f);
           addResult(outputNormalColor(">>The result is ")+outputNumberColor(f.function));
       }
   }
   else if(p.types.size()==2)
   {
       int size;
       if(p.types[0].type==0)
       {
           size=p.types[0].number;
       }
       else if(p.types[0].type==1)
       {
           size=numbers[p.types[0].position].value;
       }
       else
      {
        return 12;
      }
       if(size<=0) return 12;
       if(p.types[1].type==3)
       {
           rewriteFunction(p.types[1].position,programe.RandFunction(size));
       }
       else
       {
           return 12;
       }
   }
   else
   {
       return 12;
   }
   return 0;
}

int MainWindow::randNumber(Dealparams p)
{
    double r=randcount.rand();
    if(p.types.size()>1) return 12;
    else if(p.isNull)
    {
        addNumberResult(r);
        addResult(outputNormalColor(">>Rand a number: ")+outputNumberColor(QString::number(r,10,saveNumberCount)));
    }
    else
    {
        if(p.types[0].type!=1) return 12;
        else
        {
            rewriteNumber(p.types[0].position,r);
        }
    }
    return 0;
}

int MainWindow::randMatrix(Dealparams p)
{
   RandMatrix r;
   if(!r.rand(p,randcount)) return 12;
   else
   {
       if(r.new_Matrix.name=="Result")
       {
           addMatrixResult(r.new_Matrix);
       }
       else
       {
           rewriteMatrix(r.position,r.new_Matrix);
       }
   }
   return 0;
}

int MainWindow::plot2d(Dealparams p)
{
    if(p.types.size()>3) return 12;
    if(p.isNull)
    {
        if(!isPlaceExit)
        {
            plotPlace=new Plot2DWidget();
            isPlaceExit=true;
            connect(plotPlace,SIGNAL(closeWindow()),this,SLOT(close()));
            plotPlace->show();
            addResult(outputNormalColor(">>Open a new canvas."));
        }
        else
        {
            plotPlace->clearGraph();
            addResult(outputNormalColor(">>Cleare the canvas."));
        }
    }
    else if(p.types.size()==1)
    {
        if(p.types[0].type!=3&&p.types[0].type!=4&&p.types[0].type!=5) return 12;
            if(p.types[0].type==3)
            {
                Function f=functions[p.types[0].position];
                if(f.virtualNames.size()>1) return 12;
            }
            else
            {
                if(p.types[0].new_matrix.n!=2) return 12;
            }
            if(!isPlaceExit)
            {
                plotPlace=new Plot2DWidget();
                isPlaceExit=true;
                connect(plotPlace,SIGNAL(closeWindow()),this,SLOT(close()));
                plotPlace->show();
                addResult(outputNormalColor(">>Open a new canvas."));
            }
            if(p.types[0].type==3)
           {
                Function f=functions[p.types[0].position];
                plotPlace->plotGraph(f,-10,10);
           }
            else
            {
                if(p.types[0].type==5)
                plotPlace->plorGraph2(matrixs[p.types[0].position]);
                else
                plotPlace->plorGraph2(p.types[0].new_matrix);
            }
            addResult(outputNormalColor(">>draw a new graph."));
        }
    else if(p.types.size()==3)
    {
         if(p.types[0].type!=3) return 12;
         Function f=functions[p.types[0].position];
         if(f.virtualNames.size()>1) return 12;
         if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
         double min=p.types[1].number;
         if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
         double max=p.types[2].number;
         if(!isPlaceExit)
         {
             plotPlace=new Plot2DWidget();
             isPlaceExit=true;
             connect(plotPlace,SIGNAL(closeWindow()),this,SLOT(close()));
             plotPlace->show();
             addResult(outputNormalColor(">>Open a new canvas."));
         }
         plotPlace->plotGraph(f,min,max);
         addResult(outputNormalColor(">>draw a new graph."));
    }
    else
    {
        return 12;
    }
    return 0;
}
/*names<<"Pro_PlotPolar()";
names<<"Pro_PlotPolar(Function f)";
names<<"Pro_PlotPolar(Function f,Number start,Number end)";
names<<"Pro_PlotPolar(Matrix datas)";*/
int MainWindow::plotPolar(Dealparams p)
{
   if(p.isNull)
   {
       plot2DPolar=new plotpolar();
       plot2DPolar->show();
       connect(plot2DPolar,SIGNAL(closePolarWindow()),this,SLOT(close2()));
       isPolarExit=true;
       addResult(outputNormalColor(">>Open a new canvas."));
   }
   else
   {
       vector<double> x;
       vector<double> y;
       if(p.types.size()==1)
       {
           if(p.types[0].type==3)
           {
               if(p.types[0].new_function.virtualNames.size()>1) return 12;
               double m=-3.1415926;
               while(m<3.1415926)
               {
                   vector<double> v2;
                   v2.push_back(m);
                   x.push_back(m*180.0/3.1415926);
                   y.push_back(p.types[0].new_function.calculate(v2));
                   m+=0.01;
               }
           }
           else if(p.types[0].type==5)
           {
               if(p.types[0].new_matrix.n!=2) return 12;
               Matrix data=matrixs[p.types[0].position];
               for(unsigned i=0;i<data.m;i++)
               {
                   x.push_back(data.arrays[i][0]);
                   y.push_back(data.arrays[i][1]);
               }
           }
           else
           {
               return 12;
           }
       }
       else if(p.types.size()==3)
       {
           if(p.types[0].type==3)
           {
               if((p.types[1].type==0||p.types[1].type==1)&&(p.types[2].type==1||p.types[2].type==0))
               {
                   double min=p.types[1].number;
                   double max=p.types[2].number;
                   double m=min;
                   if(min>=max) return 12;
                   while(m<max)
                   {
                       vector<double> v2;
                       v2.push_back(m);
                       x.push_back(m*180.0/3.1415926);
                       y.push_back(p.types[0].new_function.calculate(v2));
                       m+=0.01;
                   }
               }
               else return 12;
           }
           else return 12;
       }
       else
       {
           return 12;
       }
       if(isPolarExit)
       {
           plot2DPolar->plot(x,y,"new_data");
           addResult(outputNormalColor(">>new polar graph!"));
       }
       else
       {
           plot2DPolar=new plotpolar();
           plot2DPolar->show();
           connect(plot2DPolar,SIGNAL(closePolarWindow()),this,SLOT(close2()));
           plot2DPolar->plot(x,y,"new_data");
           addResult(outputNormalColor(">>Open a new canvas."));
           addResult(outputNormalColor(">>new polar graph!"));
           isPolarExit=true;
       }
   }
   return 0;
}
//--------------------------------------------------------------------------------------------------Continue
int MainWindow::equationSolving(Dealparams p)
{
    EquationSolving solve;
    int code=solve.count(p);
    if(code!=0) return code;
    else
    {
        if(solve.isOk)
        {
            addResult(outputNormalColor(">>Solve the equation, the answer is ")+outputNumberColor(QString::number(solve.answer,10,saveNumberCount)));
            if(solve.has_save)
            {
               rewriteNumber(solve.save_position,solve.answer);
            }
            else
            {
                addNumberResult(solve.answer);
            }
        }
        else
        {
            addResult(redColor("Can solve the problem."));
        }
    }
    return 0;
}

int MainWindow::integration_simpson(Dealparams p)
{
    IntegrationSolving_Simpson simpson;
    int code=simpson.count(p);
    if(code!=0) return code;
    else
    {
        addResult(outputNormalColor(">>Solve the integration, the answer is ")+outputNumberColor(QString::number(simpson.integration,10,saveNumberCount)));
        if(simpson.has_save)
        {
           rewriteNumber(simpson.save_position,simpson.integration);
        }
        else
        {
            addNumberResult(simpson.integration);
        }
    }
    return 0;
}

int MainWindow::integration_setpSimpson(Dealparams p)
{
    StepSimpson stepSimpson;
    int code=stepSimpson.count(p);
    if(code!=0) return code;
    else
    {
        if(stepSimpson.isOk)
        {
            addResult(outputNormalColor(">>Solve the integration, the answer is ")+outputNumberColor(QString::number(stepSimpson.answer,10,saveNumberCount)));
            if(stepSimpson.has_save)
            {
               rewriteNumber(stepSimpson.save_position,stepSimpson.answer);
            }
            else
            {
                addNumberResult(stepSimpson.answer);
            }
        }
        else
        {
            addResult(redColor(">>Can't solve this problem."));
        }
    }
    return 0;
}

int MainWindow::integration_romberg(Dealparams p)
{
    IntegrationSolving_Romberg romberg;
    int code=romberg.count(p);
    if(code!=0) return code;
    else
    {
        if(romberg.isOk)
        {
            addResult(outputNormalColor(">>Solve the integration, the answer is ")+outputNumberColor(QString::number(romberg.integration,10,saveNumberCount)));
            if(romberg.has_save)
            {
               rewriteNumber(romberg.save_position,romberg.integration);
            }
            else
            {
                addNumberResult(romberg.integration);
            }
        }
        else
        {
            addResult(redColor(">>Can't solve this problem."));
        }
    }
    return 0;
}

int MainWindow::integration_gaussFivePoint(Dealparams p)
{
    IntegrationGuassFivePoint guass;
    int code=guass.count(p);
    if(code!=0) return code;
    else
    {
         addResult(outputNormalColor(">>Solve the integration, the answer is ")+outputNumberColor(QString::number(guass.integration,10,saveNumberCount)));
        if(guass.has_save)
        {
           rewriteNumber(guass.save_position,guass.integration);
        }
        else
        {
            addNumberResult(guass.integration);
        }
    }
    return 0;
}

int MainWindow::linearEquationSolving(Dealparams p)
{
    LinearEquationsSolving solve;
    if(!solve.solving(p)) return 12;
    if(!solve.isTrue) return 14;
    if(solve.isSaved)
    {
      rewriteMatrix(solve.position,solve.new_matrix);
    }
    else
    {
        addMatrixResult(solve.new_matrix);
    }
    return 0;
}

int MainWindow::linearEquationSolvingW(Dealparams p)
{
    if(p.isNull) return 12;
    int size=p.types.size();
    if(size==1)
    {
        if(p.types[0].type!=4&&p.types[0].type!=5) return 12;
        linearequationssolving_iterationW l(p.types[0].new_matrix,1,0.00000001,10000);
        if(!l.isOk) return 14;
        addMatrixResult(l.answer);
        return  0;
    }
    else if(size==2)
    {
        if((p.types[0].type!=4&&p.types[0].type!=5)&&(p.types[1].type!=0&&p.types[1].type!=1)) return 12;
        linearequationssolving_iterationW l(p.types[0].new_matrix,p.types[1].number,0.00000001,10000);
        if(!l.isOk) return 14;
        addMatrixResult(l.answer);
        return  0;
    }
    else if(size==3)
    {
        if((p.types[0].type!=4&&p.types[0].type!=5)&&(p.types[1].type!=0&&p.types[1].type!=1)&&(p.types[2].type!=3)) return 12;
        linearequationssolving_iterationW l(p.types[0].new_matrix,p.types[1].number,0.00000001,10000);
        if(!l.isOk) return 14;
        rewriteMatrix(p.types[2].position,l.answer);
        return  0;
    }
    else if(size==4)
    {
        if((p.types[0].type!=4&&p.types[0].type!=5)&&(p.types[1].type!=0&&p.types[1].type!=1)&&(p.types[2].type!=0&&p.types[2].type!=1)&&(p.types[3].type!=0&&p.types[3].type!=1)) return 12;
        linearequationssolving_iterationW l(p.types[0].new_matrix,p.types[1].number,p.types[2].number,p.types[3].number);
        if(!l.isOk) return 14;
        addMatrixResult(l.answer);
        return  0;
    }
    else if(size==5)
    {
        if((p.types[0].type!=4&&p.types[0].type!=5)&&(p.types[1].type!=0&&p.types[1].type!=1)&&(p.types[2].type!=0&&p.types[2].type!=1)&&(p.types[3].type!=0&&p.types[3].type!=1)&&(p.types[4].type!=3)) return 12;
        linearequationssolving_iterationW l(p.types[0].new_matrix,p.types[1].number,p.types[2].number,p.types[3].number);
        if(!l.isOk) return 14;
        rewriteMatrix(p.types[4].position,l.answer);
        return  0;
    }
    return  12;
}

int MainWindow::linearEquationDigitalSolving(Dealparams p)
{
    int size=p.types.size();
    if(size==1||size==2)
    {
        if(p.types[0].type==4||p.types[0].type==5)
        {
           for(int i=0;i<p.types[0].new_matrix.m;i++)
           {
               int k=i-2;
               if(k>=0)
               {
                   while (k<i-1)
                   {
                       if(fabs(p.types[0].new_matrix.arrays[i][k]-0)>10e-20)
                       {
                           return 21;
                       }
                          k++;
                   }
               }
               k=i+2;
               if(k+2<p.types[0].new_matrix.m)
               {
                   if(fabs(p.types[0].new_matrix.arrays[i][k]-0)>10e-20)
                   {
                       return 21;
                   }
                      k++;
               }
           }
           Linearequationssolving_diagonal digital(p.types[0].new_matrix);
           if(size==1)
           {
               addMatrixResult(digital.n);
           }
           else
           {
               if(p.types[1].type==5)
               {
                   rewriteMatrix(p.types[1].position,digital.n);
               }
           }
           return 0;
        }
    }
    return 12;
}

int MainWindow::matrixtoDownTriangel(Dealparams p)
{
    if(p.isNull) return 12;
    if(p.types.size()==1)
   {
        if(p.types[0].type==5)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addMatrixResult(matrixs[p.types[0].position].downTriangle());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addMatrixResult(p.types[0].new_matrix.downTriangle());
            return 0;
        }
   }
   else if(p.types.size()==2)
   {
        if(p.types[1].type==5)
        {
            if(p.types[0].type==5)
            {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteMatrix(p.types[1].position,matrixs[p.types[0].position].downTriangle());
            return 0;
            }
            else if(p.types[0].type==4)
            {
                if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
                rewriteMatrix(p.types[1].position,p.types[0].new_matrix.downTriangle());
                return 0;
            }
        }
   }
   return 12;
}

int MainWindow::matrixtoUpTriangle(Dealparams p)
{
    if(p.isNull) return 12;
    if(p.types.size()==1)
   {
        if(p.types[0].type==5)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addMatrixResult(matrixs[p.types[0].position].upTriangle());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addMatrixResult(p.types[0].new_matrix.upTriangle());
            return 0;
        }
   }
   else if(p.types.size()==2)
   {
        if(p.types[1].type==5)
        {
            if(p.types[0].type==5)
            {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteMatrix(p.types[1].position,matrixs[p.types[0].position].upTriangle());
            return 0;
            }
            else if(p.types[0].type==4)
            {
                if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
                rewriteMatrix(p.types[1].position,p.types[0].new_matrix.upTriangle());
                return 0;
            }
        }
   }
   return 12;
}

int MainWindow::matrixtoLadder(Dealparams p)
{
    if(p.isNull) return 12;
    if(p.types.size()==1)
   {
        if(p.types[0].type==5)
        {
            addMatrixResult(matrixs[p.types[0].position].ladder());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            addMatrixResult(p.types[0].new_matrix.ladder());
            return 0;
        }
   }
   else if(p.types.size()==2)
   {
        if(p.types[1].type==5)
        {
            if(p.types[0].type==5)
            {
            rewriteMatrix(p.types[1].position,matrixs[p.types[0].position].ladder());
            return 0;
            }
            else if(p.types[0].type==4)
            {
                rewriteMatrix(p.types[1].position,p.types[0].new_matrix.ladder());
                return 0;
            }
        }
   }
   return 12;
}

int MainWindow::matrixRank(Dealparams p)
{
    if(p.isNull) return 12;

    if(p.types.size()==1)
    {
        if(p.types[0].type==5)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addNumberResult(matrixs[p.types[0].position].rankOfMatrix());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addNumberResult(p.types[0].new_matrix.rankOfMatrix());
            return 0;
        }
    }
    else if(p.types.size()==2)
    {
        if(p.types[0].type==5&&p.types[1].type==1)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteNumber(p.types[1].position,matrixs[p.types[0].position].rankOfMatrix());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            rewriteNumber(p.types[1].position,p.types[0].new_matrix.rankOfMatrix());
            return 0;
        }
    }

    return 12;
}

int MainWindow::matrixDet(Dealparams p)
{
    if(p.isNull) return 12;

    if(p.types.size()==1)
    {
        if(p.types[0].type==5)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addNumberResult(matrixs[p.types[0].position].det());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addNumberResult(p.types[0].new_matrix.det());
            return 0;
        }
    }
    else if(p.types.size()==2)
    {
        if(p.types[0].type==5&&p.types[1].type==1)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteNumber(p.types[1].position,matrixs[p.types[0].position].det());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            rewriteNumber(p.types[1].position,p.types[0].new_matrix.det());
            return 0;
        }
    }

    return 12;
}

int MainWindow::matrixTrace(Dealparams p)
{
    if(p.isNull) return 12;

    if(p.types.size()==1)
    {
        if(p.types[0].type==5)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addNumberResult(matrixs[p.types[0].position].traceOfMatrix());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addNumberResult(p.types[0].new_matrix.traceOfMatrix());
            return 0;
        }
    }
    else if(p.types.size()==2)
    {
        if(p.types[0].type==5&&p.types[1].type==1)
        {
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteNumber(p.types[1].position,matrixs[p.types[0].position].traceOfMatrix());
            return 0;
        }
        else if(p.types[0].type==4)
        {
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            rewriteNumber(p.types[1].position,p.types[0].new_matrix.traceOfMatrix());
            return 0;
        }
    }

    return 12;
}

int MainWindow::matrixPow(Dealparams p)
{
    if(p.isNull) return 12;

    if(p.types.size()==2)
    {
        if(p.types[0].type==5&&(p.types[1].type==0||p.types[2].type==1))
        {
            int size=p.types[1].number;
            if(size<0) return 12;
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            addMatrixResult(matrixs[p.types[0].position].pow(size));
            return 0;
        }
        else if(p.types[0].type==4&&(p.types[1].type==0||p.types[2].type==1))
        {
            int size=p.types[1].number;
            if(size<0) return 12;
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            addMatrixResult(p.types[0].new_matrix.pow(size));
            return 0;
        }
    }
    else if(p.types.size()==3)
    {
        if(p.types[0].type==5&&(p.types[1].type==0||p.types[2].type==1)&&p.types[2].type==5)
        {
            int size=p.types[1].number;
            if(size<0) return 12;
            if(matrixs[p.types[0].position].m!=matrixs[p.types[0].position].n) return 15;
            rewriteMatrix(p.types[2].position,matrixs[p.types[0].position].pow(size));
            return 0;
        }
        else if(p.types[0].type==4&&(p.types[1].type==0||p.types[2].type==1)&&p.types[2].type==5)
        {
            int size=p.types[1].number;
            if(size<0) return 12;
            if(p.types[0].new_matrix.m!=p.types[0].new_matrix.n) return 15;
            rewriteMatrix(p.types[2].position,p.types[0].new_matrix.pow(size));
            return 0;
        }
    }
    return 12;
}

int MainWindow::matrixTransform(Dealparams p)
{
    if(p.isNull) return 12;

     if(p.types.size()==1)
    {
         if(p.types[0].type==5)
         {
             addMatrixResult(matrixs[p.types[0].position].T());
             return 0;
         }
         else if(p.types[0].type==4)
         {
             addMatrixResult(p.types[0].new_matrix.T());
             return 0;
         }
    }
    else if(p.types.size()==2)
    {
         if(p.types[0].type==5&&p.types[1].type==5)
         {
             rewriteMatrix(p.types[1].position,matrixs[p.types[0].position].T());
             return 0;
         }
         else if(p.types[0].type==4)
         {
             rewriteMatrix(p.types[1].position,p.types[0].new_matrix.T());
             return 0;
         }
    }
    return 12;
}

int MainWindow::clearWindow(Dealparams p)//直接分析
{
    if(p.isNull)
    {
        AnalyzeBrowser->clear();
        return 0;
    }
    return 12;
}

int MainWindow::eraserVirtual(Dealparams p)//不对数据进行复制,直接检查。
{
    if(!p.isNull&&(p.types.size()==1))
    {
        QString name="";
        if(p.types[0].type==1)
        {
            name=numbers[p.types[0].position].name;
            eraser(1,p.types[0].position);
        }
        else if(p.types[0].type==3)
        {
            name=functions[p.types[0].position].virtualName;
            eraser(2,p.types[0].position);
        }
        else if(p.types[0].type==5)
        {
            name=matrixs[p.types[0].position].name;
            eraser(3,p.types[0].position);
        }
        else
        {
            return 12;
        }
        addResult(outputNormalColor(">>Eraser "+name));
        classExplor->delet(name);
        return 0;
    }
    return 12;
}

void MainWindow::eraser(int type,int position)
{
    switch (type)
   {
    case 1:
    {
        vector<Number>::iterator it=numbers.begin();
        for(int a=0;a<position;a++)
            it++;
        numbers.erase(it);
    }
        break;
    case 2:
    {
        vector<Function>::iterator it=functions.begin();
        for(int a=0;a<position;a++)
            it++;
        functions.erase(it);
    }
        break;
       case 3:
    {
         if(position!=0)
        {
            vector<Matrix>::iterator it=matrixs.begin();
            for(int a=0;a<position;a++)
            it++;
            matrixs.erase(it);
        }
         else
        {
             Matrix s;
             vector<Matrix> new_m;
             for(unsigned i=1;i<matrixs.size();i++)
             {
                 s=matrixs[i];
                 s.name=matrixs[i].name;
                 new_m.push_back(s);
             }
             matrixs.clear();
             matrixs=new_m;
        }
    }
       break;
   }
}

int MainWindow::matrixOutput(Dealparams p)
{
    if(p.isNull) return 12;
    if(p.types.size()==1)
    {
        if(p.types[0].type==5)
        {
             QStringList filenames=QFileDialog::getOpenFileNames(this,tr("文件选择"),tr("/home"),"数据文件(*.txt *.dat)");
             if(filenames.size()==0)
             {
                 return -1;
             }
             else
             {

                 ofstream file(filenames[0].toStdString());
                 if(!file)  return -1;//打不开文件
                 Matrix matrix=matrixs[p.types[0].position];
                 for(unsigned i=0;i<matrix.m;i++)
                 {
                     for(unsigned j=0;j<matrix.n;j++)
                      file<<matrix.arrays[i][j]<<" ";
                      file<<"\n";
                 }
                 file.close();
                 addResult(outputNormalColor(">>The data is saved."));
                 return 0;
             }
        }
    }
    return 12;
}

int MainWindow::matrixInput(Dealparams p)
{
    if(!p.isNull&&p.types.size()==2)
    {
        if(p.types[0].type==5)
        {
            int position=p.types[0].position;
            if(p.types[1].type==0||p.types[1].type==1)
            {
               int a=p.types[1].number;
               if(a>0)
               {
                   QStringList filenames=QFileDialog::getOpenFileNames(this,tr("文件选择"),tr("/home"),"数据文件(*.txt *.dat)");
                   if(filenames.size()==0)
                   {
                       return -1;
                   }
                   vector<vector<double>> datas;
                   ifstream file(filenames[0].toStdString());
                   if(!file)  return -1;//打不开文件
                   double number=0;
                   bool isEnd=false;
                   while(!file.eof())
                   {
                      vector<double> data;
                      for(int i=0;i<a;i++)
                      {
                          if(file>>number)
                          {
                              data.push_back(number);
                          }
                             else if(!file.eof())
                          {
                              return 16;
                          }
                          else
                          {
                              isEnd=true;
                              break;
                          }
                      }
                      if(!isEnd) datas.push_back(data);
                   }
                   if(datas.size()==0) return 16;
                   else
                   {
                       Matrix m;
                       m.arrays=datas;
                       m.m=datas.size();
                       m.n=a;
                       addResult(outputNormalColor(">>Data inputs successful."));
                       rewriteMatrix(position,m);
                       return 0;
                   }
               }
            }
        }
    }
    return 12;
}

int MainWindow::setDigit(Dealparams p)
{
  if(!p.isNull&&p.types.size()==1)
  {
      if(p.types[0].type==0||p.types[0].type==1)
      {
          if(p.types[0].number>1)
          {
            saveNumberCount=(int)p.types[0].number;
            addResult(outputNormalColor(">>Set Digit success."));
            return 0;
          }
            return 17;
      }

  }
  return 12;
}

int MainWindow::regressionUnifiedRegression(Dealparams p)
{
    if(!p.isNull&&(p.types.size()==2||p.types.size()==3))
    {
        int id=0;
        Matrix m(1,1);
        if(p.types[0].type==0||p.types[0].type==1)
        {
            id=p.types[0].number;
            if(id<=0||id>9) return 17;
            if(p.types[1].type==4||p.types[1].type==5)
            {
                m=p.types[1].new_matrix;
                if(m.n!=2) return 18;
                if(p.types.size()==2)
                {
                    regressionUnified regression(id,m);
                    if(!regression.ok)
                    {
                        return 19;
                    }
                    addFunctionResult(regression.f);
                    return 0;
                }                
                else
                {
                    if(p.types[2].type!=3) return 12;
                    regressionUnified regression(id,m);
                    if(!regression.ok)
                    {
                        return 19;
                    }
                    rewriteFunction(p.types[2].position,regression.f);
                    return 0;
                }
            }
        }
    }
    return 12;
}

int MainWindow::regressionMultipleRegression(Dealparams p)
{
     Matrix m(1,1);
     if(!p.isNull&&(p.types.size()==1||p.types.size()==2))
     {
         if(p.types[0].type==4||p.types[0].type==5)
         {
              m=p.types[0].new_matrix;
              if(m.m<m.n) return 20;
              if(p.types.size()==1)
              {
                 regressionMultiple regressin(m);
                 if(regressin.isTrue)
                 {
                     addFunctionResult(regressin.function);
                     return 0;
                 }
                 else return 19;
              }
              else
              {
                  if(p.types[1].type!=3) return 12;
                  regressionMultiple regressin(m);
                  if(regressin.isTrue)
                  {
                      rewriteFunction(p.types[1].position,regressin.function);
                      return 0;
                  }
                  else return 19;
              }
         }
     }
     return 0;
}

int MainWindow::regressionPlecrve(Dealparams p)
{
    if(!p.isNull&&(p.types.size()==2||p.types.size()==3))
    {
        int id=0;
        Matrix m(1,1);
        if(p.types[0].type==0||p.types[0].type==1)
        {
            id=p.types[0].number;
            if(id<0) return 17;
            if(p.types[1].type==4||p.types[1].type==5)
            {
                m=p.types[1].new_matrix;
                if(m.n!=2) return 18;
                if(m.m<id+1) return 20;
                if(p.types.size()==2)
                {
                    regressionPlecrvefitting regression(id,m);
                    if(!regression.isTrue)
                    {
                        return 19;
                    }
                    addFunctionResult(regression.new_function);
                    return 0;
                }
                else
                {
                    if(p.types[2].type!=3) return 12;
                    regressionPlecrvefitting regression(id,m);
                    if(!regression.isTrue)
                    {
                        return 19;
                    }
                    rewriteFunction(p.types[2].position,regression.new_function);
                    return 0;
                }
            }
        }
    }
    return 12;
}

void MainWindow::close()
{
    isPlaceExit=false;
}

void MainWindow::close2()
{
    isPolarExit=false;
}
//天线工程函数

int MainWindow::antennaWireSSA(Dealparams p)
{
    if(p.types.size()!=3&&p.types.size()!=4)
    {
       return 12;
    }
    else
    {
        if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        if(p.types.size()==4)
        {
            if(p.types[3].type!=5) return 12;
        }
        double k=p.types[0].number;
        double d=p.types[1].number;
        double n=p.types[2].number;
        if(k<0||d<0||n<1) return 12;
        antennaWire_SSA ass(k,d,n);
        if(p.types.size()==3)
        {
          addMatrixResult(ass.saves);
        }
        else
        {
            rewriteMatrix(p.types[3].position,ass.saves);
        }
        return 0;
    }
}

int MainWindow::antennaWireOEA(Dealparams p)
{
    if(p.types.size()!=3&&p.types.size()!=4)
    {
       return 12;
    }
    else
    {
        if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        if(p.types.size()==4)
        {
            if(p.types[3].type!=5) return 12;
        }
        double k=p.types[0].number;
        double d=p.types[1].number;
        double n=p.types[2].number;
        if(k<0||d<0||n<1) return 12;
        projectAntennaWireOEA oea(k,d,n);
        if(p.types.size()==3)
        {
          addMatrixResult(oea.save);
        }
        else
        {
            rewriteMatrix(p.types[3].position,oea.save);
        }
        return 0;
    }
}

int MainWindow::antennaWireTEA(Dealparams p)
{
    if(p.types.size()!=3&&p.types.size()!=4)
    {
       return 12;
    }
    else
    {
        if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        if(p.types.size()==4)
        {
            if(p.types[3].type!=5) return 12;
        }
        double k=p.types[0].number;
        double d=p.types[1].number;
        double n=p.types[2].number;
        if(k<0||d<0||n<1) return 12;
        projectAntennaWireTEA tea(k,d,n);
        if(p.types.size()==3)
        {
          addMatrixResult(tea.save);
        }
        else
        {
            rewriteMatrix(p.types[3].position,tea.save);
        }
        return 0;
    }
}

int MainWindow::antennaWirePA(Dealparams p)
{
    if(p.types.size()!=4&&p.types.size()!=5)
    {
       return 12;
    }
    else
    {
        if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        if(p.types[3].type!=0&&p.types[3].type!=1) return 12;
        if(p.types.size()==5)
        {
            if(p.types[4].type!=5) return 12;
        }
        double k=p.types[0].number;
        double d=p.types[1].number;
        double n=p.types[2].number;
        double theta=p.types[3].number;
        if(k<0||d<0||n<1) return 12;
        projectAntennaWirePA pa(k,d,n,theta);
        if(p.types.size()==4)
        {
          addMatrixResult(pa.save);
        }
        else
        {
            rewriteMatrix(p.types[4].position,pa.save);
        }
        return 0;
    }
}


//工程特殊函数
//0 厄米多项式; 1 勒让德多项式 2 贝塞尔函数
int MainWindow::specialFunction(Dealparams p,int mode)
{
    if(p.types.size()==4||p.types.size()==5)
    {
        if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
        if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
        if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
        double n=p.types[0].number;
        if(n<0) return 12;
        double min=p.types[1].number;
        double max=p.types[2].number;
        if(min>=max) return 12;
        double dx=0.01;
        int    position=0;
        if(p.types.size()==4)
        {
            if(p.types[3].type!=5) return 12;
            position=p.types[3].position;
        }
        else
        {
            if(p.types[3].type!=0&&p.types[3].type!=1) return 12;
            if(p.types[4].type!=5)return 12;
            dx=p.types[3].number;
            if(dx<0) return 12;
            position=p.types[4].position;
        }
        switch (mode)
        {
          case 0:
        {
            specialFunction_Hermite herimte(n,min,max,dx);
            rewriteMatrix(position,herimte.answer);
            return 0;
        }
            break;
          case 1:
        {
            specialFunction_Legendre legendre(n,min,max,dx);
            rewriteMatrix(position,legendre.answer);
            return 0;
        }
            break;
          case 2:
        {
            specialFunction_Bezier bezier(n,min,max,dx);
            rewriteMatrix(position,bezier.m);
            return 0;
        }
            break;
        }
    }
    return 12;
}

 int MainWindow::specialFunction_Besier(Dealparams p)
 {
     if(p.types.size()==4||p.types.size()==5)
     {
         if(p.types[0].type!=0&&p.types[0].type!=1) return 12;
         if(p.types[1].type!=0&&p.types[1].type!=1) return 12;
         if(p.types[2].type!=0&&p.types[2].type!=1) return 12;
         double n=p.types[0].number;
         if(n<0) return 12;
         double min=p.types[1].number;
         double max=p.types[2].number;
         if(min>=max) return 12;
         double dx=0.01;
         int    position=0;
         if(p.types.size()==4)
         {
             if(p.types[3].type!=5) return 12;
             position=p.types[3].position;
         }
         else
         {
             if(p.types[3].type!=0&&p.types[3].type!=1) return 12;
             if(p.types[4].type!=5)return 12;
             dx=p.types[3].number;
             if(dx<0) return 12;
             position=p.types[4].position;
         }
         specialFunction_Bezier bezier(n,min,max,dx);
         rewriteMatrix(position,bezier.m);
         return 0;
     }
     return 12;
 }
//------------------------------------------------------------添加Result
void MainWindow::addNumberResult(double a)
{
     Number s(a,"Result");
    if(isCreate)
    {
       classExplor->changeTableItem(s);
    }
    else
    {
        isCreate=true;
        classExplor->addNumberTableItem(s);
    }
    style=0;
    valueOfResult=a;
    addResult(outputNormalColor(">> Result=")+outputNumberColor(QString::number(a,10,saveNumberCount)));
}

void MainWindow::addFunctionResult(Function f)
{
    f.virtualName="Result";
    if(isCreate)
    {
       classExplor->changeTableItem(f);
    }
    else
    {
        isCreate=true;
        classExplor->addFunctiontableItem(f);
    }
    style=1;
    functionOfResult=f;

    addResult(outputNormalColor(">> Result=")+outputNumberColor(f.function));
}

void MainWindow::addMatrixResult(Matrix m)
{
    m.name="Result";
    if(isCreate)
    {
        classExplor->changeTableItem(m);
        matrixOfResult.name=m.name;
    }
    else
    {
        isCreate=true;
        matrixOfResult.name="Result";
        classExplor->addMatrixtableItem(m);
    }
    style=2;
    matrixOfResult=m;
    showMatrix(m);
}

int MainWindow::dealResult(QString text)
{
    if(!isCreate)
    {
        addResult(outputNormalColor(">>The result is not created."));
        return 0;
    }
    if(text=="Result;")
    {
        switch (style)
        {
          case 0:
            addResult(outputNormalColor(">>The class of Result is Number."));
            addResult(outputNormalColor(">> Result =")+outputNumberColor(QString::number(valueOfResult,10,saveNumberCount)));
            break;
          case 1:
             addResult(outputNormalColor(">>The class of Result is Function."));
             addResult(outputNormalColor(">> Result =")+outputNumberColor(functionOfResult.function));
            break;
          case 2:
            addResult(outputNormalColor(">>The class of Result is Matrix."));
            showMatrix(matrixOfResult);
            break;
        }
        return 0;
    }
    else
    {
        QString t="";
        int i;
        for(i=0;i<8;i++)
          t.append(text[i]);
        if(t=="Result->")
        {
            t="";
            do
            {
                t.append(text[i]);
                i++;
            }
            while(text[i]!=';');
            for(unsigned i=0;i<numbers.size();i++)
            {
               if(numbers[i].name==t)
               {
                   if(style==0)
                   {
                       rewriteNumber(i,valueOfResult);
                       return 0;
                   }
                   else
                       return 5;
               }
            }
            for(unsigned i=0;i<functions.size();i++)
            {
                if(functions[i].virtualName==t)
                {
                    if(style==1)
                    {
                        rewriteFunction(i,functionOfResult);
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
            }
            for(unsigned i=0;i<matrixs.size();i++)
            {
                if(matrixs[i].name==t)
                {
                    if(style==2)
                    {
                        rewriteMatrix(i,matrixOfResult);
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
            }
            return 5;
        }
        else
        {
            return 5;
        }
    }
}


//----------------------------------------------------------------整体性操作
void MainWindow::endTime()
{
    QueryPerformanceCounter(&litmp);
    //   获得终止值
    QPart2=litmp.QuadPart;
    dfMinus=(double)(QPart2-QPart1);
    //   获得对应的时间值
   showTime->addData((double)dfMinus/dfFreq*1000);
}

void MainWindow::startTime()
{
    QueryPerformanceFrequency(&litmp);
    //   获得计数器的时钟频率
    dfFreq=(double)litmp.QuadPart;

    QueryPerformanceCounter(&litmp);
    //   获得初始值
    QPart1=litmp.QuadPart;
}

void MainWindow::addCommand(QString information)
{
    commandBox.push_back(information);
    commandPointer=commandBox.end();
}

void MainWindow::upOperater()
{
    if(commandBox.size()==0) return;
    if(commandPointer!=commandBox.begin()) commandPointer--;
    else commandPointer=commandBox.end()-1;
    input->setText(*commandPointer);
}

void MainWindow::downOperater()
{
    if(commandBox.size()==0) return;
    if(commandPointer!=commandBox.end()-1)commandPointer++;
    else commandPointer=commandBox.begin();
    input->setText(*commandPointer);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Up)
    {
        upOperater();
    }
    else if(event->key()==Qt::Key_Down)
    {
        downOperater();
    }
}

void MainWindow::addCode()
{

}

void MainWindow::addResult(QString s)
{
    AnalyzeBrowser->append(s);
    AnalyzeBrowser->append("");
}


