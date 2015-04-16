#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card
{
private:
    char number;    //0-9, S=ugorj(skip), D=húzz kettőt (draw two), R=fordulj (reverse),
    char color; //R=piros, B=kék, G=zöld Y=sárga
public:
    Card();
    ~Card();
    char getNumber();
    char getColor();
    void setNumber(char n);
    void setColor(char c);
    void Print();
};

#endif // CARD_H

