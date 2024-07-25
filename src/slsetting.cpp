#include "slsetting.h"
#include "ui_slsetting.h"

SLSetting::SLSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SLSetting)
{
    ui->setupUi(this);
    this->setWindowTitle("配置");
    setting = new QSettings(iniFilePath, QSettings::IniFormat);

    init();

    connect(this->ui->ok_btn, &QPushButton::clicked, this, &SLSetting::writeToIni);

}

SLSetting::~SLSetting()
{
    delete ui;
}

void SLSetting::init()
{
    QFile file(this->iniFilePath);
//    QSettings setting("./LPTport.ini", QSettings::IniFormat);
    if(file.exists()){  //配置文件存在
        QString port_str = setting->value("port").toString();
        qDebug() << "port:" << port_str << endl;
        this->ui->portEdit->setText(port_str);
        this->ui->tishi->setText("配置文件已读取");
    }else{
        this->ui->tishi->setText("配置文件不存在");
        // 则创建文件
        if(file.open(QIODevice::WriteOnly)){
            file.close();
            qDebug() << "创建文件..." << endl;
        }
    }
}

void SLSetting::writeToIni()
{
    QString port = ui->portEdit->text();
    setting->setValue("port", port);
    emit windowClosed1();
    this->close();
}
