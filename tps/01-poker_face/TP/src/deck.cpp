#include "deck.hpp"

Deck::Deck() {
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j) + "O");
                }
                break;
            case 1:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j) + "E");
                }
                break;
            case 2:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j) + "C");
                }
                break;
            case 3:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j) + "P");
                }
                break;
            
            default:
                break;
        }
    }
}

Deck::~Deck() {
    for (int i = 0; i < this->totalCards; i++)
    {
        delete this->cardDeck[i];
        this->cardDeck[i] = nullptr;
    }
}

Card* Deck::locateCard(int cardNum, std::string cardNipe) {
    enum {
        ouro,
        espada,
        copas,
        paus
    };

    if (cardNipe == "O")
    {
        Card *aux;
        aux = this->cardDeck[ cardNum + ouro * this->cardsPerNipe ];
        this->cardDeck[ cardNum + ouro * this->cardsPerNipe ] = nullptr;
        return aux;
    }
    else if (cardNipe == "E")
    {
        Card *aux;
        aux = this->cardDeck[ cardNum + espada * this->cardsPerNipe ];
        this->cardDeck[ cardNum + espada * this->cardsPerNipe ] = nullptr;
        return aux;
    }
    else if (cardNipe == "C")
    {
        Card *aux;
        aux = this->cardDeck[ cardNum + copas * this->cardsPerNipe ];
        this->cardDeck[ cardNum + copas * this->cardsPerNipe ] = nullptr;
        return aux;
    }
    else if (cardNipe == "P")
    {
        Card *aux;
        aux = this->cardDeck[ cardNum + paus * this->cardsPerNipe ];
        this->cardDeck[ cardNum + paus * this->cardsPerNipe ] = nullptr;
        return aux;
    }
    else {
        return nullptr;
    }
}

Card* Deck::getCard(std::string cardCode) {
    int it = 0;
    for (auto &&i : cardCode)
    {
        if (isalpha(i))
            break;
        it++;
    }

    std::string num = cardCode.substr(0, it);
    std::string cardNipe = cardCode.substr(it, cardCode.length() - 1);

    return this->locateCard(atoi(num.c_str()), cardNipe);
}