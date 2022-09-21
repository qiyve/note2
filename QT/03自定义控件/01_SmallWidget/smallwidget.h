#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>

namespace Ui {
class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = 0);
    ~SmallWidget();

    //设置值
    void setNum(int Value);

    //获取值
    int getNum();

private:
    Ui::SmallWidget *ui;
};

#endif // SMALLWIDGET_H
