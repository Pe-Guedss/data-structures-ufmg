#include "deck.hpp"

int main()
{
    Deck *cardDeck;
    cardDeck = new Deck();

    std::cout << cardDeck->getCard("13O") << std::endl;
    cardDeck->cleanDeck();
    std::cout << "\n\n==============================================\n\n";
    cardDeck->showDeck();
    std::cout << "\n\n++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
    cardDeck->initializeDeck();
    cardDeck->showDeck();

    delete cardDeck;
    return 0;
}