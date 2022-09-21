#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //重写定时器事件
    void timerEvent(QTimerEvent *e);

    int  Id1; //定时器ID
    int  Id2; //定时器ID

    //重写事件过滤器的事件
    bool eventFilter(QObject *, QEvent *);


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
