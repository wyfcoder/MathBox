#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"buildhelper.h"
#include<QStringListModel.h>
#include"parmtype.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置主窗口的一些性质
    this ->setWindowTitle("MathBox");
    this ->setMinimumSize(900,600);

    createActions();
    createToolBars();

    mainWidget = new QWidget;
    input = new QLineEdit(mainWidget);
    output = new QTextBrowser(mainWidget);
    inputLabel = new QLabel("指令输入：",mainWidget);
    outputLabel = new QLabel("输出：",mainWidget);
    mainLayout = new QVBoxLayout;
    mainLayout ->addWidget(outputLabel);
    mainLayout ->addWidget(output);
    mainLayout ->addWidget(inputLabel);
    mainLayout ->addWidget(input);
    mainWidget ->setLayout(mainLayout);
    this ->setCentralWidget(mainWidget);


    SearchDock = new QDockWidget("搜索");
    SearchDock ->setMinimumSize(200,300);
    SearchDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
    SearchWidget = new QWidget;
    SearchLineEdit = new QLineEdit("请输入...",SearchWidget);
    SearchBtn = new QPushButton("搜索",SearchWidget);
    SearchTextBrowser = new QTextBrowser(SearchWidget);
    SearchMainLayout = new QGridLayout(SearchWidget);
    SearchMainLayout ->addWidget(SearchLineEdit,0,0);
    SearchMainLayout ->addWidget(SearchBtn,0,1);
    SearchMainLayout ->addWidget(SearchTextBrowser,1,0,1,2);
    SearchDock ->setWidget(SearchWidget);
    SearchWidget ->setLayout(SearchMainLayout);
    this ->addDockWidget(Qt::LeftDockWidgetArea,SearchDock);


    DataDock = new QDockWidget("数据情况");
    DataDock ->setMinimumSize(200,250);
    DataDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
//    DataDock ->setMaximumSize(200,250);
    this ->addDockWidget(Qt::LeftDockWidgetArea,DataDock,Qt::Vertical);


//    OutputDock = new QDockWidget("输出显示窗口");
//    OutputDock ->setFixedSize(500,300);
//    OutputDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
////    OutputDock ->setMinimumSize(450,450);
//    OutputWidget = new QWidget;
//    OutputDock ->setWidget(OutputWidget);
//    OutPutTextBrowser = new QTextBrowser(OutputWidget);
//    OutputLayout = new QHBoxLayout(OutputDock);
//    OutputLayout ->addWidget(OutPutTextBrowser);
//    OutputWidget ->setLayout(OutputLayout);
//    this ->addDockWidget(Qt::TopDockWidgetArea,OutputDock,Qt::Horizontal);

//    InputDock = new QDockWidget("输入显示窗口");
//    InputDock ->setFixedSize(500,250);
//    InputDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
////    InputDock ->setMinimumSize(450,80);
//    InputWidget = new QWidget;
//    InputDock ->setWidget(InputWidget);
//    InputLineEdit = new QLineEdit(InputWidget);
//    InputLayout = new QHBoxLayout(InputWidget);
//    InputLayout ->addWidget(InputLineEdit);
//    InputWidget ->setLayout(InputLayout);
//    this ->addDockWidget(Qt::BottomDockWidgetArea,InputDock,Qt::Horizontal);

    Filemodel = new QFileSystemModel;
    Filemodel ->setRootPath(QDir::currentPath());

    FileCatalogDock = new QDockWidget("文件目录");
    FileCatalogDock ->setMinimumSize(200,300);
    FileCatalogWidget = new QWidget;
    FileCatalogLayout = new QVBoxLayout(FileCatalogWidget);
    FileCatalogView = new QTreeView(FileCatalogWidget);
    FileCatalogView ->setModel(Filemodel);
    FileCatalogLayout ->addWidget(FileCatalogView);
    FileCatalogDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
    FileCatalogDock ->setWidget(FileCatalogWidget);
//    FileCatalogDock ->setMaximumSize(200,300);
    this ->addDockWidget(Qt::RightDockWidgetArea,FileCatalogDock);

    FileDock = new QDockWidget("文件");
    FileDock ->setMinimumSize(200,250);
    FileDock ->setFeatures(QDockWidget::NoDockWidgetFeatures);
    FileWidget = new QWidget;
    FileLayout = new QVBoxLayout(FileWidget);
    FileListView = new QListView(FileWidget);
    FileListView ->setModel(Filemodel);
    FileListView ->setRootIndex(Filemodel->index(QDir::currentPath()));
    FileLayout ->addWidget(FileListView);
    FileDock ->setWidget(FileWidget);
//    FileDock ->setMaximumSize(200,250);
    this ->addDockWidget(Qt::RightDockWidgetArea,FileDock,Qt::Vertical);

