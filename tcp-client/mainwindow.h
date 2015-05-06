#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTcpSocket>
#include <QMainWindow>
#include <qtimer.h>
#include <table.h>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool Connect();

public slots:
    void readyRead();
    void clientConnected();

private slots:
    void on_pushButton_clicked();
    void createMessage(QString temp);

private:
    Ui::MainWindow *ui;
    QString *serverAddr;
    int *serverPort;
    QString *userName;
    QTcpSocket *socket;
    bool m_bUserNameSend;
    Table *table;
    std::vector<int> handSize;
    int player_id;


};

#endif // MAINWINDOW_H
