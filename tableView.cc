#include "tableView.h"
#include <iostream>
using namespace std;

TableView::TableView()
    : table{} {}

void TableView::init(unsigned int numPlayers)
{
    table.distributeDecks(numPlayers);
}

//begins the game
void TableView::beginGame()
{
    cout << "How many players?" << endl;
    unsigned int numPlayers;
    cin >> numPlayers;
    if (numPlayers < 2)
    {
        cout << "Too few players" << endl;
    }
    else
    {
        init(numPlayers);
        if (debug)
        {
            table.debug = true;
        }
        table.attach(this);
        table.play();
    }
}

void TableView::receiveInput(bool swapped)
{
    if (debug)
    {
        cout << "Card value?" << endl;
        string v, s;
        cin >> v;
        if (table.cur->drawPile.getTopSuit() != "J")
        {
            cout << "Suit?" << endl;
            cin >> s;
        }
        table.cur->drawPile.getTopCard().setValue(v);
        table.cur->drawPile.getTopCard().setSuit(s);
    }

    cout << "Player " << to_string(table.cur->playerNum) << ", you are holding a "
         << table.cur->drawPile.getTopName() << ". Your move?" << endl;

    string input;
    cin >> input;
    int cmd = stoi(input);

    int firstNum = table.hydras.front()->getNum();
    int lastNum = table.hydras.back()->getNum();

    int hydraIndex = 0;
    for (int i = 0; i < table.hydras.size(); ++i)
    {
        if (table.hydras[i]->getNum() == cmd)
        {
            hydraIndex = i;
            break;
        }
    }

    if (cmd > 0)
    {
        if (cmd < firstNum || cmd > lastNum)
        {
            receiveInput();
        }
        else if (table.canCutHead())
        {
            if (cmd == firstNum)
            {
                table.cutHead();
                table.cur->turnsRemaining = 0;
            }
            else
            {
                receiveInput();
            }
        }
        else if (table.cur->drawPile.getTopSuit() == "J")
        {
            string val;
            cout << "Joker value?" << endl;
            cin >> val;
            if (table.placeableOn(val, table.hydras[hydraIndex]->getTopValue()))
            {
                table.cur->drawPile.getTopCard().setValue(val); // sets the joker to the value inputed
                bool endturn = (val == table.hydras[hydraIndex]->getTopValue());
                table.cur->drawPile.moveTopTo(*(table.hydras[hydraIndex]));
                if (endturn)
                {
                    table.cur->turnsRemaining = 0;
                }
                table.hydras[hydraIndex]->getTopCard().setValue(val);
            }
            else
            {
                receiveInput();
            }
        }
        else if (table.placeableOn(table.cur->drawPile.getTopValue(), table.hydras[hydraIndex]->getTopValue()))
        {
            bool endturn = (table.cur->drawPile.getTopValue() == table.hydras[hydraIndex]->getTopValue());
            table.cur->drawPile.moveTopTo(*(table.hydras[hydraIndex]));
            if (endturn)
            {
                table.cur->turnsRemaining = 0;
            }
        }
        else
        {
            receiveInput();
        }
    }
    else if (cmd == 0)
    {
        if (table.cur->reserve.getSize() == 1)
        {
            // cannot swap again
            if (swapped == false)
            {
                //swap
                Pile temp;
                table.cur->reserve.moveTopTo(temp);
                table.cur->drawPile.moveTopTo(table.cur->reserve);
                temp.moveTopTo(table.cur->drawPile);
                if (debug)
                {
                    cout << "Card value?" << endl;
                    string v, s;
                    cin >> v;
                    if (table.cur->drawPile.getTopSuit() != "J")
                    {
                        cout << "Suit?" << endl;
                        cin >> s;
                    }
                    table.cur->drawPile.getTopCard().setValue(v);
                    table.cur->drawPile.getTopCard().setValue(s);
                }
            }
            receiveInput(true);
        }
        else if (table.cur->reserve.getSize() == 0 && table.hydras.size() > 1)
        {
            table.cur->drawPile.moveTopTo(table.cur->reserve);
        }
        else
        {
            receiveInput();
        }
    }
    else
    {
        receiveInput();
    }
}

void TableView::update(bool won)
{
    if (won)
    {
        cout << "Player " << to_string(table.cur->playerNum) << " wins!" << endl;
        return;
    }

    // shuffles the deck as needed
    if (table.cur->drawPile.getSize() == 0)
    {
        if (table.cur->discardPile.getSize() == 0)
        {
            table.cur->reserve.moveTopTo(table.cur->drawPile);
            table.cur->turnsRemaining = 0; //ends the user's turns
        }
        else
        {
            for (int i = 0; i < table.cur->discardPile.getSize(); ++i)
            {
                table.cur->discardPile.moveTopTo(table.cur->drawPile);
            }
        }
        table.cur->drawPile.shuffleDeck();
    }

    cout << endl;
    cout << "Heads:" << endl;
    for (const auto &n : table.hydras)
    {
        cout << n->getNum() << ": " << n->getTopValue() << " "
             << "(" << to_string(n->getSize()) << ")" << endl;
    }
    cout << endl;
    cout << "Players:" << endl;
    for (const auto &n : table.players)
    {
        if ((table.cur == n.get()) && (table.cur->turnsRemaining > 0)) // (table.turn > 1)
        {
            cout << "Player " << n->playerNum << ": " << to_string(n->drawPile.getSize() + n->discardPile.getSize() - 1)
                 << " (" << to_string(n->drawPile.getSize() - 1) << " draw, " << to_string(n->discardPile.getSize()) << " discard)"
                 << " + 1 in hand, " << to_string(n->turnsRemaining - 1) << " remaining, " << to_string(n->reserve.getSize()) << " in reserve";
        }
        else
        {
            cout << "Player " << n->playerNum << ": " << to_string(n->drawPile.getSize() + n->discardPile.getSize())
                 << " (" << to_string(n->drawPile.getSize()) << " draw, " << to_string(n->discardPile.getSize()) << " discard)";
        }
        cout << endl;
    }
    cout << endl;

    if (table.cur->turnsRemaining > 0)
    {
        receiveInput(false);
        table.cur->turnsRemaining -= 1;
    }

    else // if the current played all the cards they need to in their turn
    {
        // return the reserve to the draw pile.
        table.cur->reserve.moveTopTo(table.cur->drawPile);

        table.setNextPlayer();
        table.cur->turnsRemaining = table.hydras.size();
        cout << "Player " << to_string(table.cur->playerNum) << ", it is your turn." << endl;
        cin.clear();
        cin.ignore();
        string temp;
        getline(cin, temp);
    }
}

void TableView::setDebug(bool debug)
{
    this->debug = debug;
}
