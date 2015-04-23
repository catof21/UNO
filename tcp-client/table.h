#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <card.h>

#include <list>





class Table
{
public:

    std::list<Card> Hand;
    Card playedCard;
    Table();
    ~Table();
    void Print();
    void Draw();
    int Play(QChar n, QChar c);
    void SayUno();
    bool action;
};

#endif // TABLE_H

