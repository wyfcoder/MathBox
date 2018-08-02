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

#include<vector>
#include<QCompleter>
#include"number.h"
#include"matrix.h"
#include"classexplor.h"
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
    explicit MainWindow(QWidget *parent = 0);

    void createActions();//创建动作
    void createToolBars();//创建工具栏


    ~MainWindow();

protected slots:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void Delete();
    void Back();
    void Forward();
    void Paint();
    void ReMain();
    //--------------------
    void change();
    void find();
private:
    Ui::MainWindow *ui;

    //工具栏
    QToolBar *FileTool;
    QToolBar *EditTool;
    QToolBar *PaintTool;
    QToolBar *RenewMainTool;


    //工具栏动作
    QAction *OpenFileAction;
    QAction *NewFileAction;
    QAction *SaveFileAction;
    QAction *DeleteAction;
    QAction *BackAction;
    QAction *ForwardAction;
    QAction *PaintAction;
    QAction *MainWinAction;

    //搜索窗口的部件
    QDockWidget *SearchDock;
    QLineEdit *SearchLineEdit;
    QPushButton *SearchBtn;
    QTextBrowser *SearchTextBrowser;
    QGridLayout *SearchMainLayout;
    QWidget *SearchWidget;


    //数据情况窗口
    QDockWidget *DataDock;


//    //输出窗口
//    QDockWidget *OutputDock;
//    QTextBrowser *OutPutTextBrowser;
//    QWidget *OutputWidget;
//    QHBoxLayout *OutputLayout;

//    //输入窗口
//    QDockWidget *InputDock;
//    QLineEdit *InputLineEdit;
//    QHBoxLayout *InputLayout;
//    QWidget *InputWidget;

    //中心centralWidget
    QWidget *mainWidget;
    QTextBrowser *output;
    QLineEdit *input;
    QVBoxLayout *mainLayout;
    QLabel *outputLabel;
    QLabel *inputLabel;


    //文件目录显示窗口
    QDockWidget *FileCatalogDock;
    QWidget *FileCatalogWidget;
    QVBoxLayout *FileCatalogLayout;
    QTreeView *FileCatalogView;


    //所有文件列表窗口
    QDockWidget *FileDock;
    QListView *FileListView;
    QVBoxLayout *FileLayout;
    QWidget *FileWidget;


    QFileSystemModel *Filemodel;
private:
     QCompleter* completer;
     ClassExplor* classExplor;
 //----------------------------------------------------
     QString null;
//-----------------------------------------------------
    void setFonts();
    QString redColor(QString);
    QString greenColor(QString);
    QString blueColor(QString);
    QString blackColor(QString);
    QString lightSkyBlue(QString);
    QString lightGreen(QString);
    QString lightGray(QString);
//------------------------------------------------------
    void initVecor();
    vector<QString> classNames;
    QStringList names;
    vector<Number> numbers;
    vector<Matrix> matrixs;
//------------------------------------------------------
     void MakeCompleter();
//------------------------------------------------------
     int check(QString text);
     void dealWrong(int number);
     class_mode(QString name);
//---------------------------------------------------------UI响应
     void addNewNumber(Number number);
     void rewriteNumber(QString name, double value);
};

#endif // MAINWINDOW_H
