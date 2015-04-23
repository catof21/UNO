#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <card.h>
#include <vector>
#include <map>
#include <list>
#include "QString"

#include <ctime>
#include <cstdlib>

//proba


class Table
{
public:
    std::vector<Card> drawDeck;
    std::vector<Card> playDeck;
    std::list<Card> Hand;
    Card playedCard;
    unsigned numberOfDrawCards;
    bool action;
    Table();
    ~Table();
    void PrintDrawDeck();
    void ShuffleDrawDeck();
    void Draw();
    void Play(char c, char n, char c2);
    void PlayClient();
    void Deal();
    void SayUno();
    void PrintTable();
    QString Send();

};

#endif // TABLE_H

