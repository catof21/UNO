#include "gameserver.h"



GameServer::GameServer(QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << "Welcome to Server";
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newconnection()));
    quint16 serverport;
    std::cout << "Enter the port number:";
    std::cin >> serverport;
    if(!server->listen(QHostAddress::Any,serverport))
        {
        std::cout<<"Server could'nt started\n";
    } else {
        std::cout<<"Server started\n";
    }

}

void GameServer::newConnection()
{
    QTcpSocket *socket=server->nextPendingConnection();
    socket->waitForReadyRead(5000);
    if(socket->readLine()=="start")
    {
        qDebug()<<"start";
        socket->write("start");
        socket->flush();
        QString clientmove="something";
        while(clientmove!="close")
        {
            char move[9];
            std::cout<<"Enter the move: ";
            std::cin >>move;
            socket->write(move);
            socket->flush();
            socket->waitForBytesWritten(10000);
            socket->waitForReadyRead(30000);
            clientmove=socket->readLine();
            qDebug()<<clientmove;
        }
    }

}


