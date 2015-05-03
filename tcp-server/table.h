#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <card.h>
#include <vector>
#include <map>
#include <list>
#include "QString"
#include "QChar"

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
    void Load();
    void PrintDrawDeck();
    void ShuffleDrawDeck();
    void Draw();
    void DrawEnough();
    void Play(QChar c, QChar n, QChar c2);
    void PlayClient();
    void Deal(int c);
    void SayUno();
    void PrintTable();
    QString Send();

};

#endif // TABLE_H

