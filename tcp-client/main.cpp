#include <QtCore/QCoreApplication>
#include "cli_socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cli_socket Csocket;
    Csocket.Connect();
    return a.exec();
}
