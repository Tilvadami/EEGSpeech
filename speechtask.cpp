#include "speechtask.h"
#include "ui_speechtask.h"

SpeechTask::SpeechTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpeechTask)
{
    ui->setupUi(this);
}

SpeechTask::~SpeechTask()
{
    delete ui;
}
