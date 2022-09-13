#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单栏 只能有一个
    QMenuBar* bar = menuBar();

    //将菜单栏写入窗口
    setMenuBar(bar);

    //设置窗口大小
    resize(600,400);

    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");

    //创建菜单项
    QAction* newfile = fileMenu->addAction("新建");
    //创建分割线
    fileMenu->addSeparator();
    QAction* open = fileMenu->addAction("打开");


    //创建工具栏  工具栏可以有多个
    QToolBar* toolBar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolBar); //设置工具栏位置

    //后期设置只能左右 移动
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //设置浮动
    toolBar->setFloatable(false);

    //设置移动  (总开关)
    toolBar->setMovable(false);

    //工具栏中设置内容
    toolBar->addAction(newfile);
    //添加分割线
    toolBar->addSeparator();
    toolBar->addAction(open);

    //工具栏添加控件
    QPushButton * btn = new QPushButton("AAA",this);
    toolBar->addWidget(btn);



    //状态栏 只能有一个
    QStatusBar* qstatusBar = new QStatusBar();

    //设置到窗口中
    setStatusBar(qstatusBar);

    //放入标签控件
    QLabel* labs = new QLabel("提示信息",this);
    qstatusBar->addWidget(labs);

    //设置右侧提示
    QLabel* labs2 = new QLabel("右侧提示信息",this);
    qstatusBar->addPermanentWidget(labs2);

    //铆接部件 （浮动窗口） 可以有多个
   QDockWidget* dockWidget = new QDockWidget("浮动",this);
   addDockWidget(Qt::BottomDockWidgetArea,dockWidget);

    //设置后期停靠区域
   dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);

    //设置中心部件
   QTextEdit* textEdit= new QTextEdit(this);
   setCentralWidget(textEdit);

}

MainWindow::~MainWindow()
{

}
