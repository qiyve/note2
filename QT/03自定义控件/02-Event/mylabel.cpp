#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪状态
    //setMouseTracking(true);
}

//鼠标进入事件
void myLabel::enterEvent(QEvent *event)
{
    //qDebug()<<"鼠标进入";
}

//鼠标离开事件
void myLabel::leaveEvent(QEvent *)
{
    //qDebug()<<"鼠标离开";
}

// 鼠标按下
void myLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        QString src = QString("鼠标按下 x = %1 y = %2 globalX = %3 globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<src ;
    }
}

//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
     if( ev->buttons() & Qt::LeftButton)
     {
         QString src = QString("鼠标移动 x = %1 y = %2 ").arg(ev->x()).arg(ev->y());
         qDebug()<<src;
     }
}


//鼠标释放
void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QString src = QString("鼠标释放 x = %1 y = %2 ").arg(ev->x()).arg(ev->y());
    qDebug()<<src;
}

bool myLabel::event(QEvent *event)
{

    //如果是鼠标按下 在Event事件分发中做拦截操作
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* ev = static_cast <QMouseEvent*>(event);
        QString src = QString("Event事件函数  鼠标按下 x = %1 y = %2 globalX = %3 globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<src ;

        return true; //true 这个代表用户自己处理事件 不向下分发
    }

    //其他交给 父类 默认处理
    return QLabel::event(event);
}

