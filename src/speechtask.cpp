#include "speechtask.h"
#include "ui_speechtask.h"
#include "inpout32.h"

SpeechTask::SpeechTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpeechTask)
{
    ui->setupUi(this);
    setting = new QSettings(iniFilePath, QSettings::IniFormat);

    this->setStyleSheet("*{border:1px solid}");
    init();

    connect(this, &SpeechTask::stateChanged, this, &SpeechTask::sendToLPT);

}

SpeechTask::~SpeechTask()
{
    delete ui;
}

void SpeechTask::init()
{
    initPort();

    // 背景色
    this->setStyleSheet("background-color:black;"
                        "color:white");
    // 标题
    QString txt_title = "语义识别任务";
    this->lab_title = new QLabel(this);
    this->lab_title->setText(txt_title);
    this->lab_title->setAlignment(Qt::AlignCenter);
    this->lab_title->setStyleSheet("QLabel{font-size:34px;font:bold;border:1px solid}");

    // 任务说明
    QString txt_description = "任务说明：\n\n任务开始，第一个阶段为准备阶段，屏幕中心会出现一个十字，在此期间请将注意力集中再十字上，十字将持续显示3秒。\n\n第二阶段出现口令，你需要在口令出现时，用标准的普通话大声、清晰地读出口令的内容，口令将持续显示2秒。\n\n第三阶段为空白阶段，等待下一个口令，此阶段持续2秒。\n\n注意：在任务过程中，请尽量不要发出杂音。";
    this->lab_description = new QLabel(this);
    this->lab_description->setText(txt_description);
    this->lab_description->setAlignment(Qt::AlignLeft);
    this->lab_description->setStyleSheet("QLabel{font-size:34px;font:bold;}");

    // 底部展示过程
    this->widget_bottom = new QWidget(this);
    this->hlayout = new QHBoxLayout();
    // 添加控件
    lab_img = new QLabel();
    QPixmap pixmap;
    pixmap.load(":/2.jpg");
    lab_img->setPixmap(pixmap);
    lab_img->setAlignment(Qt::AlignCenter);
    this->hlayout->addWidget(lab_img);
    widget_bottom->setLayout(this->hlayout);

    // 整体布局。把控件放到layout里面，然后设置父控件的layout
    this->vlayout = new QVBoxLayout();
    vlayout->addWidget(this->lab_title);
    vlayout->addWidget(this->lab_description);
    vlayout->addWidget(this->widget_bottom);
    this->setLayout(this->vlayout);
    vlayout->setStretchFactor(lab_title, 2);
    vlayout->setStretchFactor(lab_description, 2);
    vlayout->setStretchFactor(widget_bottom, 6);

}

void SpeechTask::mainStage()
{
    lab_cross = new QLabel(this);
    lab_cross ->setText("＋");

    lab_cross->resize(100, 50);
    lab_cross->setAlignment(Qt::AlignCenter);
    lab_cross->setStyleSheet("QLabel{font-size:68px;font:bold;color:white}");

    this->vlayout->addWidget(lab_cross);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SpeechTask::updateStates);

    timer->start(3000);
}

void SpeechTask::deleteAllItems()
{
    //findChildren<QLabel*>()应该只找直属孩子控件

    qDebug() << "deleteAllItems..." << endl;
    // 找到并删除所有label控件
    QList<QLabel*> listLabel = this->findChildren<QLabel*>();
    foreach (QLabel *label, listLabel) {
        delete label;
    }

    QList<QWidget*> listWidget = this->findChildren<QWidget*>();
    foreach (QWidget *widget, listWidget) {
        delete widget;
    }

    // 找到并删除所有layout控件
//    QList<QVBoxLayout*> listLayout = this->findChildren<QVBoxLayout*>();
//    foreach (QVBoxLayout *layout, listLayout) {
//        delete layout;
//    }
    this->setCursor(Qt::BlankCursor);
    mainStage();
    Out32(port, 0);
}

void SpeechTask::initPort()
{
    this->port = setting->value("port").toString().toShort();
    qDebug() << "-=-=-=-port:" << port << endl;
}

void SpeechTask::updateStates()
{
    if(state == 0){ //目前为十字
        emit stateChanged(i+1);
        lab_cross->setText(STIMULATES[i]);
        ++i;
        state = 1; //更新状态为口令
        timer->setInterval(2000);
    }else if(state == 1){ // 目前为口令
        emit stateChanged(50);
        lab_cross->setText("");// 空白
        state = 2;

    }else{  //state == 2    空白
        if(i >= STIMULATES.size()){ //全部口令显示完

            lab_cross->setText("任务结束");
            timer->stop();
            isOver = true;
        }else{
            emit stateChanged(0);
            lab_cross->setText("＋");// 十字
            state = 0;
            timer->setInterval(3000);   // 等待3秒
        }
    }
}

void SpeechTask::sendToLPT(short msg)
{
     Out32(port, msg);
}
