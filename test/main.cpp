#include <QApplication>
//#include "speechtask.h"
#include "tcpsocket.h"
#include "slsetting.h"
#include "taskmanager.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);

//    SpeechTask task;
//    task.showFullScreen();
//    SLSetting s;
//    s.show();
    TaskManager ma;

    return QApplication::exec();

}
