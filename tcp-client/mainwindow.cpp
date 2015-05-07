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
    player_id = -1;
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
//    for(int i=0;i<10000000;i++); //waste time for thread on server to setup
   QThread::sleep(1) ;
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
//   ui->textBrowser->setText("U(pdate) | P(lay) | D(raw) | X(UNO)");
//   ui->textBrowser->append(userName->toUtf8());
}






void MainWindow::readyRead()
{
// handle the readyRead signal
   QString tempString = socket->readAll();
   if (tempString == "ACK") {
        qDebug() << "ACK kapott";
        QString menu;
        menu.append("Hello ");
        menu.append(userName->toUtf8());
        menu.append("!");
        ui->textBrowser->setText(menu);
        ui->textBrowser->append("Nemsokara jatszhatsz...");


   } else if (tempString.startsWith(QChar('L'))){
       qDebug() << "Logint kapok";
//       qDebug() << tempString.at(1) << "player_id";
       if (player_id == -1) {
           player_id = tempString.at(1).digitValue();
           for (int i=0; i<tempString.at(2).digitValue()+1;i++) {
               handSize.push_back(9);

           }
       }
       if (tempString.at(1).digitValue() == tempString.at(2).digitValue()) {
           QString tmp;
           tmp.append("UU");
           createMessage(tmp);
       }
       qDebug() << "valid player_id"<< player_id;

   } else if (tempString == "EXIT") {
       ui->textBrowser->setText("Maximális játékosszám elérve");
       //sleep valamennyit
       QCoreApplication::quit();

   } else {
       ui->textBrowser->clear();
         QString hexa;
         hexa.append(tempString.at(5));
         hexa.append(tempString.at(6));
         int nhex = hexa.toInt(0,16);
         if(nhex==0){
             table->nxtP=100;
             if(player_id==tempString.at(4).digitValue()){
                 ui->textBrowser->setText("GRATULÁLUNK!");
                 ui->textBrowser->append("");
                 ui->textBrowser->append("NYERTÉL!");
             }else{
                 QString menu;
                 ui->textBrowser->setText("A JATEKNAK VEGE");
                 ui->textBrowser->append("");
                 menu.append("A jatekot a(z) ");
                 menu.append(QString::number(tempString.at(4).digitValue()+1));
                 menu.append(". jatekos nyerte ");
                 ui->textBrowser->append(menu);
             }
         }else{
              ui->textBrowser->clear();
              QString menu;
              menu.append("Hello ");
              menu.append(userName->toUtf8());
              menu.append(", Te vagy a ");
              menu.append(QString::number(player_id+1));
              menu.append(". jatekos");
              ui->textBrowser->setText(menu);
              ui->textBrowser->append("P(lay) | D(raw) | U(no)");
              table->playedCard.setNumber(tempString.at(0));                    //asztalon levo szama
              table->playedCard.setColor(tempString.at(1));                     //asztalon levo szine
              table->playedCard.setColor2(tempString.at(2));                    //asztalon levo szin keres
              QChar a = tempString.at(3);                                       //action ?
              if ( a == '0') {
                  table->action=false;
              } else {
                  table->action=true;
              }
              QString hexa;
              hexa.append(tempString.at(5));
              hexa.append(tempString.at(6));
              int nhex = hexa.toInt(0,16);
              handSize[tempString.at(4).digitValue()]=nhex;
              table->nxtP=tempString.at(7).digitValue();
              if (tempString.at(4).digitValue() == player_id) {                              //PID

    /*                  qDebug() << tempString.at(0);
                      qDebug() << tempString.at(1);
                      qDebug() << tempString.at(2);
                      qDebug() << tempString.at(3);
                      qDebug() << tempString.at(4)<< "PID";
                      qDebug() << tempString.at(5);
                      qDebug() << tempString.at(6)<< "LAPSZ";
                      qDebug() << tempString.at(7)<< "kijon"; */
                      table->Hand.erase(table->Hand.begin(), table->Hand.end());

                      Card c;
                       for(int i=8;i<tempString.length();i=i+3) {
                           c.setNumber(tempString.at(i));
                           c.setColor(tempString.at(i+1));
                           c.setColor2(tempString.at(i+2));
                           table->Hand.push_back(c);
                       }
                       int i =table->Hand.size();
                       qDebug() << i;
                       if(table->Hand.size()==1){
                           table->setUno(true);
                       }
              }
               for (uint i=0; i<handSize.size();i++) {
                   if (i!=player_id){
                        QString ext;
                        ext.append(QString::number(i+1));
                        ext.append(". jatekos lapjainak szama: ");
                        ext.append(QString::number(handSize[i]));
                        ui->textBrowser->append(ext);
                    }
               }

               ui->textBrowser->append("Hívó lap:");
               ui->textBrowser->append(table->playedCard.Send().toUtf8());
               if(table->playedCard.getColor()=='W'){
                   ui->textBrowser->append("A hivott szin: ");
                   ui->textBrowser->append(table->playedCard.getColor2());
               }
               QString kijon;
               kijon.append(QString::number(tempString.at(7).digitValue()+1));
               kijon.append(". jatekos kovetkezik");
               ui->textBrowser->append(kijon);
               ui->textBrowser->append("\nKézben lévő lapok:");
               for(std::list<Card>::iterator i = table->Hand.begin(); i != table->Hand.end(); i++){
                    ui->textBrowser->append(i->Send().toUtf8());
               }
            }
   }
   qDebug() << "readyread legvége" << tempString;
   tempString.clear();


   ui->textBrowser->repaint();
}
void MainWindow::on_pushButton_clicked()
{
    //user clicked the send button and would like their message to be sent. woooo.
    QString temp, stuff;
    if(table->getUno()==true){
        temp='1';
    }else{
        temp='0';
    }
    temp.append(ui->lineEdit->text());
    if (temp.at(1)=='P') {
        if (table->nxtP!=player_id) {
            ui->textBrowser->append("Nem te jössz!");
             ui->lineEdit->clear();
        }else {
        QChar c=temp.at(2);
        QChar n=temp.at(3);
        if(table->Play(n, c)==0){                           //ha játszható
           if (c=='W')   {              
              createMessage(temp);
           } else {
              createMessage(temp.append(temp.at(2)));       //ha nincs megadva második szín, akkor a lap színét teszi be másodiknak
           }
           table->setUno(false);
        }else{
            switch (table->Play(n, c)) {
            case 1:
                ui->textBrowser->append("Nincs ilyen lap a kezedben. Kerlek adj meg masikat!");
                ui->lineEdit->clear();
                break;
            case 2:
                ui->textBrowser->append("Nem hivhatod ki ezt a lapot, mert van hivo szinu lapod!");
                ui->lineEdit->clear();
                break;
            case 3:
                ui->textBrowser->append("A hivott akciolapra csak ugyan olyan akciolapot tehetsz. Ha nincs nalad ilyen lap, valaszd a D(raw) menut!");
                ui->lineEdit->clear();
                break;
            case 4:
                ui->textBrowser->append("Nem hivhatod ki ezt a lapot, mert sem a szine sem a szama nem egyezik meg a hívo lapeval!");
                ui->lineEdit->clear();
                break;
            }
            ui->lineEdit->clear();
            }
        }
    }
    else if (temp.at(1)=='D'){
        if (table->nxtP!=player_id) {
            ui->textBrowser->append("Nem te jössz!");
             ui->lineEdit->clear();
        }else {
        createMessage(temp);
        table->setUno(false);
        }
    }
    else if (temp.at(1)=='U'){
        int i;
        i=table->SayUno();
        if(i==0){
            ui->textBrowser->append("Bemondtad, hogy UNO!");
        }else{
            ui->textBrowser->append("Nem mondhatod be, hogy UNO!");
        }
        ui->lineEdit->clear();
    }else{
        if (table->nxtP<0){
            ui->textBrowser->append("Nincs meg itt mindenki!");
            ui->lineEdit->clear();
        } else {
            createMessage(temp);
        }
    }
    if(table->getUno()==true){
        qDebug()<<"true";
    }else{
        qDebug()<<"false";
    }


}

void MainWindow::createMessage(QString temp)
{

    socket->write("MSG\n");
    socket->flush();
    for(int i=0;i<1000000;i++); //wait for data to be read on server.


    socket->write(temp.toUtf8());
    socket->flush();
    ui->lineEdit->clear();


}


