#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <list>
#include <card.h>






class Table
{

private:

public:
    std::list<Card> Hand;
    Card playedCard;
    Table();
    ~Table();
    void Print();
    void Draw();
    int Play(QChar n, QChar c);
    int SayUno();
    bool getUno();
    void setUno(bool b);
    bool action;
    bool uno;
    int nxtP=-1;
};

#endif // TABLE_H

