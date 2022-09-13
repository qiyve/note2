#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //创建一个按钮
    QPushButton* btn = new QPushButton();
    //显示按钮
    //btn->show();//show以顶层方式弹出控件
    //让btn对象 依赖在 myWidget窗口中
    btn->setParent(this);

    //设置文本
    btn->setText("第一个按钮");

    //创建第二个按钮  按照
    QPushButton* btn2 = new QPushButton("第二个按钮",this);

    //移动btn2 按钮
    btn2->move(100,0);

    //设置按钮的担心
    btn2->resize(50,50);

    //重置窗口大小
    resize(600,500);

    //设置窗口标题
    setWindowTitle("第一个窗口");

    //设置窗口固定大小
    setFixedSize(600,500);


    //创建一个自己的按钮对象
    MyPushButton* myBtn= new MyPushButton;
    myBtn->setText("我自己的按钮");

    myBtn->move(300,100);
    myBtn->setParent(this);  //设置到对象树中

    //需求 点击我的按钮 关闭窗口
    //参数1 信号发送者 参数2 发送的信号(函数的地址） 参数3 信号的接收者 参数4 处理的槽函数
    //connect(myBtn,&MyPushButton::clicked,this,&MyWidget::close);
    connect(myBtn,&QPushButton::clicked,this,&QWidget::close);

}

MyWidget::~MyWidget()
{
    qDebug()<<"MyWidget析构调用";
    delete ui;
}



























