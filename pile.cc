#include <algorithm>
#include <random>
#include <chrono>
#include "pile.h"
#include <iostream>

using namespace std;

int Pile::getSize() const
{
    return cards.size();
}

string Pile::getTopValue() const
{
    if (cards.size() == 0)
    {
        return "empty";
    }
    else
    {
        return cards.back()->getValue();
    }
}

string Pile::getTopSuit() const
{
    if (cards.size() == 0)
    {
        return "empty";
    }
    else
    {
        return cards.back()->getSuit();
    }
}

string Pile::getTopName() const
{
    if (cards.size() == 0)
    {
        return "empty";
    }
    else
    {
        return cards.back()->getName();
    }
}

void Pile::moveTopTo(Pile &pile)
{
    if (cards.size() > 0)
    {
        if (cards.back()->getSuit() == "J")
        {
            cards.back()->setValue("2");
        }
        pile.cards.push_back(move(cards.back()));
        cards.pop_back();
    }
}

void Pile::removeTop()
{
    if (cards.size() > 0)
    {
        cards.pop_back();
    }
}

void Pile::shuffleDeck()
{
    // obtain a time-based seed: (from cplusplus reference)
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

void Pile::addCard(string value, string suit)
{
    cards.emplace_back(make_unique<Card>(value, suit));
}

void Pile::addJoker(string value)
{
    cards.emplace_back(make_unique<Joker>(value));
}

void Pile::printPile()
{
    int size = cards.size();
    for (int i = size - 1; i >= 0; --i)
    {
        cout << "Name: " << cards[i]->getName() << ", Value: " << cards[i]->getValue() << ", Suit: " << cards[i]->getSuit() << endl;
    }
}

Card &Pile::getTopCard()
{
    return *(cards.back());
}
