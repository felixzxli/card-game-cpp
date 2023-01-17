#ifndef _JOKER_H_
#define _JOKER_H_
#include <string>
#include "card.h"

class Joker : public Card
{

public:
    Joker(std::string value);
    virtual std::string getName() override;
};

#endif
