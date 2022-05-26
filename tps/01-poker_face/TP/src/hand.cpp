#include "hand.hpp"
#include "msgassert.hpp"

Hand::Hand() {
    this->cleanHand();
    this->bestCombination = -1;
}

void Hand::cleanHand() {
    for (int i = 0; i < this->maxCards; i++)
    {
        delete this->cards[i];
        this->cards[i] = nullptr;
    }
}