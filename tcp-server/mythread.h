#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QMutex>
#include <QByteArray>
#include <QLinkedList>
#include <qtimer.h>
#include "frameData.h"
#include "threadFrame.h"
#include "table.h"

using namespace::std;

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(QMutex *lk, int *frm, int ID, QLinkedList<frameData> *dat, QLinkedList<threadFrame> *list, Table *t, QObject *parent = 0, int playerid = 0, int connect=0, int maxplayer=0);
    void run();
    //QLinkedList<Data> data;
   // QLinkedList<User> users;



signals:
    void error(QTcpSocket::SocketError sockError);
    void readyWriteSig();
    void timeSig();



public slots:
    void readyRead();
    void disconnected();
    void readyWrite();
    void timeUp();
private:
    QTcpSocket *socket;
    int socketDescriptor;
    QLinkedList<frameData> *sendData;
    QLinkedList<threadFrame> *sysFrameList;
    int frame;
    int *sysFrame;
    Table *table;
    QString name;
    QMutex *lock;
    int playerid;
    int conn;
    int maxplayer;


};

#endif // MYTHREAD_H
