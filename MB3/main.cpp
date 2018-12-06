#include "mainwindow.h"
#include <QApplication>
#include<QElapsedTimer>
#include<QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/picture/mathbox.png");
    QSplashScreen screen(pixmap);
    screen.show();
    int delayTime=5;
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<(delayTime*1000))
    {
        a.processEvents();
    }
    screen.close();
    int exitCode = 0;
        do{
            MainWindow w;
            w.show();
            exitCode  = a.exec();

        }while( exitCode  == 888 );




    return 0;
}
