#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击按钮设置值
    connect(ui->btn_set,&QPushButton::clicked,[=](){
        ui->widget->setNum(50);
    });
    //点击按钮打印值
    connect(ui->btn_get,&QPushButton::clicked,[=](){
        qDebug()<<ui->widget->getNum();

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
