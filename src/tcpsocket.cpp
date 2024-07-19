#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    initConnection();
}

TcpSocket::TcpSocket(QString ip, quint16 port)
{
    socket = new QTcpSocket(this);
    initConnection();
    setIp(ip);
    setPort(port);
}

void TcpSocket::initConnection()
{
    connect(socket, &QTcpSocket::connected, [=](){
        qDebug() << "连接成功！！" << endl;
    });

    connect(socket, &QTcpSocket::readyRead, [=](){
        QString str = socket->readAll();
        qDebug() << "抄收服务器消息：" << str << endl;
    });
}

QString TcpSocket::getIp() const
{
    return ip;
}

void TcpSocket::setIp(const QString &value)
{
    ip = value;
}

quint16 TcpSocket::getPort() const
{
    return port;
}

void TcpSocket::setPort(const quint16 &value)
{
    port = value;
}

bool TcpSocket::connectToServer()
{
    if(ip == "" || port == 0){
        qDebug() << "无法连接，因为ip或port不存在" << endl;
        return false;
    }
    // 建立连接
    socket->connectToHost(ip, port);
    qDebug() << "1231231";
    return true;
}

void TcpSocket::sendMsg(QString str)
{
    if(nullptr == socket)
        return;
    socket->write(str.toUtf8().data());
}
