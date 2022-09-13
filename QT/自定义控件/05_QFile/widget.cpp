#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击选择文件按钮  弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){

        //打开文件
        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\86175\\Desktop");
        //将路径放入 lineEdit
        ui->lineEdit->setText(path);

        //编码格式类
        //QTextCodec* codec = QTextCodec::codecForName("gbk");

        //将读取的内容放入 textEdit对话框中
        //QFile 默认支持的格式是UIT_8
        QFile file(path); //参数就是文件路径

        //设置打开方式
        file.open(QIODevice::ReadOnly);
        //QByteArray array = file.readAll();

        QByteArray array;
        while (!file.atEnd())
        {
           //按行读取
           array += file.readLine();

        }
        //将文件内容写入 text 对话框
        ui->textEdit->setText(array);
        //ui->textEdit->setText(codec->toUnicode(array));

        //关闭文件
        file.close();


//        //写入内容
//        file.open(QIODevice::Append); //追加方式打开
//        file.write("啊啊啊");
//        file.close();


        //QFileInfo
        QFileInfo info(path);
        qDebug() <<"大小："<<info.size()<<"后缀名："<<info.suffix()<<"文件路径:"<<info.filePath()<<"文件名:"<<info.fileName();
        qDebug()<<"创建日期:"<<info.created().toString("yyyy/MM/dd hh:mm:ss");
        qDebug()<<"修改日期:"<<info.lastModified().toString("yyyy/MM/dd hh:mm:ss");

    });


}

Widget::~Widget()
{
    delete ui;
}
