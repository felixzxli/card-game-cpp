#include <algorithm>
#include <random>
#include <chrono>
#include "tableModel.h"
#include <iostream>
using namespace std;

const int NUM_CARDS = 54;

TableModel::TableModel()
    : Subject{}, turn{1}, cur{nullptr} {}

void TableModel::setNextPlayer()
{
    int size = players.size();
    if ((cur == nullptr) || (cur == players[size - 1].get()))
    {
        cur = players[0].get();
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            if (cur == players[i].get())
            {
                cur = players[i + 1].get();
                return;
            }
        }

        std::cout << "next player not found!!" << std::endl; // error testing
    }
}

void TableModel::notifyView(bool won)
{
    view->update(won);
}

// performs the first move and starts the game
void TableModel::play()
{
    //perform first move
    setNextPlayer();
    hydras.emplace_back(make_unique<Hydra>(1));
    if (debug)
    {
        cout << "Card value?" << endl;
        string v, s;
        cin >> v;
        if (cur->drawPile.getTopSuit() != "J")
        {
            cout << "Suit?" << endl;
            cin >> s;
        }
        cur->drawPile.getTopCard().setValue(v);
        cur->drawPile.getTopCard().setSuit(s);
    }
    cur->drawPile.moveTopTo(*hydras[0]);

    while (!(hasWon()))
    {
        // does a "turn": the view is responsible for receiving input and modifying this object"s data to continue playing
        notifyView(false);
        turn += 1;
    }
    notifyView(true);
}

bool TableModel::hasWon()
{
    return (cur->drawPile.getSize() + cur->discardPile.getSize() + cur->reserve.getSize() == 0);
}

// requires: value is a valid card value (2-10, J, Q, K, A)
int TableModel::getIntVersion(string value)
{
    if (value == "2" || value == "3" || value == "4" || value == "5" || value == "6" || value == "7" ||
        value == "8" || value == "9" || value == "10")
    {
        return stoi(value);
    }
    else if (value == "J")
    {
        return 11;
    }
    else if (value == "Q")
    {
        return 12;
    }
    else if (value == "K")
    {
        return 13;
    }
    else if (value == "A")
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

bool TableModel::placeableOn(string value1, string value2)
{
    if (value1 == "A" || value2 == "A")
    {
        return true;
    }
    int i1 = getIntVersion(value1);
    int i2 = getIntVersion(value2);
    if (i1 == -1 || i2 == -1)
    {
        return false;
    }
    if (i1 <= i2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TableModel::canCutHead()
{
    if (cur->drawPile.getTopValue() == "A" || cur->drawPile.getTopSuit() == "J" || hydras[0]->getTopValue() == "A")
    {
        return false;
    }

    for (int i = 0; i < hydras.size(); ++i)
    {
        if (placeableOn(cur->drawPile.getTopValue(), hydras[i]->getTopValue()))
        {
            return false;
        }
    }

    return true;
}

void TableModel::cutHead()
{
    cur->drawPile.moveTopTo(cur->discardPile);
    if (cur->reserve.getSize() == 1)
    {
        cur->reserve.moveTopTo(cur->drawPile);
    }
    int numCards = hydras[0]->getSize();
    for (int i = 0; i < numCards; ++i)
    {
        hydras[0]->moveTopTo(cur->discardPile);
    }
    int prevNum = hydras[hydras.size() - 1]->getNum();

    hydras.erase(hydras.begin());
    hydras.emplace_back(make_unique<Hydra>(prevNum + 1));
    hydras.emplace_back(make_unique<Hydra>(prevNum + 2));

    cur->discardPile.shuffleDeck();
    while (cur->drawPile.getSize() < 2)
    {
        cur->discardPile.moveTopTo(cur->drawPile);
    }

    cur->drawPile.moveTopTo(*hydras[hydras.size() - 2]);
    cur->drawPile.moveTopTo(*hydras[hydras.size() - 1]);
}

void TableModel::distributeDecks(unsigned int numPlayers)
{
    Pile deck;
    for (int i = 0; i < numPlayers; ++i)
    {
        deck.addCard("A", "S");
        deck.addCard("2", "S");
        deck.addCard("3", "S");
        deck.addCard("4", "S");
        deck.addCard("5", "S");
        deck.addCard("6", "S");
        deck.addCard("7", "S");
        deck.addCard("8", "S");
        deck.addCard("9", "S");
        deck.addCard("10", "S");
        deck.addCard("J", "S");
        deck.addCard("Q", "S");
        deck.addCard("K", "S");
        deck.addCard("A", "H");
        deck.addCard("2", "H");
        deck.addCard("3", "H");
        deck.addCard("4", "H");
        deck.addCard("5", "H");
        deck.addCard("6", "H");
        deck.addCard("7", "H");
        deck.addCard("8", "H");
        deck.addCard("9", "H");
        deck.addCard("10", "H");
        deck.addCard("J", "H");
        deck.addCard("Q", "H");
        deck.addCard("K", "H");
        deck.addCard("A", "C");
        deck.addCard("2", "C");
        deck.addCard("3", "C");
        deck.addCard("4", "C");
        deck.addCard("5", "C");
        deck.addCard("6", "C");
        deck.addCard("7", "C");
        deck.addCard("8", "C");
        deck.addCard("9", "C");
        deck.addCard("10", "C");
        deck.addCard("J", "C");
        deck.addCard("Q", "C");
        deck.addCard("K", "C");
        deck.addCard("A", "D");
        deck.addCard("2", "D");
        deck.addCard("3", "D");
        deck.addCard("4", "D");
        deck.addCard("5", "D");
        deck.addCard("6", "D");
        deck.addCard("7", "D");
        deck.addCard("8", "D");
        deck.addCard("9", "D");
        deck.addCard("10", "D");
        deck.addCard("J", "D");
        deck.addCard("Q", "D");
        deck.addCard("K", "D");
        deck.addJoker();
        deck.addJoker();
    }
    deck.shuffleDeck();
    for (int i = 0; i < numPlayers; i++)
    {
        int num = i + 1;
        players.emplace_back(make_unique<Player>(num));
        for (int j = 0; j < NUM_CARDS; ++j)
        {
            deck.moveTopTo(players[i]->drawPile);
        }
    }
}
