#ifndef _CARD_H_
#define _CARD_H_
#include <string>

class Card
{
    std::string value; // must be one of A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
    std::string suit;  // must be one of S, H, C, D, or J if it is a Joker

public:
    Card(std::string value, std::string suit);
    std::string getSuit() noexcept;
    std::string getValue() noexcept;
    void setSuit(std::string suite);
    void setValue(std::string value);
    virtual std::string getName();
};

#endif
