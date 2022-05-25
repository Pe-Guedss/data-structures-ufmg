#include "card.hpp"

int main()
{
    Card *card1 = new Card("2A");
    Card *card2 = new Card("3A");
    Card *card3 = new Card("13A");
    Card *card4 = new Card("13A");

    bool a = card2 < card1;
    bool b = card2 > card1;
    bool c = *card2 == *card3;
    bool d = *card3 == *card4;

    std::cout << "card2 < card1 -> " << a << std::endl;
    std::cout << "card2 > card1 -> " << b << std::endl;
    std::cout << "card2 == card3 -> " << c << std::endl;
    std::cout << "card3 == card4 -> " << d << std::endl;

    std::cout << card1 << std::endl;
    std::cout << *card2 << std::endl;
    std::cout << card3 << std::endl;

    return 0;
}