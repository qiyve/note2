#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //应用程序对象 有且仅有一个
    MyWidget w; //实例化窗口对象
    w.show();   //调用show函数  显示窗口

    return a.exec(); //让应用程序对象进入消息循环机制中，代码阻塞到当前
}
