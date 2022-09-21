#include "smallwidget.h"
#include "ui_smallwidget.h"
#include <QDebug>

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);

    // QSpinBox 移动 QSlider 跟着滑动
    void(QSpinBox:: *spSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spSignal,ui->horizontalSlider,QSlider::setValue);


    // QSlider 滑动  QSpinBox 跟着移动
    void(QSlider:: *slSignal)(int) = &QSlider::valueChanged;
    connect(ui->horizontalSlider,slSignal,ui->spinBox,QSpinBox::setValue);

}

//设置值
void SmallWidget::setNum(int Value)
{
    ui->spinBox->setValue(Value);
}

//获取值
int SmallWidget::getNum()
{
   return ui->spinBox->value();
}

SmallWidget::~SmallWidget()
{
    delete ui;
}
