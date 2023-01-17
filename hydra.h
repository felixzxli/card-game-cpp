#ifndef _HYRDA_H_
#define _HYRDA_H_
#include <string>
#include <vector>
#include <memory>
#include "pile.h"

class Hydra : public Pile
{
    unsigned int hydraNum;

public:
    Hydra(unsigned int num);
    virtual ~Hydra() = default;
    unsigned int getNum() const;
};

#endif
