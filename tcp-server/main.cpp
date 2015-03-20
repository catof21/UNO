#include <QCoreApplication>
#include <gameserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameServer gserver;
    gserver.startServer();

    return a.exec();
}
