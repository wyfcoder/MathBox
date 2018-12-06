#ifndef SHOWHELPDOC_H
#define SHOWHELPDOC_H

#include <QWidget>
#include<QMenuBar>
#include<QTextBrowser>
#include<QAction>
#include<QWidget>
#include<QVBoxLayout>

class ShowHelpDoc : public QWidget
{
    Q_OBJECT
public:
    explicit ShowHelpDoc(QWidget *parent = nullptr);
    void ShowFile(int i,QTextBrowser* text);

    void creatAction();
    void creatMenuBar();
    int i = 1;
    QTextBrowser* text;

signals:

public slots:
    void setFont();
    void PreviousType();
    void NextType();
private:



    QMenuBar* menuBar;
    QAction* previous;
    QAction* next;
    QAction* fonts;



};

#endif // SHOWHELPDOC_H
