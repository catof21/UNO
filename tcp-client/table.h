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
    void Play();
    void SayUno();
};

#endif // TABLE_H

