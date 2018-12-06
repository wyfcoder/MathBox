#ifndef MQLINEEDIT_H
#define MQLINEEDIT_H
#include<QLineEdit>
#include<qwidget.h>
class MQLineEdit : public QLineEdit
{
public:
    MQLineEdit(QWidget*);
    int key;
};

#endif // MQLINEEDIT_H
