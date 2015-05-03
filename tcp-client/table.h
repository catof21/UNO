#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <list>
#include <card.h>






class Table
{

private:
    bool uno;

public:

    std::list<Card> Hand;
    Card playedCard;
    Table();
    ~Table();
    void Print();
    void Draw();
    int Play(QChar n, QChar c);
    void SayUno();
    bool getUno();
    void setUno(bool b);
    bool action;

};

#endif // TABLE_H

