#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "teacher.h"
#include "student.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    Teacher* teacher;
    Student* student;

    //下课函数
    void classIsOver();
};

#endif // WIDGET_H
