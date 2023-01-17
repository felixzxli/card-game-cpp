#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <string>
#include "pile.h"

class Player
{
public:
    int playerNum;
    int turnsRemaining = 0;

    Pile drawPile;
    Pile discardPile;
    Pile reserve; // pile with size 0 or 1

    Player() = default;
    Player(int num);
    ~Player() = default;
};

#endif
