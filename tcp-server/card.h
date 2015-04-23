#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card
{
private:
    char number;    //0-9, S=ugorj(skip), D=húzz kettőt (draw two), R=fordulj (reverse),
    char color;     //R=piros, B=kék, G=zöld Y=sárga, W=joker
    char color2;    //R=piros, B=kék, G=zöld Y=sárga A rátehető lap színe
public:
    Card();
    ~Card();
    char getNumber();
    char getColor();
    char getColor2();
    void setNumber(char n);
    void setColor(char c);
    void setColor2(char c2);
    void Print();
};

#endif // CARD_H
