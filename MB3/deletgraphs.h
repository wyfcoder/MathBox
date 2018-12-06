#ifndef DELETGRAPHS_H
#define DELETGRAPHS_H

#include <QWidget>
#include<vector>
#include<QButtonGroup>
#include<QPushButton>
using namespace std;
class DeletGraphs : public QWidget
{
    Q_OBJECT
public:
    explicit DeletGraphs(QWidget *parent = nullptr);
    void setName(vector<QString> names);
private:
    void init();
    vector<QString> selectNames;
    vector<QString> allNames;
    QButtonGroup* group;
    QPushButton* deletButton;
    QPushButton* exitButton;
signals:
    void sendData(QString data);
public slots:
    void deletButoonClick();
    void exit();
};

#endif // DELETGRAPHS_H
