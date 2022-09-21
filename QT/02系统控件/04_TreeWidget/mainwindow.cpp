#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置水平头
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");

    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem* minItem = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem* zhitem = new QTreeWidgetItem(QStringList()<<"智力");
    //设置顶层节点
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhitem);

    QStringList heroL1,heroL2,heroM1,heroM2,heroZ1,heroZ2;
    heroL1<<"钢背猪"<<"坦克 有出色的抗伤能力";
    heroL2<<"熊猫"<<"战士, 有一定坦度输入稳定";
    heroM1<<"小鱼人"<<"刺客, 偷敌方属性强化自身";
    heroM2<<"月骑"<<"射手, 生存较低有弹射攻击";
    heroZ1<<"巫医"<<"辅助, 群体治疗";
    heroZ2<<"巫妖"<<"法师, 有较高爆发技能";

    //追加子节点
    QTreeWidgetItem* l1 = new QTreeWidgetItem(heroL1);
    liItem->addChild(l1);
    QTreeWidgetItem* l2 = new QTreeWidgetItem(heroL2);
    liItem->addChild(l2);
    QTreeWidgetItem* m1 = new QTreeWidgetItem(heroM1);
    minItem->addChild(m1);
    QTreeWidgetItem* m2 = new QTreeWidgetItem(heroM2);
    minItem->addChild(m2);
    QTreeWidgetItem* z1 = new QTreeWidgetItem(heroZ1);
    zhitem->addChild(z1);
    QTreeWidgetItem* z2 = new QTreeWidgetItem(heroZ2);
    zhitem->addChild(z2);
}


MainWindow::~MainWindow()
{
    delete ui;
}
