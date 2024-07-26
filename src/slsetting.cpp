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
    }else{  //配置文件不存在
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
    if(port == ""){ // 检查是否为空
        QMessageBox::warning(this,
                             tr("端口号为空"),
                             tr("您还未填写端口号，请填写端口号"),
                             QMessageBox::Ok);
    }else if(port.toInt() < 1024 || port.toInt() > 65535){    // toInt()是为了检查是否超出端口范围。不是用int类型
        QMessageBox::warning(this,
                             tr("端口号超出范围"),
                             tr("您所填写的端口号超出范围，请填写1024~65535之间的数字"),
                             QMessageBox::Ok);
    }else{
        setting->setValue("port", port);
        emit windowClosed1();
        this->close();
    }

}
