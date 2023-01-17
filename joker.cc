#include "joker.h"
using namespace std;

Joker::Joker(string value = "2")
    : Card{value, "J"} {}

string Joker::getName()
{
    return "Joker";
}
