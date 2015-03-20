#include "gameserver.h"

#include <stdlib.h>
#include <QtNetwork>

GameServer::GameServer(QObject *parent) :
    QTcpServer(parent)
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("QTPorject"));
        settings.beginGroup(QLatin1String("QTNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

    }
}

void GameServer::startServer()
{

    int port=1234;

    if(!this->listen(QHostAddress::Any,port)){

                qDebug() << "Server could not start!";

            }else{

                qDebug() << "Server started!";
            }
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor <<"Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);

    connect(thread,SIGNAL(finished()),thread, SLOT(deleteLater()));

    thread->start();
//    thread->write();

//    socket->flush();
//    socket->waitForBytesWritten(3000);
//    socket->close();

}
