#include "card.h"
using namespace std;

Card::Card(string value, string suit)
    : value{value}, suit{suit} {}

string Card::getSuit() noexcept
{
    return suit;
}

string Card::getValue() noexcept
{
    return value;
}

void Card::setSuit(string suit)
{
    this->suit = suit;
}

void Card::setValue(string value)
{
    this->value = value;
}

string Card::getName()
{
    return value + suit;
}
