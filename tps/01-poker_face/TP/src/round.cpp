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
    this->winningPlayersAmount = 0;
}

Round::Round(int playersAmount, int openingBet) {
    this->openingBet = openingBet;
    this->playersAmount = playersAmount;
    this->pot = 0;
    this->isValidRound = true;
    this->winningPlayersAmount = 0;

    this->enrolledPlayers = new Player*[playersAmount];
    this->cardDeck = new Deck();
    this->betsQueue = new BetsChainedQueue();
}

Round::~Round() {
    for (int i = 0; i < this->playersAmount; i++) {
        delete [] this->enrolledPlayers[i];
        this->enrolledPlayers[i] = nullptr;
    }
    delete [] this->enrolledPlayers;
    this->enrolledPlayers = nullptr;

    for (int i = 0; i < this->winningPlayersAmount; i++) {
        delete [] this->winners[i];
        this->winners = nullptr;
    }
    delete [] this->winners;
    this->winners = nullptr;
}

void Round::invalidateRound() {
    this->isValidRound = false;
}
bool Round::isRoundValid() {
    return this->isValidRound;
}

void Round::addPlayer(int pos, Player *player) {
    this->enrolledPlayers[pos] = player;
}

// Lembre-se de alterar quando a classe "Match" for criada.
void Round::demandOpeningBet() {
    for (int i = 0; i < this->playersAmount; i++) {
        this->pot += this->openingBet;
        this->enrolledPlayers[i]->makeBet(this->openingBet);
    }
}

void Round::pushBet(int bet) {
    this->betsQueue->enqueue(bet);
}

void Round::pushCardToPlayer(int pos, std::string cardCode) {
    this->enrolledPlayers[pos]->addCard(cardCode, this->cardDeck);
}

void Round::collectBets() {
    for (int i = 0; i < this->playersAmount; i++) {
        int bet = this->betsQueue->dequeue();
        this->enrolledPlayers[i]->makeBet(bet);
        this->pot += bet;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind == highestFourOfAKind) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio == highestTrio) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
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
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestTrio) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::twoPairsTieBreaker() {
    // ============================= Desempata pelo maior par ==================================

    int highestPair = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair > highestPair) {
            highestPair = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // =========================== Desempata pelo menor par ======================================

    int lowestPair = -1;
    for (int i = 0; i < tieWinners; i++) {
        if(this->winners[i]->hand->bestCombinationInfo.lowestPair > lowestPair) {
            lowestPair = this->winners[i]->hand->bestCombinationInfo.lowestPair;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // ========================= Desempata pela maior carta =============================

    int highestCard = -1;
    for (int i = 0; i < tieWinners; i++) {
        if(this->winners[i]->hand->bestCombinationInfo.twoPairHighestCard > highestCard) {
            highestCard = this->winners[i]->hand->bestCombinationInfo.twoPairHighestCard;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.twoPairHighestCard == highestCard) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.twoPairHighestCard == highestCard) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::onePairTieBreaker() {
    // ============================= Decidindo empate pelo maior par ==============================
    int highestSinglePair = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair > highestSinglePair) {
            highestSinglePair = this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestSinglePair) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestSinglePair) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // ============================ Decidindo empate pela maior carta ===========================
    int highestCard = -1;
    for (int i = 0; i < tieWinners; i++) {
        if(this->winners[i]->hand->bestCombinationInfo.highestCard > highestCard) {
            highestCard = this->winners[i]->hand->bestCombinationInfo.highestCard;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestSinglePair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestSinglePair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::highestCardTieBreaker() {
    int highestCard = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard > highestCard) {
            highestCard = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::tieBreaker() {
    this->decideWinningPlayers();
    if (this->winningPlayersAmount == 1) {
        this->winners = new Player*[1];
        this->winners[0] = this->enrolledPlayers[0];
        return;
    }

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
        std::cout << "Two pairs!" << std::endl;
        this->twoPairsTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.OP) {
        this->onePairTieBreaker();
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.HC) {
        this->highestCardTieBreaker();
    }

}

void Round::printRoundInfo() {
    std::cout << "================= Round Info ====================" << std::endl;
    std::cout << "Pingo: " << this->openingBet << std::endl;
    std::cout << "Quantidade de jogadores: " << this->playersAmount << std::endl;
    std::cout << "Jogadores:" << std::endl;
    for (int i = 0; i < this->playersAmount; i++) {
        std::cout << "\t" << this->enrolledPlayers[i] << std::endl;
    }
    std::cout << "Quantidade de vencedores: " << this->winningPlayersAmount << std::endl;
    std::cout << "Vencedores: " << std::endl;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        std::cout << "\t" << this->winners[i] << std::endl;
    }
}

void Round::transferPotCoinsToWinners() {
    this->tieBreaker();
    int potCoins = this->pot / this->winningPlayersAmount;

    for (int i = 0; i < this->winningPlayersAmount; i++) {
        this->winners[i]->coins += potCoins;
    }
    
}
