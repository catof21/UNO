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

void Card::setNumber(char n)
{
    number =n;
}

void Card::setColor(char c)
{
    color =c;
}

void Card::Print()
{
    std::cout<<color<<number;
}


