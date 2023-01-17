#include "hydra.h"

Hydra::Hydra(unsigned int num)
    : Pile{}, hydraNum{num} {}

unsigned int Hydra::getNum() const
{
    return hydraNum;
}
