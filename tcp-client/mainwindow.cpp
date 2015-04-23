#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startdialog.h"
#include <qthread.h>
#include "table.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //bool flag;
    serverAddr = new QString;
    serverPort = new int;
    userName = new QString;
    table = new Table;
    startDialog start(serverAddr, serverPort, userName,this);
    start.setModal(true);
    start.exec();


    //flag = MainWindow::Connect();
    ui->setupUi(this);
    //if(!flag)
    //{
    //    ui->textBrowser->setText("Unable to connect to server. Please restart client to try again.");
    //}
    //else
    //{
     //   ui->textBrowser->setText("Successfully connected");
    //}*/

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));

    socket = new QTcpSocket(this);
   connect(socket, SIGNAL(connected()), this, SLOT(clientConnected()));
   connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
//    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
  // connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
 //  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
   socket->connectToHost(*serverAddr,*serverPort);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serverAddr;
    delete serverPort;
    delete userName;
    delete socket;
    delete table;
}


void MainWindow::clientConnected()
{
//you are now connected, continue with your execution
    for(int i=0;i<10000000;i++); //waste time for thread on server to setup

   connect(socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
   socket->write("REG\n");
   socket->flush();
   socket->waitForReadyRead();
   socket->readAll();
   socket->write(userName->toUtf8());
   socket->flush();
   socket->waitForReadyRead();
   socket->readAll();
   m_bUserNameSend = true;
   ui->textBrowser->setText("Successfully connected.\n");
}


/*bool MainWindow::Connect()
{
    bool flag=false;
    QString tempString;
    socket->connectToHost(*serverAddr,*serverPort);
    if(!socket->waitForConnected())
       flag = false;
    else flag=true;
    if(flag)
    {//attempt to register user with name
        socket->write("REG\n");
        socket->flush();
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead();
        tempString = socket->readAll();
        if(tempString == "ACK")
        {
            socket->write(userName->toUtf8());
            socket->flush();
            tempString.clear();
            socket->waitForReadyRead();
            tempString = socket->readAll();
            if(tempString=="ACK")
            {
                return true;
            }
            else return false;
        }
        else return false;
       }
    else return false;
}*/



/*void MainWindow::readyRead()
{
    //client has now been told by the socket that there is data to be ready that is not a part of the sending or registering. cool
    QString temp,browsTemp;
    temp=socket->readAll();
    ui->textBrowser->append(temp);
    ui->textBrowser->repaint();
    temp.clear();
}*/

void MainWindow::readyRead()
{
// handle the readyRead signal
   QString tempString = socket->readAll();

   if (tempString != "ACK") {
          ui->textBrowser->clear();
          ui->textBrowser->append("U(pdate) | P(lay) | D(raw) | X(UNO)");
          table->playedCard.setNumber(tempString.at(0));
          table->playedCard.setColor(tempString.at(1));
          table->playedCard.setColor2(tempString.at(2));
          QChar a = tempString.at(3);
          if ( a == '0') {
              table->action=false;
          } else {
              table->action=true;
          }
          qDebug() << tempString.at(0);
          qDebug() << tempString.at(1);
          qDebug() << tempString.at(2);
          qDebug() << tempString.at(3);
          qDebug() << tempString.at(4);
          ui->textBrowser->append("Hívó lap:");
          ui->textBrowser->append(table->playedCard.Send().toUtf8());
          ui->textBrowser->append("\nKézben lévő lapok:");
          Card c;
           for(int i=4;i<tempString.length();i=i+3) {
               c.setNumber(tempString.at(i));
               c.setColor(tempString.at(i+1));
               c.setColor2(tempString.at(i+2));
               table->Hand.push_back(c);
               ui->textBrowser->append(c.Send().toUtf8());
           }

   } else {
    ui->textBrowser->append(tempString);
   }
   qDebug() << "readyread" << tempString;
   ui->textBrowser->repaint();
}
void MainWindow::on_pushButton_clicked()
{
    //user clicked the send button and would like their message to be sent. woooo.
    QString temp, stuff;
    temp=ui->lineEdit->text();
    if (temp.at(0)=='P') {
        QChar c=temp.at(1);
        QChar n=temp.at(2);
        if(table->Play(n, c)==0){                           //ha játszható
           if (c=='W')   {
              createMessage(temp);
           } else {
              createMessage(temp.append(temp.at(1)));       //ha nincs megadva második szín, akkor a lap színét teszi be másodiknak
           }
        }else{
            ui->textBrowser->append("Válassz másik lapot!");  //miért nem case->
            ui->lineEdit->clear();
        }
    }
    else if ((temp.at(0)=='U') || (temp.at(0)=='D')){
        createMessage(temp);
    }

}

void MainWindow::createMessage(QString temp)
{
    socket->write("MSG\n");
    socket->flush();
    for(int i=0;i<1000000;i++); //wait for data to be read on server.
    //socket->waitForBytesWritten(3000);
    //socket->waitForReadyRead();
    //socket->flush();
    //stuff=socket->readAll();


    //table->playedCard.setNumber(tempString.at(0));
//    qDebug() << "temp" << temp;
//    qDebug() << "onpush.stuff" << stuff;


    //ready to send
    socket->write(temp.toUtf8());
    socket->flush();
    ui->lineEdit->clear();
    // socket->waitForReadyRead();
    // stuff=socket->readAll();
    // if(stuff!="ACK")
    //  {
    //    ui->textBrowser->clear();
    //   ui->textBrowser->setText("Send failed. Please close client to reconnect");
    // }
}


