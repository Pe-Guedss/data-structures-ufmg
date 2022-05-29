#include "hand.hpp"
#include "msgassert.hpp"

#define swapCards(A, B) \
    {                      \
        Card *aux = A;       \
        A = B;             \
        B = aux;           \
    }

Hand::Hand() {
    this->cleanHand();
    this->bestCombination = -1;
    this->highestCard = nullptr;
}

Hand::~Hand() {
    this->cleanHand();
}

void Hand::sortHand() {
    std::cout << this << std::endl;

    for (int i = 0; i < this->maxCards; i++) {
        Card *minCard = this->cards[i];
        for (int j = i; j < this->maxCards; j++) {
            if (*this->cards[j] < *minCard) {
                minCard = this->cards[j];
            }
        }
        swapCards(this->cards[i], minCard);
        std::cout << this << std::endl;
    }
}

bool Hand::checkStraight() {
    int previousNumber = this->cards[0]->number;
    for (int i = 1; i < this->maxCards; i++) {
        if (this->cards[i]->number != previousNumber + 1) {
            return false;
        }
        previousNumber = this->cards[i]->number;
    }
    return true;
}

bool Hand::checkFlush() {
    std::string previousNipe = this->cards[0]->nipe;
    for (auto &&card : this->cards) {
        if (card->nipe != previousNipe) {
            return false;
        }
        previousNipe = card->nipe;
    }
    return true;
}

bool Hand::checkRoyalStraight() {
    if (this->cards[0]->number != 1) {
        return false;
    }
    int royalCardsNumber = 10;
    for (int i = 1; i < this->maxCards; i++) {
        if (this->cards[i]->number != royalCardsNumber) {
            return false;
        }
        royalCardsNumber++;
    }
    
    return true;
}

bool Hand::checkFourOfAKind() {
    bool isFirstFour, isLastFour;

    isFirstFour = *this->cards[0] == *this->cards[3];
    isLastFour = *this->cards[1] == *this->cards[4];
    
    return isFirstFour || isLastFour;
}

bool Hand::checkOnePair() {
    int previousNumber = this->cards[0]->number;

    for (int i = 1; i < this->maxCards; i++) {
        if (this->cards[i]->number == previousNumber) {
            return true;
        }
        previousNumber = this->cards[i]->number;
    }

    return false;
}

bool Hand::checkTwoPairs() {
    bool firstPairFound = false, secondPairFound = false;

    int previousNumber = this->cards[0]->number;

    for (int i = 1; i < this->maxCards; i++) {
        if (this->cards[i]->number == previousNumber) {
            firstPairFound == false ? (firstPairFound = true) : (secondPairFound = true);
            if (secondPairFound)
            {
                return true;
            }
            i++;
        }
        previousNumber = this->cards[i]->number;
    }

    return false;
}

bool Hand::checkThreeOfAKind() {
    bool isFirstThree = false, isMiddleThree = false, isLastThree = false;

    isFirstThree = *this->cards[0] == *this->cards[2];
    isMiddleThree = *this->cards[1] == *this->cards[3];
    isLastThree = *this->cards[2] == *this->cards[4];

    return isFirstThree || isMiddleThree || isLastThree;
}

bool Hand::checkFullHouse() {
    bool isPairFirst = false, isPairLast = false;

    isPairFirst = (*this->cards[0] == *this->cards[1]) && (this->cards[2] == this->cards[4]);
    isPairFirst = (*this->cards[3] == *this->cards[4]) && (this->cards[0] == this->cards[2]);

    return isPairFirst || isPairLast;
}

bool Hand::checkValidHand() {
    for (auto &&card : this->cards) {
        if (!card) {
            std::cout << "Esta mão não é válida. Há cartas faltantes." << std::endl;
            return false;
        }
    }
    
    return true;
}

void Hand::findHighestCard() {
    bool isHandValid = this->checkValidHand();
    if (!isHandValid) {
        return;
    }

    if (this->cards[0]->number == 1) {
        this->highestCard = this->cards[0];
    } else {
        this->highestCard = this->cards[this->maxCards - 1];
    }
}

void Hand::addCard(std::string cardCode, Deck *cardDeck) {
    for (auto &&card : this->cards) {
        if (!card) {
            card = cardDeck->getCard(cardCode);
            break;
        }
    }
}

std::string Hand::getBestCombinationCode() {
    bool isHandValid = this->checkValidHand();
    if (!isHandValid) {
        return "";
    }

    if (this->bestCombination == -1) {
        this->findBestCombination();
    }

    std::cout << "Melhor combinação: " << this->bestCombination << std::endl;

    switch (this->bestCombination) {
        case this->HC:
            return "HC";
            break;
        
        case this->OP:
            return "OC";
            break;

        case this->TP:
            return "TP";
            break;

        case this->TK:
            return "TK";
            break;

        case this->S:
            return "S";
            break;

        case this->F:
            return "F";
            break;

        case this->FH:
            return "FH";
            break;

        case this->FK:
            return "FK";
            break;

        case this->SF:
            return "SF";
            break;

        case this->RSF:
            return "RSF";
            break;
        
        default:
            return "";
            break;
    }
}

void Hand::findBestCombination() {
    bool isHandValid = this->checkValidHand();
    if (!isHandValid) {
        return;
    }

    this->sortHand();
    this->findHighestCard();

    bool isRoyalStraight = this->checkRoyalStraight();
    std::cout << "Is Royal Straight: " << isRoyalStraight << std::endl;
    bool isFourOfAKind = this->checkFourOfAKind();
    bool isFullHouse = this->checkFullHouse();
    bool isFlush = this->checkFlush();
    bool isStraight = this->checkStraight();
    bool isThreeOfAKind = this->checkThreeOfAKind();
    bool isTwoPairs = this->checkTwoPairs();
    bool isOnePair = this->checkOnePair();

    if (isFlush) {
        if (isRoyalStraight) {
            this->bestCombination = this->RSF;
            return;
        }
        else if (isStraight) {
            this->bestCombination = this->SF;
            return;
        }
    }
    else if (isFourOfAKind) {
        this->bestCombination = this->FK;
        return;
    }
    else if (isFullHouse) {
        this->bestCombination = this->FH;
        return;
    }
    else if (isFlush) {
        this->bestCombination = this->F;
        return;
    }
    else if (isStraight) {
        this->bestCombination = this->S;
        return;
    }
    else if (isThreeOfAKind) {
        this->bestCombination = this->TK;
        return;
    }
    else if (isTwoPairs) {
        this->bestCombination = this->TP;
        return;
    }
    else if (isOnePair)
    {
        this->bestCombination = this->OP;
        return;
    }
    else {
        this->bestCombination = this->HC;
        return;
    }
}

void Hand::cleanHand() {
    for (int i = 0; i < this->maxCards; i++)
    {
        delete this->cards[i];
        this->cards[i] = nullptr;
    }

    delete this->highestCard;
    this->highestCard = nullptr;

    this->bestCombination = -1;
}

std::ostream &operator<<(std::ostream &out, const Hand *hand)
{
    out << "===== Current hand state =====" << std::endl;
    for (auto &&card : hand->cards) {
        out << card->getCardNumber() << card->getCardNipe() << " ";
    }
    std::cout << std::endl;
    
    return out;
}

std::ostream &operator<<(std::ostream &out, const Hand hand)
{
    out << "===== Current hand state =====" << std::endl;
    for (auto &&card : hand.cards) {
        out << card->getCardNumber() << card->getCardNipe() << " ";
    }
    std::cout << std::endl;
    
    return out;
}