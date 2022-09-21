#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置单选按钮 默认选择
    ui->radioButton_Man->setChecked(true);

    //选择女后 打印信息
    connect(ui->radioButton_Girl,&QRadioButton::clicked,[=](){
        qDebug()<<"它是女的";
    });

    //多选按钮 2是选中  1是半选   0未选中
    connect(ui->cBox,&QCheckBox::stateChanged,[=](int state){
        qDebug()<<state;
    });

    //利用QListWidgetItem 写诗
//    QListWidgetItem* item = new QListWidgetItem("锄禾日当午");
//    ui->listWidget->addItem(item);
//    item->setTextAlignment(Qt::AlignHCenter);


    //通过 QStringList QList<QString>  一次性写入
    QStringList list;
    list<<"锄禾日当午"<<"汗滴禾下土";
    ui->listWidget->addItems(list);





}

MainWindow::~MainWindow()
{
    delete ui;
}
