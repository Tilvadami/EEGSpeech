#include <QApplication>
#include "speechtask.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);

    SpeechTask task;
    task.showFullScreen();

    return QApplication::exec();

}
