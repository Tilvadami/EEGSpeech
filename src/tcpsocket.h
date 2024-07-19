#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "qdebug.h"


class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr);
    TcpSocket(QString ip, quint16 port);

    void initConnection();

    QString getIp() const;
    void setIp(const QString &value);

    quint16 getPort() const;
    void setPort(const quint16 &value);

    bool connectToServer();

    void sendMsg(QString str);

private:
    // 维护一个套接字
    QTcpSocket *socket = nullptr;

    // 服务器ip和端口
    QString ip = "";
    quint16 port = 0;

signals:

};

#endif // TCPSOCKET_H
