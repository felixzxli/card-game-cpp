#ifndef _TABLEMODEL_H_
#define _TABLEMODEL_H_
#include <vector>
#include <string>
#include "subject.h"
#include "pile.h"
#include "hydra.h"
#include "player.h"

class TableModel : public Subject
{
public:
    int turn;
    std::vector<std::unique_ptr<Player>> players;
    Player *cur;
    std::vector<std::unique_ptr<Hydra>> hydras;
    bool debug = false;

    TableModel();
    ~TableModel() = default;
    void setNextPlayer();
    virtual void notifyView(bool won) override;
    // void playTurn();

    // performs the first move and starts the game
    void play();

    // determines if the current card on top of the player's draw pile has no valid moves to make except cutting off a head
    bool canCutHead();
    void cutHead(); // cuts the head off the oldest hydra and makes 2 more

    bool hasWon();

    int getIntVersion(std::string value);
    // determines if a card with value1 can be placed on a card with value2
    bool placeableOn(std::string value1, std::string value2);

    // initializes players and distributes each player 54 cards
    // requires: numPlayers >= 2 (user's responsibility)
    void distributeDecks(unsigned int numPlayers);
};

#endif
