#ifndef SLSETTING_H
#define SLSETTING_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include <QString>
#include "qdebug.h"

namespace Ui {
class SLSetting;
}

class SLSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SLSetting(QWidget *parent = nullptr);
    ~SLSetting();

    void init();

public slots:
    void writeToIni();

signals:
    void windowClosed1();

private:
    Ui::SLSetting *ui;

    const QString iniFilePath = "LPTport.ini";

    QSettings *setting;

};

#endif // SLSETTING_H
