#include "round.hpp"

#define swapPlayers(A, B) \
    {                      \
        Player *aux = A;       \
        A = B;             \
        B = aux;           \
    }

Round::Round() {
    this->openingBet = 0;
    this->playersAmount = 0;
    this->pot = 0;
    this->isValidRound = true;
    this->winningPlayersAmount;
}

Round::~Round() {
    delete [] this->enrolledPlayers;
    this->enrolledPlayers = nullptr;
}

// Lembre-se de alterar quando a classe "Match" for criada.
void Round::demandOpeningBet() {
    for (int i = 0; i < this->playersAmount; i++) {
        this->enrolledPlayers[i]->makeBet(this->openingBet);
    }
}

void Round::collectBets() {
    for (int i = 0; i < this->playersAmount; i++) {
        this->enrolledPlayers[i]->makeBet(this->betsQueue->dequeue());
    }
}

void Round::sortEnrolledPlayers() {
    for (int i = 0; i < this->playersAmount; i++) {
        int maxPlayer = i;
        for (int j = i; j < this->playersAmount; j++) {
            if (*this->enrolledPlayers[j] > *this->enrolledPlayers[maxPlayer]) {
                maxPlayer = j;
            }
        }
        swapPlayers(this->enrolledPlayers[i], this->enrolledPlayers[maxPlayer]);
    }
}

void Round::decideWinningPlayers() {
    this->sortEnrolledPlayers();

    int highestCombination = this->enrolledPlayers[0]->hand->bestCombination;
    this->winningPlayersAmount++;
    for (int i = 1; i < this->playersAmount; i++) {
        if (this->enrolledPlayers[i]->hand->bestCombination == highestCombination) {
            this->winningPlayersAmount++;
            continue;
        }
        break;
    }
    
}

void Round::straightFlushTieBreaker() {
    int highestStraight = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest > highestStraight) {
            highestStraight = this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::fourOfAKindTieBreaker() {
    int highestFourOfAKind = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind > highestFourOfAKind) {
            highestFourOfAKind = this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind == highestFourOfAKind) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::fullHouseTieBreaker() {
    int highestTrio = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio > highestTrio) {
            highestTrio = this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio == highestTrio) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::flushTieBreaker() {
    int highestCard = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard > highestCard) {
            highestCard = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::straightTieBreaker() {
    int highestStraight = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest > highestStraight) {
            highestStraight = this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::threeOfAKindTieBreaker() {
    int highestTrio = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind > highestTrio) {
            highestTrio = this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestTrio) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::twoPairsTieBreaker() {
    int highestPair = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair > highestPair) {
            highestPair = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {
            this->winners = new Player*[1];
            this->winners[tieWinners] = this->enrolledPlayers[i];
            tieWinners++;
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    int lowestPair = -1;
    for (int i = 0; i < tieWinners; i++) {
        if(this->winners[i]->hand->bestCombinationInfo.lowestPair > lowestPair) {
            lowestPair = this->winners[i]->hand->bestCombinationInfo.lowestPair;
        }
    }
    
    int newTieWinners = 0;
    for (int i = 0; i < tieWinners; i++) {
        if(this->winners[i]->hand->bestCombinationInfo.lowestPair == lowestPair) {
            this->winners = new Player*[1];
            this->winners[tieWinners + newTieWinners] = this->winners[i];
            newTieWinners++;
        }
    }

    tieWinners = 0;
    delete [] this->winners;
    this->winners = nullptr;
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::tieBreaker() {
    Hand cardCombinations;

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.RSF) return;
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.SF) {
        this->straightFlushTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FK) {
        this->fourOfAKindTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FH) {
        this->fullHouseTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.F) {
        this->flushTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.S) {
        this->straightTieBreaker();
    }
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.TK) {
        this->threeOfAKindTieBreaker();
    }
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.TP) {
        this->twoPairsTieBreaker();
    }

}

void Round::transferPotCoinsToWinners() {

}
