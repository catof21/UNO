#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include <qlinkedlist.h>
#include <qmutex.h>
#include <qtimer.h>
#include "mythread.h"
#include "threadFrame.h"
#include "frameData.h"
#include "table.h"

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = 0);
    ~myserver();
    void StartServer();
    void decrCntP();

signals:

public slots:
   void cleanUp();
protected:
    void incomingConnection(int socketDescriptor);

private:
    QTimer *timer;
    QMutex *lock;
//    int cntP;                //count of Players

//    Table *table;

};

#endif // MYSERVER_H
