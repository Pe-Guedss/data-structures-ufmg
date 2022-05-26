#include "deck.hpp"
#include "msgassert.hpp"

Deck::Deck() {
    this->initializeDeck();
}

Deck::~Deck() {
    this->cleanDeck();
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
        aux = this->cardDeck[ (cardNum + ouro * this->cardsPerNipe) - 1 ];
        erroAssert(aux != nullptr, "Essa carta já foi utilizada por outro jogador!");
        this->cardDeck[ (cardNum + ouro * this->cardsPerNipe) - 1 ] = nullptr;
        return aux;
    }
    else if (cardNipe == "E")
    {
        Card *aux;
        aux = this->cardDeck[ (cardNum + espada * this->cardsPerNipe) - 1 ];
        erroAssert(aux != nullptr, "Essa carta já foi utilizada por outro jogador!");
        this->cardDeck[ (cardNum + espada * this->cardsPerNipe) - 1 ] = nullptr;
        return aux;
    }
    else if (cardNipe == "C")
    {
        Card *aux;
        aux = this->cardDeck[ (cardNum + copas * this->cardsPerNipe) - 1 ];
        erroAssert(aux != nullptr, "Essa carta já foi utilizada por outro jogador!");
        this->cardDeck[ (cardNum + copas * this->cardsPerNipe) - 1 ] = nullptr;
        return aux;
    }
    else if (cardNipe == "P")
    {
        Card *aux;
        aux = this->cardDeck[ (cardNum + paus * this->cardsPerNipe) - 1 ];
        erroAssert(aux != nullptr, "Essa carta já foi utilizada por outro jogador!");
        this->cardDeck[ (cardNum + paus * this->cardsPerNipe) - 1 ] = nullptr;
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

void Deck::showDeck() {
    for (int i = 0; i < this->totalCards; i++)
    {
        if (this->cardDeck[i]) {
            std::cout << this->cardDeck[i] << std::endl;
        } else {
            std::cout << "===== Card Info =====" << std::endl;
            std::cout << "This card is in someone's hand!\n" << std::endl;
        }
    }
}

void Deck::cleanDeck() {
    for (int i = 0; i < this->totalCards; i++)
    {
        delete this->cardDeck[i];
        this->cardDeck[i] = nullptr;
    }
}

void Deck::initializeDeck() {
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j + 1) + "O");
                }
                break;
            case 1:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j + 1) + "E");
                }
                break;
            case 2:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j + 1) + "C");
                }
                break;
            case 3:
                for (int j = 0; j < this->cardsPerNipe; j++) {
                    this->cardDeck[j + i * this->cardsPerNipe] = new Card(std::to_string(j + 1) + "P");
                }
                break;
            
            default:
                break;
        }
    }
}