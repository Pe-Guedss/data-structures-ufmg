#include "hand.hpp"
#include "msgassert.hpp"

Hand::Hand() {
    this->cleanHand();
    this->bestCombination = -1;
    this->highestCard = nullptr;
}

Hand::~Hand() {
    this->cleanHand();
}

void Hand::sortHand() {
    for (int i = 0; i < this->maxCards; i++) {
        Card *minCard = this->cards[i];
        for (int j = i; j < this->maxCards; j++)
        {
            if (this->cards[j] < minCard)
            {
                minCard = this->cards[j];
            }
        }
        swapCards(this->cards[i], minCard);
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
    for (auto &&card : this->cards) {
        if (card->number != royalCardsNumber) {
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

void Hand::findHighestCard() {
    if (this->cards[0]->number == 1) {
        this->highestCard = this->cards[0];
    } else {
        this->highestCard = this->cards[this->maxCards - 1];
    }
}

void Hand::addCard(std::string cardCode) {
    for (auto &&card : this->cards) {
        if (!card) {
            card = new Card(cardCode);
            break;
        }
    }
}

std::string Hand::getBestCombinationCode() {
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
    this->sortHand();
    this->findHighestCard();

    bool isFlush, isStraight, isRoyalStraight;

    isStraight = this->checkStraight();
    isFlush = this->checkFlush();
    if (isFlush) {
        isRoyalStraight = this->checkRoyalStraight();
        if (isRoyalStraight) {
            this->bestCombination = this->RSF;
            return;
        }
        
        if (isStraight) {
            this->bestCombination = this->SF;
            return;
        }
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