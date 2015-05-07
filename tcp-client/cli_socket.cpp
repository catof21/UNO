/*#include "cli_socket.h"

cli_socket::cli_socket(QObject *parent) :
    QObject(parent)
{
}

void cli_socket::Connect()
{
    socket=new QTcpSocket(this);
    quint16 clientport;
    qDebug() << "Welcome client!";
    std::cout << "Enter the port for connection: ";
    std::cin >> clientport;
    socket->connectToHost("127.0.0.1",clientport);
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected";
        socket->write("start");
        socket->flush();
        socket->waitForBytesWritten(1000);
    } else {
        qDebug() << "Not connected";
    }
    socket->waitForReadyRead(1000);
    if(socket->readLine()=="start\n")
    {
        QString servermove="something";
        while(servermove!="close");
        {
            char move[9];
            socket->waitForReadyRead(3000);
            servermove=socket->readLine();
            qDebug()<<servermove;
            std::cout<<"Enter move: ";
            std::cin>>move;
            socket->write(move);
            socket->flush();
            socket->waitForBytesWritten(1000);
        }
    }
    socket->close();
    socket->waitForDisconnected(3000);
}
*/
