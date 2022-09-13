#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    Id1 = startTimer(1000);//单位毫秒
    Id2 = startTimer(2000);//单位毫秒

    //创建第二种定时器
    QTimer* timer = new QTimer(this);

    //启动定时器 0.5 秒 走一次
    timer->start(500);
    connect(timer,&QTimer::timeout,[=](){
        static int num3 = 0;
        ui->label_4->setText(QString::number(num3++));
    });

    //点击按钮暂停 计时器4
    connect(ui->btn,&QPushButton::clicked,[=](){
        timer->stop();
    });


    //给 Label1 安装事件过滤器
    //步骤1 安装事件过滤器
    ui->label->installEventFilter(this);
}

// 步骤2 重写 eventFilter
bool Widget::eventFilter(QObject *obj, QEvent *e)
{
    //先判断是否是 自己想要的控件
    if(obj == ui->label)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* ev = static_cast <QMouseEvent*>(e);
            QString src = QString("事件过滤器  鼠标按下 x = %1 y = %2 globalX = %3 globalY = %4 ").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
            qDebug()<<src ;

            return true; //true 这个代表用户自己处理事件 不向下分发
        }

    }
    //其他交给 父类 默认处理
    return QWidget::eventFilter(obj,e);
}


// 定时器
void Widget::timerEvent(QTimerEvent *ev)
{
    //每隔1秒走一次
    if(ev->timerId()== Id1)
    {
        static int num = 0;
        ui->label_2->setText(QString::number(num++));
    }


    //每隔2秒走一次
    if(ev->timerId() == Id2)
    {
        static int num2 = 0;
        ui->label_3->setText(QString::number(num2++));
    }
}


Widget::~Widget()
{
    delete ui;
}

