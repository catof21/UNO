#include "mythread.h"
#include "myserver.h"
#include "table.h"

QMutex lock;

mythread::mythread(QMutex *lk, int *frm, int ID, QLinkedList<frameData> *dat, QLinkedList<threadFrame> *list, Table *t, QObject *parent, int playerid, int conn, int maxplayer) :
QThread(parent)
{
    this->socketDescriptor = ID;
    this->sendData = dat;
    this->sysFrameList = list;
    this->frame = *frm;
    this->sysFrame = frm;
    this->table = t;
    this->lock = lk;
    this->playerid = playerid;
    this->conn = conn;
    this->maxplayer = maxplayer;

}

void mythread::run()
{
    //thread starts here
    threadFrame myFrame;
    QTimer *timer = new QTimer(0);


    timer->start(10);
    qDebug() << socketDescriptor << "Starting thread";
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    myFrame.frame = *sysFrame;
    myFrame.socketDescriptor=this->socketDescriptor;
    sysFrameList->append(myFrame);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUp()),Qt::DirectConnection); //still need this.
    connect(this,SIGNAL(timeSig()),this,SLOT(readyWrite()),Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client connected.";
    QMutex lock;



    exec(); //thread will stay alive until we tell it to close
}


void mythread::readyRead()
{
    frameData tempData;
    QByteArray stuff = socket->readAll();
    qDebug() << stuff;
    QString stuffText,testName, msgTemp;
    stuffText.clear();
    qDebug() << socketDescriptor << "Data in: " << stuff;



    if(stuff=="REG\n") // set client username internal to the thread. No need to do much else.
    {
        if (conn == 1) {
            if(-1==socket->write("ACK"))                                //reg
            {
                    qDebug() << "error2";
            }
            socket->flush();
            msgTemp.clear();
            socket->waitForReadyRead();
            stuff=socket->readAll();
            name=stuff;

            msgTemp.append("L");                                        //login
            msgTemp.append(QString::number(playerid).at(0));
            msgTemp.append(QString::number(maxplayer).at(0));
            if (playerid == maxplayer) {                                //ha elérjük a maxplayert, akkor osztunk
                        qDebug() << "maxplayer reached!";
                }

            } else if (conn == 0){
            if(-1==socket->write("EXIT"))
            {
                    qDebug() << "error3";
            }
            socket->flush();
            socket->waitForReadyRead();

        }

    }


    if(stuff=="MSG\n") //client would like to send a message.
    {

        socket->waitForReadyRead();
        stuff=socket->readAll();
        msgTemp.clear();
        QString str;
        str.clear();
        char *command = stuff.data();
        char cmd[stuff.length()];
        int i=0;
        while (*command) {
                cmd[i] = *command;
                ++command;
                ++i;
        }
        if (cmd[1] == 'P') {
            qDebug() << "play";
            table->Play(playerid, cmd[2],cmd[3],cmd[4]);
            if(cmd[0]=='1'){
                table->SayUno(playerid);
            }
            table->SetNextPlayer();
        }
        else if (cmd[1] == 'D'){
            qDebug() << "draw";
            table->DrawEnough(playerid);
            table->SetNextPlayer();
            if(cmd[0]=='1'){
                table->SayUno(playerid);
            }

        }else {
            qDebug() << "update"<<playerid;
        }

        str.append((table->Send(playerid)));
        msgTemp.append(str);
    }


        lock->lock(); //I'm messing with the shared memory here... make sure to lock

        tempData.setData(msgTemp.toUtf8());
        tempData.setFrame(*sysFrame);
        sendData->append(tempData);
        (*sysFrame)++;
        lock->unlock();
    }






void mythread::disconnected()
{
    //THIS IS WHERE YOU ARE
    QLinkedList<threadFrame>::iterator fit;
    qDebug() << "Client " << socketDescriptor << "has disconnected from the server.";
    //remover the thread from the list of frames... because if the thread isn't removed, then the system cleanup will never be able to work right.
    lock->lock(); //I only want one person playing around with the shared variables.
    for(fit=sysFrameList->begin();fit!=sysFrameList->end();fit++)
    {
        //search for yourself in the list, remove yourself.
        if(fit->socketDescriptor == this->socketDescriptor)
        {
            //found myself, need to remove.
            sysFrameList->erase(fit);
            break; //memory accesss issues if you erase something then do not break.
        }
    }
    lock->unlock();
    socket->deleteLater();
    mythread::exit();
}



void mythread::readyWrite()
{
    //this method will compare the thread's current frame with what's in the sendData memory. if the frame that's in there is equal to or greater than the frame, the method will send that data. the messages should be in order, anyway.
    QLinkedList<frameData>::iterator it;
    QLinkedList<threadFrame>::iterator fit;
    QString response;
    lock->lock();
    for(it=sendData->begin();it!=sendData->end();it++)
    {
        if(it->getFame()==this->frame) // using == because the increment each time through will cause the == to change and I don't want to repeat messages
        {
            response = it->getData();
            socket->write(response.toUtf8());
            socket->flush();
            //doing an ACK to synchronize when the client expects more data.
            this->frame++;
        }
    }

    //have to update system level frame number. otherwise issues.
    for(fit=sysFrameList->begin();fit!=sysFrameList->end();fit++)
    {
        if(fit->socketDescriptor==this->socketDescriptor)
        {
            //found this thread
            fit->frame = this->frame;

        }
    }
    lock->unlock();
}


void mythread::timeUp() //probably does not need to be remade.
{
    emit timeSig();
}
