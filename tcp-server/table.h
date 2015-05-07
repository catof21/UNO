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
    vector<Hand> Hands;
    //Hand Hands[1];
    Card playedCard;
    unsigned numberOfDrawCards;
    bool action;
    int currentPlayer;
    int course;
    int maxPlayer;
    Table(int cnt_players);
    ~Table();
    void Load(int cnt_players);
    void PrintDrawDeck();
    void ShuffleDrawDeck();
    void Draw(int player_id);
    void DrawEnough(int player_id);
    void Play(int player_id, QChar c, QChar n, QChar c2);
//    void PlayClient();
    void Deal(int cnt_cards, int cnt_players);
    void SayUno(int player_id);
    void PrintTable();
    QString Send(int player_id);
    void SetNextPlayer();

};

#endif // TABLE_H

