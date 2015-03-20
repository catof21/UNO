#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "mythread.h"


class QNetworkSession;

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit GameServer(QObject *parent = 0);

signals:

private slots:
    void SessionOpened();
    void sendCard();

private:
    QNetworkSession *networkSession;
    QStringList cards;
//    QTcpServer *tcpServer;

//protected:
//    void incomingConnection(qintptr socketDescriptor);


};

#endif // GAMESERVER_H

