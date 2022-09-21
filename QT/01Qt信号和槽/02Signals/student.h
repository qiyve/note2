#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QDebug>


class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = 0);

signals:

public slots:
//    返回值 void
//    需要声明，也需要实现
//    可以有参数，可以重载
//    写到 public slot 下 或者 public 或者全局函数
    void treat();

    //请老师吃宫保鸡丁
    void treat(QString FoodName);

};

#endif // STUDENT_H
