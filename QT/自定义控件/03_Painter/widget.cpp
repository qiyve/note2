#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击按钮移动图片
    connect(ui->btn,&QPushButton::clicked,[=](){
            posX += 20;
            update();
    });


    //创建定时器 连接 图片使其 自己移动
    QTimer* timer = new QTimer(this);

    timer->start(1000); //启动定时器
    connect(timer,&QTimer::timeout,[=](){
        posX += 20;
        update();
    });

}
void Widget::paintEvent(QPaintEvent *event)
{


//    QPainter painter(this); //实例化画家对象  这里this  指定的是绘图设备

//    QPen pen(QColor(255,0,0)); //设置画笔 颜色

//    pen.setWidth(3); //设置画笔宽度

//    pen.setStyle(Qt::DotLine);   //设置风格

//    QBrush brush(Qt::cyan);  //设置画刷颜色
//    brush.setStyle(Qt::Dense1Pattern);//设置画刷风格

//    painter.setBrush(brush);//让画家使用画刷

//    painter.setPen(pen);  //让画家使用画笔

//    painter.drawLine(QPoint(0,0),QPoint(200,200)); //画线

//    painter.drawEllipse(QPoint(200,200),50,50); //画圆 椭圆

//    painter.drawRect(120,120,50,50); //画矩形

//    painter.drawText(QPoint(0,200),"好好学习"); //画文字



    /////////////////////// 高级设置 //////////////////

//    QPainter painter(this);
//    painter.drawEllipse(QPoint(50,50),50,50);
//    //设置 抗锯齿能力  效率较低  Antialiasing
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawEllipse(QPoint(150,50),50,50);


//    //画矩形
//    painter.drawRect(20,20,50,50);

//    //移动画家
//    painter.translate(100,0);
//    //保存画家位置
//    painter.save();

//    painter.drawRect(20,20,50,50);

//    painter.translate(100,0);
//    //还原画家位置
//    painter.restore();

//    painter.drawRect(20,20,50,50);


  /////////////////////// 利用绘图事件 画图片//////////////////

    QPainter painter(this);

    //画 图片
    //判断 如果超出屏幕就回来
    if(posX > this->width())
    {
        posX = 0;
    }
    painter.drawPixmap(posX,20,100,100,QPixmap(":/s.png"));

}



Widget::~Widget()
{
    delete ui;
}
