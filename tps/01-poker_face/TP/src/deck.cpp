#include "deck.hpp"

Deck::Deck() {
    const int cardsPerNipe = 13;

    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                for (int j = 0; j < cardsPerNipe; j++) {
                    this->cardDeck[j + i * cardsPerNipe] = new Card(std::to_string(j) + "O");
                }
                break;
            case 1:
                for (int j = 0; j < cardsPerNipe; j++) {
                    this->cardDeck[j + i * cardsPerNipe] = new Card(std::to_string(j) + "E");
                }
                break;
            case 2:
                for (int j = 0; j < cardsPerNipe; j++) {
                    this->cardDeck[j + i * cardsPerNipe] = new Card(std::to_string(j) + "C");
                }
                break;
            case 3:
                for (int j = 0; j < cardsPerNipe; j++) {
                    this->cardDeck[j + i * cardsPerNipe] = new Card(std::to_string(j) + "P");
                }
                break;
            
            default:
                break;
        }
    }
    
}