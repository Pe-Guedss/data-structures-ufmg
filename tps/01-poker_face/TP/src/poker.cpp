#include "deck.hpp"

int main()
{
    Deck *cardDeck;
    cardDeck = new Deck();

    std::cout << cardDeck->getCard("13O") << std::endl;
    std::cout << "\n\n==============================================\n\n";
    cardDeck->showDeck();

    delete cardDeck;
    return 0;
}