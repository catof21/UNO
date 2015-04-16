#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <card.h>
#include <vector>
#include <map>
#include <list>

#include <ctime>
#include <cstdlib>



class Table
{
public:
    std::vector<Card> drawDeck;
    std::vector<Card> playDeck;
    std::list<Card> Hand;
    Card playedCard;
    Table();
    ~Table();
    void PrintDrawDeck();
    void ShuffleDrawDeck();
    void Draw();
    void Play(char c, char n);
    void Deal();
};

#endif // TABLE_H

