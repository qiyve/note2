#include "student.h"

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::treat()
{
    qDebug()<<"请客吃饭";
}

void Student::treat(QString FoodName)
{
  // QString 转char*
  // QString 先转成
  qDebug()<<"请老师吃饭："<<FoodName.toUtf8().data();
}
