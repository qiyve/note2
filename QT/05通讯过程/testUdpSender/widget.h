#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnClear_clicked();

    void on_btnSend_clicked();

    void on_readyRead();
    void on_btnJoin_clicked();

    void on_btnExit_clicked();

    QString getLocalIp();

private:
    Ui::Widget *ui;

private:
    QUdpSocket *m_udpSocket = nullptr;

    QHostAddress groupAddr; //组播地址
};

#endif // WIDGET_H
