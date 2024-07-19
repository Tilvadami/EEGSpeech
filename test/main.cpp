#include <QApplication>
#include "speechtask.h"
#include "tcpsocket.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);

    SpeechTask task;
//    task.showFullScreen();

    TcpSocket client("127.0.0.1", 1010);
    client.connectToServer();
    client.sendMsg("sada");

    return QApplication::exec();

}
