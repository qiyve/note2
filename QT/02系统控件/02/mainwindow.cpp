#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击按钮创建一个对话框
    connect(ui->actionNew,&QAction::triggered,[=](){
        //对话框分类
        //模态对话框（不可以对其他窗口操作） 非模态对话框(可以对其他窗口进行操作）
        //模态创建 阻塞
//        QDialog dlg(this);
//        dlg.resize(200,100);
//        dlg.exec();
//        qDebug()<<"模态对话框弹出";

        //非模态创建   需要创建在堆区 避免代码执行完 被释放掉
//        QDialog* dlg2 = new QDialog(this);
//        dlg2->resize(200,100);
//        dlg2->show();
//        //设置属性 对话框 关闭后自动释放堆区
//        dlg2->setAttribute(Qt::WA_DeleteOnClose); 55号//属性
//        qDebug()<<"拟态对话框弹出";


        //消息对话框
        //错误对话框
        //QMessageBox::critical(this,"critical","错误");

        //信息对话框
        //QMessageBox::information(this,"info","提示");

        //提问对话框
        //参数1 父类指针 参数2 标题 参数3 提示内容 参数4 按键类型  参数5 默认关联回车按键
//        if(QMessageBox::Ok == QMessageBox::question(this,"quse","提问", QMessageBox::Ok|QMessageBox::No,QMessageBox::No))
//        {
//            qDebug()<<"用户选择的是OK";
//        }
//        else
//        {
//           qDebug()<<"用户选择的是NO";
//        }

        //警告对话框
        //QMessageBox::warning(this,"warning","警告");

//        //其他对话框
//        //颜色对话框
//        QColor color = QColorDialog::getColor(QColor(255,0,0));
//        qDebug()<<"r = "<<color.red()<<"g = "<<color.green()<<"b"<<color.blue();

          //文件对话框
          QString str = QFileDialog::getOpenFileName(this,"打开文件","D:\\","*.txt");
          qDebug()<<str;

          //字体对话框
//        bool flag;
//        QFont font = QFontDialog::getFont(false,QFont("黑体",72));
//        qDebug()<<"字体"<<font.family()<<"字体"<<font.pointSize()<<"是否倾斜"<<font.italic();

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
