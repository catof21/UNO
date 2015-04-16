#ifndef CLI_SOCKET_H
#define CLI_SOCKET_H

#include <QObject>
#include<QTcpSocket>
#include<QDebug>
#include<iostream>
class cli_socket : public QObject
{
    Q_OBJECT

public:
    explicit cli_socket(QObject *parent = 0);
    void Connect();

signals:

public slots:
private:
    QTcpSocket *socket;

};

#endif // CLI_SOCKET_H
