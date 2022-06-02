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

void Round::tieBreaker() {
    Hand cardCombinations;

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.RSF) return;
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.SF) {
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
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FK) {
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
    }
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FH) {
        /* code */
    }
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.F) {
        /* code */
    }
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.S) {
        /* code */
    }
    
}

void Round::transferPotCoinsToWinners() {

}
