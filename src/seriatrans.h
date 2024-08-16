#ifndef SERIATRANS_H
#define SERIATRANS_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
//#include <libusb>

class SeriaTrans : public QObject
{
    Q_OBJECT
public:
    explicit SeriaTrans(QObject *parent = nullptr);
    void convertStringToHexString(const QString &str, QByteArray &byteData);
    char convertCharToHex(char ch);

signals:

};

#endif // SERIATRANS_H
