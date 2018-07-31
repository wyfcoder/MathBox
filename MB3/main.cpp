#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int exitCode = 0;
        do{
            MainWindow w;
            w.show();
            exitCode  = a.exec();

        }while( exitCode  == 888 );


    return 0;
}
