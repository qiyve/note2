#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    // QPixmap 绘图设备 专门为平台做了显示的优化
//    QPixmap pix(300,300);
//    //填充颜色
//    pix.fill(QColor(Qt::white));
//    //声明画家
//    QPainter painter(&pix);
//    painter.setPen(Qt::green);  //设置画笔颜色
//    painter.drawEllipse(QPoint(150,150),100,100); //画圆

//    //保存
//    pix.save("D:/s/p.png");

    ////////////////////QImage 绘图设备////////////////////////////////

//    // QImage 绘图设备  可以对象进行访问
//    QImage image(300,300,QImage::Format_RGB32);
//    //填充颜色
//    image.fill(QColor(Qt::white));
//    //声明画家
//    QPainter painter(&image);
//    painter.setPen(Qt::red);
//    painter.drawEllipse(QPoint(150,150),100,100); //画圆

//    image.save("D:/s/image.png");



    //////////////QPicture///////////////////////////////////

    //QPicture 绘图设备 可以记录和重现绘图指令

    QPicture pic;
    QPainter painter;
    painter.begin(&pic); //开始在pic上画
    painter.setPen(Qt::red);
    painter.drawEllipse(QPoint(150,150),100,100); //画圆

    painter.end();  //结束画画
    pic.save("D:/s/pic.xx");

}

//绘图事件
 void Widget::paintEvent(QPaintEvent *event)
 {
//     QPainter painter(this);

//     //利用QImage 对像素进行修改
//     QImage img;
//     img.load("D:\\s\\p.png");
//     for(int i = 100; i < 350; i++)
//     {
//         for(int j = 50; j < 150; j++)
//         {
//             QRgb value = qRgb(255,200,100);
//             img.setPixel(i,j,value);
//         }
//     }

//     painter.drawImage(0,0,img);



      QPainter painter(this);
     // QPicture 重现绘图指令
      QPicture pic;
      pic.load("D:/s/pic.xx");
      painter.drawPicture(0,0,pic);

 }

Widget::~Widget()
{
    delete ui;
}
