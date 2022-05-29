#include "hand.hpp"

int main()
{
    Deck *cardDeck;
    cardDeck = new Deck();

    Hand *firstHand;
    firstHand = new Hand();
    firstHand->addCard("2O", cardDeck);
    firstHand->addCard("3E", cardDeck);
    firstHand->addCard("4P", cardDeck);
    firstHand->addCard("5C", cardDeck);
    firstHand->addCard("6O", cardDeck);

    Hand *secondHand;
    secondHand = new Hand();
    secondHand->addCard("12C", cardDeck);
    secondHand->addCard("1C", cardDeck);
    secondHand->addCard("10C", cardDeck);
    secondHand->addCard("11C", cardDeck);
    secondHand->addCard("13O", cardDeck);

    std::cout << "The first hand best combination is: " << firstHand->getBestCombinationCode() << std::endl;
    std::cout << "The second hand best combination is: " << secondHand->getBestCombinationCode() << std::endl;

    bool a = *firstHand > *secondHand;
    bool b = *firstHand < *secondHand;
    bool c = *firstHand == *secondHand;

    std::cout << "Is the first Hand greater than the second one? " << a << std::endl;
    std::cout << "Is the first Hand lesser than the second one? " << b << std::endl;
    std::cout << "Is the first Hand equals the second one? " << c << std::endl;

    return 0;
}