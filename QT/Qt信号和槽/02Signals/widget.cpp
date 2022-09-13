#include "widget.h"
#include <QPushButton>
#include <QDebug>

//Teacher 类 老师类
//Student 类 学生类
//下课后， 老师会触发一个信号，饿了， 学生相应信号 请客吃饭


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建老师
    this->teacher = new Teacher(this);
    //创建学生
    this->student = new Student(this);

    //连接 老师饿了 学生请客
    // connect(teacher,&Teacher::hungry,student,&Student::treat);

    //触发下课  需要先连接 在触发信号
    //classIsOver();


    //连接带参数的信号 和 槽
    //函数指针 -> 函数地址
    void(Teacher:: *teacherSignal)(QString) = &Teacher::hungry;
    void(Student::*studentSlot)(QString) = &Student::treat;
    connect(teacher,teacherSignal,student,studentSlot);
    classIsOver();


    //点击一个 下课的按钮触发 下课
    QPushButton* btn = new QPushButton("下课",this);

    //重置窗口大小
    this->resize(600,500);

    //连接单击按钮 触发下课
    //connect(btn,&QPushButton::clicked,this,&Widget::classIsOver);

    //无参信号和槽函数连接
    void(Teacher:: *teacherSignal1)() = &Teacher::hungry;
    void(Student:: *studentSlot2)() = &Student::treat;

    connect(teacher,teacherSignal1,student,studentSlot2);

    //信号连接信号
    connect(btn,&QPushButton::clicked,teacher,teacherSignal1);

    //断开信号
    //disconnect(teacher,teacherSignal1,student,studentSlot2);

    //拓展
    //1、信号是可以连接信号
    //2、一个信号可以连接多个槽函数
    //3、多个信号 可以连接 同一个槽函数
    //4、信号和槽函数的参数 必须一一对应
    // 信号的参数个数 可以多余 槽函数参数个数

    //Qt4版本以前的信号和槽连接方式
    //利用Qt4信号槽 连接无参版本
    //connect(teacher,SIGNAL(hungry()),student,SLOT(treat(QString)));
    //Qt4版本优点： 参数直观， 缺点：编译器不会检测参数类型
    //Qt5以上  支持Qt4的版本写法 反之不支持


    //Lambda 表达式  [] () {}
//    QPushButton* btn2 = new QPushButton;
//     [btn](){
//        btn->setText("AAAA");
//        btn2->setText("sss"); //btn2 看不到
//    }();



//    QPushButton* mybtn1 = new QPushButton(this);
//    QPushButton* mybtn2 = new QPushButton(this);
//    mybtn1->move(300,100);
//    mybtn2->move(400,100);
//    int m = 10;
//    //. mutable 修饰 值传递变量， 可以修改拷贝出的数据，改变不了本体
//    connect(mybtn1,&QPushButton::clicked,this,[m]()mutable{m = 100 + 10;qDebug()<<m;});
//    connect(mybtn2,&QPushButton::clicked,this,[=]()mutable{qDebug()<<m;});
//    qDebug()<<m;


    //Lambda 表达式 返回值接收
//    int ret = []()->int{return 1000;}();
//    qDebug()<<"ret = "<<ret;


    //利用Lambda 实现单击按钮 关闭窗口 并触发下课
    QPushButton* MyBtn = new QPushButton("关闭",this);
    MyBtn->move(300,300);
    connect(MyBtn,&QPushButton::clicked,this,[=](){
        this->close();
        this->classIsOver()
       });
}

void Widget::classIsOver()
{
    //下课函数，调用后触发 老师饿了信号
    //emit teacher->hungry();

    emit teacher->hungry("宫保鸡丁");
}

Widget::~Widget()
{

}
