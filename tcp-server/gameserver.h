#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit GameServer(QObject *parent = 0);

signals:

private slots:
    void newConnection();


private:
//    QNetworkSession *networkSession;
//    QStringList cards;
    QTcpServer *server;


//protected:
//    void incomingConnection(qintptr socketDescriptor);


};

#endif // GAMESERVER_H

