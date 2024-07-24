#ifndef SPEECHTASK_H
#define SPEECHTASK_H

#include <QWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QList>
#include <QTimer>
#include <QVector>
#include <QPixmap>

#include "qdebug.h"
#include "tcpsocket.h"
extern "C" {
    #include "inpout32.h"
}

namespace Ui {
class SpeechTask;
}

class SpeechTask : public QWidget
{
    Q_OBJECT

public:
    explicit SpeechTask(QWidget *parent = nullptr);
    ~SpeechTask();
    // 初始化
    void init();
    // 任务环节
    void mainStage();
    // 删除所有控件
    void deleteAllItems();

private:

    const QVector<QString> STIMULATES = {"塔台","地面","收到","申请","放行","雷达",
                                        "跑道","高度","军航","进近","标准","推出",
                                        "正常","直飞","应答机","爬升","检查","左","右",
                                        "联系","天气","重复","发动机","离场","滑出","气压",
                                        "复飞","着陆","航向","保持","零","一","二","三",
                                        "四","五","六","七","八","九"};

    Ui::SpeechTask *ui;

    QLabel *lab_title;
    QLabel *lab_description;
    QLabel *lab_startTip;

    QVBoxLayout *vlayout;

    QWidget *widget_bottom;
    QLabel *lab_img;
    QHBoxLayout *hlayout;

    QLabel *lab_cross;
    QLabel *lab_stimulate;

    bool isStart = false;

    QTimer *timer;

    int state = 0; // 状态机。初始化为0，表示目前为十字

    int i = 0; // STIMULATES下标，从0开始，顺序迭代.

    TcpSocket *tcpSocket;

    short port;

public slots:
     void updateStates();

     void sendToLPT(short msg);

signals:
     void stateChanged(short msg);

protected:
    // 重写按键事件
    void keyPressEvent(QKeyEvent *event) override{
        // 重写esc按键事件逻辑
        if(event->key() == Qt::Key_Escape){
            close();
        }else if(event->key() == Qt::Key_Space){
            // 检查任务是否开始或结束
            if(!isStart){
                deleteAllItems();
                isStart = true;
            }
        }else{
            QWidget::keyPressEvent(event);  //如果是其他按键事件就交给keyPressEvent
        }
    }

};

#endif // SPEECHTASK_H
