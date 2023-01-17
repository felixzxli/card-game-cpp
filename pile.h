#ifndef _PILE_H_
#define _PILE_H_
#include <string>
#include <vector>
#include <memory>
#include "joker.h"
#include "card.h"

class Pile
{
    std::vector<std::unique_ptr<Card>> cards;

public:
    Pile() = default;
    virtual ~Pile() = default;

    int getSize() const;

    // the following methods return "empty" if the pile has no cards;
    std::string getTopValue() const;
    std::string getTopSuit() const;
    std::string getTopName() const;

    //removes the top card of the deck
    void removeTop();

    //shuffles the deck
    void shuffleDeck();

    //moves the top of the deck to pile if the deck is not empty
    void moveTopTo(Pile &pile);

    //adds a normal card or a joker to the top of the deck
    void addCard(std::string value, std::string suit);
    void addJoker(std::string value = "2");

    Card &getTopCard();
    void printPile();
};

class noCard_emptyDeck
{
};

#endif
