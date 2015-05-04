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

using namespace std;

class Table
{
public:
    vector<Card> drawDeck;
    vector<Card> playDeck;
    typedef list<Card> Hand;
    map<int, Hand> Hands;
//    Hand Hands[cnt_players];
    Card playedCard;
    unsigned numberOfDrawCards;
    bool action;
    Table(int cnt_players);
    ~Table();
    void Load(int cnt_players);
    void PrintDrawDeck();
    void ShuffleDrawDeck();
    void Draw(player_id);
    void DrawEnough();
    void Play(QChar c, QChar n, QChar c2);
    void PlayClient();
    void Deal(int cnt_cards, int cnt_players);
    void SayUno();
    void PrintTable();
    QString Send();

};

#endif // TABLE_H

