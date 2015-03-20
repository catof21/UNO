#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = 0);

signals:

public slots:

};

#endif // GAMESERVER_H
