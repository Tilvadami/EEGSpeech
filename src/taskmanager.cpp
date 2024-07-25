#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent) : QObject(parent)
{
    runTask();
}

void TaskManager::init()
{

}

void TaskManager::runTask()
{
    slSetting = new SLSetting();
    slSetting->show();
    connect(slSetting, &SLSetting::windowClosed1, [=](){
        speechTask = new SpeechTask();
        speechTask->showFullScreen();
    });
}
