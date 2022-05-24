#include "card.hpp"
#include <iostream>

int main()
{
    Card *card1 = new Card("2A");
    Card *card2 = new Card("3A");
    Card *card3 = new Card("13A");

    bool a = card2 < card1;

    std::cout << a << std::endl;

    std::cout << card1 << std::endl;
    std::cout << *card2 << std::endl;
    std::cout << card3 << std::endl;

    return 0;
}