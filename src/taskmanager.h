#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "speechtask.h"
#include "slsetting.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);

    void init();

    void runTask();

private:
    SpeechTask *speechTask;
    SLSetting *slSetting;

signals:

};

#endif // TASKMANAGER_H
