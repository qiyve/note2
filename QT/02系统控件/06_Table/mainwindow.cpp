#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TableWidget 控件
    //设置列数
    ui->tableWidget->setColumnCount(3);

    //设置水平头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"年龄");

    //设置列数
    ui->tableWidget->setRowCount(5);

    //设置正文
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("赵云"));

    QStringList nameList;
    nameList<<"赵飞"<<"赵云"<<"刘备"<<"关羽"<<"花木兰";
    QList<QString> list;
    list<<"男"<<"男"<<"男"<<"男"<<"女";

    for(int i = 0; i<5; i++)
    {
        int a = 0 ;
        ui->tableWidget->setItem(i,a++,new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i,a++,new QTableWidgetItem(list.at(i)));
        ui->tableWidget->setItem(i,a++,new QTableWidgetItem(QString::number(i+18)));

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
