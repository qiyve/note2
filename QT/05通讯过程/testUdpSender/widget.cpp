#include "widget.h"
#include "ui_widget.h"
#include <QHostInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    QString localIP = getLocalIp();//获取IP地址
    this->setWindowTitle(this->windowTitle()+"--用户2:"+localIP);

    m_udpSocket = new QUdpSocket(this);

    //组播的数据的生存期，数据报每跨1个路由就会减1.表示多播数据报只能在同一路由下的局域网内传播
    m_udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption,1);
    connect(m_udpSocket,&QUdpSocket::readyRead,this,&Widget::on_readyRead);

    ui->comboBox->addItem("239.22.0.1");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_btnSend_clicked()//组播
{
    //目标端口
    quint16 groupPort = ui->spinBindPort->value();

    //拼接用户及消息
    QString msg = ui->lineEdit->text();
    QByteArray str = msg.toUtf8();
    QByteArray name = QString("用户2:").toUtf8();

    ui->lineEdit->clear();

    //发出数据报
    m_udpSocket->writeDatagram(name + str,groupAddr,groupPort);

    //ui->plainTextEdit->appendPlainText("[multicast] "+msg);
}

void Widget::on_readyRead()
{
    //读取数据
    while(m_udpSocket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(m_udpSocket->pendingDatagramSize());

        QHostAddress peerAddr;
        quint16 peerPort;

        //读取数据 获取端口 IP
        m_udpSocket->readDatagram(data.data(),data.size(),&peerAddr,&peerPort);

        //显示接受到数据
        QString str = data.data();
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnJoin_clicked()
{    
    QString IP = ui->comboBox->currentText(); //获取组播IP
    groupAddr = QHostAddress(IP);

    quint16 groupPort = ui->spinBindPort->value(); //端口

    //清空m_udpSocket缓存
    m_udpSocket->close();

    //加入组播之前，必须先绑定端口，端口为多播组统一的一个端口。
    if(m_udpSocket->bind(QHostAddress::AnyIPv4,groupPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
    {
        //加入组播
        m_udpSocket->joinMulticastGroup(groupAddr);

        ui->plainTextEdit->appendPlainText("**加入组播成功");
        ui->plainTextEdit->appendPlainText("**组播IP: "+ IP);
        ui->plainTextEdit->appendPlainText("**绑定端口: "+QString::number(groupPort));

        //空间 解/锁
        ui->btnSend->setEnabled(true);
        ui->btnJoin->setEnabled(false);
        ui->btnExit->setEnabled(true);
        ui->comboBox->setEnabled(false);
    }
    else
    {
        ui->plainTextEdit->appendPlainText("**绑定端口失败");
    }
}

void Widget::on_btnExit_clicked()
{
    //退出组播
    m_udpSocket->leaveMulticastGroup(groupAddr);

    //解除绑定
    m_udpSocket->abort();

    ui->btnSend->setEnabled(false);
    ui->btnJoin->setEnabled(true);
    ui->btnExit->setEnabled(false);
    ui->comboBox->setEnabled(true);

    ui->plainTextEdit->appendPlainText("Exit");
}

QString Widget::getLocalIp()
{
    //获取本机IP
    QString hostName = QHostInfo::localHostName();//本机主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QString localIP = " ";
    QList<QHostAddress> addList = hostInfo.addresses();
    if(!addList.isEmpty())
    {
        for(int i=0;i<addList.count();++i)
        {
            QHostAddress aHost = addList.at(i);
            if(QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                localIP = aHost.toString();
                break;
            }
        }
    }
    return localIP;
}
