#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //栈控件使用 stackedWidget

    //设置默认显示
    ui->stackedWidget->setCurrentIndex(1);

    //scrollArea 按钮
    connect(ui->btn_scrollArea, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);});

    //tabWidget 按钮
    connect(ui->btn_tabWidget, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);});

    //toolBox 按钮
    connect(ui->btn_toolBox, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);});

    //下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("奥迪");

    //点击按钮 显示奥迪
    connect(ui->btn_Ad, &QPushButton::clicked,[=](){
        ui->comboBox->setCurrentIndex(2);
    });

    //利用QLabel 显示图片
    ui->label->setPixmap(QPixmap(":/s.png"));

    //利用QLabel 显示gif 动图
    QMovie* movie = new QMovie(":/th.gif");
    ui->label_gif->setMovie(movie);

    //播放动图
    movie->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}