//-----------------------------------------------------------------------------
     null="NULL";
     for(int i=0;i<100;i++)
     randcount.rand();
     initVecor();
     initProgrameTable();
     output->append(greenColor(">>Hello,welcome to MathBox."));
     output->append("");
     MakeCompleter();
     setFonts();
     classExplor=new ClassExplor(this);
     DataDock->setWidget(classExplor);
     connect(input,SIGNAL(returnPressed()),this,SLOT(change()));
     connect(input,SIGNAL(textChanged(QString)),this,SLOT(find()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    OpenFileAction = new QAction(QIcon(":/picture/open.png"),("打开"),this);
    OpenFileAction ->setStatusTip("打开一个文件");
    connect(OpenFileAction,SIGNAL(triggered(bool)),this,SLOT(OpenFile()));

    NewFileAction = new QAction(QIcon(":/picture/new.png"),("新建"),this);
    NewFileAction ->setStatusTip("新建一个编辑窗口");
    connect(NewFileAction,SIGNAL(triggered(bool)),this,SLOT(NewFile()));

    SaveFileAction = new QAction(QIcon(":/picture/save.png"),("存储"),this);
    SaveFileAction ->setStatusTip("存储一个文件");
    connect(SaveFileAction,SIGNAL(triggered(bool)),this,SLOT(SaveFile()));

    DeleteAction = new QAction(QIcon(":/picture/delete2.png"),("删除"),this);
    DeleteAction ->setStatusTip("删除显示");
    connect(DeleteAction,SIGNAL(triggered(bool)),this,SLOT(Delete()));

    BackAction = new QAction(QIcon(":/picture/back.png"),("后退"),this);
    BackAction ->setStatusTip("后退一步");
    connect(BackAction,SIGNAL(triggered(bool)),this,SLOT(Back()));

    ForwardAction = new QAction(QIcon(":/picture/forward.png"),("前进"),this);
    ForwardAction ->setStatusTip("前进一步");
    connect(ForwardAction,SIGNAL(triggered(bool)),this,SLOT(Forward()));

    PaintAction = new QAction(QIcon(":/picture/paint.png"),("绘图"),this);
    PaintAction ->setStatusTip("绘制相关数据图片");
    connect(PaintAction,SIGNAL(triggered(bool)),this,SLOT(Paint()));

    MainWinAction = new QAction(QIcon(":/picture/main.png"),("主窗口"),this);
    MainWinAction ->setStatusTip("窗口恢复开始状态");
    connect(MainWinAction,SIGNAL(triggered(bool)),this,SLOT(ReMain()));
}

void MainWindow::createToolBars()
{
    //文件工具条
    FileTool = addToolBar("工具");
    FileTool ->addAction(OpenFileAction);
    FileTool ->addAction(NewFileAction);
    FileTool ->addAction(SaveFileAction);

    //编辑工具条
    EditTool = addToolBar("编辑");
    EditTool ->addAction(DeleteAction);
    EditTool ->addSeparator();
    EditTool ->addAction(BackAction);
    EditTool ->addAction(ForwardAction);

    //绘图工具条
    PaintTool = addToolBar("绘图");
    PaintTool ->addAction(PaintAction);

    //恢复工具栏
    RenewMainTool = addToolBar("恢复主页");
    RenewMainTool ->addAction(MainWinAction);

}


void MainWindow::OpenFile()
{

}
void MainWindow::NewFile()
{

}
void MainWindow::SaveFile()
{

}
void MainWindow::Delete()
{
    output ->setPlainText("");

}
void MainWindow::Back()
{

}
void MainWindow::Forward()
{

}
void MainWindow::ReMain()
{
    qApp->exit( 888 );//调用exit()，退出应用程序
}
void MainWindow::Paint()
{

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
    programTable.push_back("Pro_Rand");//0
}
void MainWindow::setFonts()
{
    SearchLineEdit->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
    DataDock->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
    //commandShow->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
    output->setFont(QFont( "Microsoft YaHei" , 12 ,  QFont::Normal));
    outputLabel->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
    input->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
    inputLabel->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));

    //classShow->setFont(QFont( "Microsoft YaHei" , 10 ,  QFont::Normal));
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
    return QObject::tr("<font color=blue>%1</font>").arg(s);
}

QString MainWindow::blackColor(QString s)
{
    return QObject::tr("<font color=black>%1</font>").arg(s);
}

QString MainWindow::lightSkyBlue(QString s)

{
          return QObject::tr("<font color=LightSeaGreen>%1</font>").arg(s);
}

QString MainWindow::lightGreen(QString s)
{
          return QObject::tr("<font color=LightGreen>%1</font>").arg(s);
}

QString MainWindow::lightGray(QString s)
{
    return QObject::tr("<font color=LightSlateGray>%1</font>").arg(s);

}

