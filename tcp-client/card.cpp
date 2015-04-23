#include "card.h"
#include <QtDebug>
using namespace::std;

Card::Card()
{

}

Card::~Card()
{

}

QChar Card::getNumber()
{
    return number;
}

QChar Card::getColor()
{
    return color;
}

QChar Card::getColor2()
{
    return color2;
}

void Card::setNumber(QChar n)
{
    number =n;
}

void Card::setColor(QChar c)
{
    color =c;
}

void Card::setColor2(QChar c2)
{
    color2 =c2;
}

void Card::Print()
{
    qDebug() << color << number;
//    std::cout<<color<<number;
}

QString Card::Send()
{
    QString str;
    str.append(color);
    str.append(number);
    return str;
}

