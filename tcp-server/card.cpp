#include "card.h"

Card::Card()
{

}

Card::~Card()
{

}

char Card::getNumber()
{
    return number;
}

char Card::getColor()
{
    return color;
}

char Card::getColor2()
{
    return color2;
}

void Card::setNumber(char n)
{
    number =n;
}

void Card::setColor(char c)
{
    color =c;
}

void Card::setColor2(char c2)
{
    color2 =c2;
}

void Card::Print()
{
    std::cout<<color<<number;
}