void MainWindow::MakeCompleter()
{
    names<<"Matrix"<<"Function"<<"U_Input"<<"U_Output";
    names<<"MB_MatrixTransform(Matrix a,Matrix save)"<<"MB_MatrixTransform(Matrix a)";
    names<<"MB_MatrixPow(Matrix a,int t,Matrix save)"<<"MB_MatrixPow(Matrix a,int t)";
    names<<"MB_MatrixTrace(Matrix a)";
    names<<"MB_MatrixDet(Matrix a)";
    names<<"MB_MatrixRank(Matrix a)";
    names<<"MB_MatrixtoLadder(Matrix a,Matrix save)"<<"MB_MatrixtoLadder(Matrix a)";
    names<<"MB_MatrixtoUpTriangle(Matrix a,Matrix save)"<<"MB_MatrixtoUpTriangle(Matrix a)";
    names<<"MB_MatrixtoDownTriangle(Matrix a,Matrix save)"<<"MB_MatrixtoDownTriangle(Matrix a)";
    names<<"MB_MatrixInvers(Matrix a,Matrix save)"<<"MB_MatrixInvers(Matrix a)";
    names<<"Number";
    names<<"Pro_Rand(Number save)";
    names<<"Pro_Rand()";
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
         switch (rb) {
         case 0:
             input->setText("");
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
            output->append(redColor(">>Undefinded Class!"));
            break;
        case 2:
            output->append(redColor(">>Undefined variable name!"));
            break;
        case 3:
            output->append(redColor(">>Not suitable for Matrix's style!"));
            break;
         case -1:
            output->append(redColor(">>Fail to open file!"));
            break;
         case 4:
            output->append(redColor(">>Matrix expression is wrong!"));
            break;
         case 5:
            output->append(redColor(">>The command is wrong!"));
            break;
         case 6:
            output->append(redColor(">>The matrix is singular!"));
            break;
          case 7:
            output->append(redColor(">>Not suitable for Number's style!"));
            break;
         case 8:
            output->append(redColor(">>Expression is not allowed."));
            break;
       }
        output->append(" ");
    }

int MainWindow::check(QString text)
{
    if(text.size()<2)
    {
        return 5;
    }
    else
    {
         buildhelper helper;
        if(text[0]=='N'||text[0]=='F'||text[0]=='M')
        {
               int mode=helper.getClassMode(text);
               if(mode==-1) return 1;
               QString name=helper.checkVirtulName();
               if(QString::compare(name,null)==0) return 2;
               switch (mode)
              {
               case 0:

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

                   break;
               default:
                   break;
               }
        }
          else if(text[0]=='P'&&text[1]=='r')
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
            int j=i;
            QString parms;
            while(i<text.size()-2)
            {
                parms.append(text[i]);
                i++;
            }
            switch (code)
           {
            case 0://单个参数的情况
            {
                double r=randcount.rand();
                if(text[j]==')')
                {
                    output->append(greenColor(">>Rand a number: ")+lightGray(QString::number(r)));
                    output->append("");
                }
                else
                {
                    ParmType type=singalParm(parms);
                    if(!type.isTrue||type.type!=1)
                        return 5;
                    rewriteNumber(type.name,r);
                }
            }
                break;
            default:
                break;
           }
        }
         else if(text[0]>='a'&&text[0]<='z')
        {
            helper.inputText(text);
            QString name=helper.checkVirtulName();
            if(QString::compare(name,null)==0) return 2;
            int mode=class_mode(name);
            if(mode==-1) return 2;
            switch (mode)
           {
            case 0:
                break;
             case 1:
                if(!helper.helpNumberBuilder(numbers))
                    return 7;
                if(helper.isExpresson)
                {
                    output->append(lightGray(">>The result is "+ QString::number(helper.value)));
                }
                else
                {
                    rewriteNumber(name,helper.value);
                }
                break;
            case 2:
                break;
            default:
                break;
            }
        }
        else
       {
            helper.inputText(text);
            if(!helper.helpNumberBuilder(numbers))
                return 7;
            output->append(lightGray(">>The result is "+ QString::number(helper.value)));
            output->append("");
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
        if(name==matrixs.size())
            return 0;
    }
    return -1;
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

ParmType MainWindow::singalParm(QString text)
{
    ParmType type;
    type.isTrue=false;
    bool isOk=false;
        type.n=text.toInt(&isOk);
        if(isOk)
        {
            type.type=4;
        }
        else
        {
          type.number=text.toDouble(&isOk);
          if(isOk)
          {
              type.type=5;
          }
          else
          {
              for(unsigned i=0;i<numbers.size();i++)
              {
                  if(numbers[i].name==text)
                  {
                      type.isTrue=true;
                      type.position=i;
                      type.type=1;
                      type.name=text;
                      isOk=true;
                      break;
                  }
              }
              if(!isOk)
              {
                  //其他容器
              }
          }
    }
        return type;
}
//----------------------------------------------------------UI响应
void MainWindow::addNewNumber(Number number)
{
    numbers.push_back(number);
    output->append(greenColor(">>New ")+blueColor(" Number "));
    output->append("");
    output->append(greenColor("@ ")+lightSkyBlue(number.name)+"="+lightGray(QString::number(number.value)));
    output->append("");
    classExplor->addNumberTableItem(number);
}
void MainWindow::rewriteNumber(QString name, double value)
{
    for(unsigned i=0;i<numbers.size();i++)
    {
        if(numbers[i].name==name)
        {
            numbers[i].value=value;
            output->append(greenColor(">>Rewrite ")+blueColor(" Number "));
            output->append("");
            output->append(greenColor("@ ")+lightSkyBlue(name)+"="+lightGray(QString::number(value)));
            output->append("");
            classExplor->changeTableItem(numbers[i]);
        }
    }
}



