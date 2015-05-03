#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "QChar"
#include <QtDebug>

class Card
{
private:
    QChar number;    //0-9, S=ugorj(skip), D=húzz kettőt (draw two), R=fordulj (reverse),
    QChar color;     //R=piros, B=kék, G=zöld Y=sárga, W=joker
    QChar color2;    //R=piros, B=kék, G=zöld Y=sárga A rátehető lap színe
public:
    Card();
    ~Card();
    QChar getNumber();
    QChar getColor();
    QChar getColor2();
    void setNumber(QChar n);
    void setColor(QChar c);
    void setColor2(QChar c2);
    void Print();
};

#endif // CARD_H
