#include <QCoreApplication>
#include "myserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    myserver Server;
    Server.StartServer();
    return a.exec();

}
/*#include <table.h>
#include <menu.h>
int main()
{
    Table T;
    T.Deal();
    Menu M;
    M.start(T);
}
*/
