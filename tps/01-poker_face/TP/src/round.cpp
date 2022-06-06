#include "round.hpp"
#include "memlog.hpp"

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

Round::Round(int roundId, int playersAmount, int openingBet) {
    this->roundId = roundId;

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

void Round::checkPlayerHand(int playerPos) {
    LEMEMLOG( (long int) (&this->enrolledPlayers[playerPos]->hand), sizeof(Hand), this->roundId );
    if ( !this->enrolledPlayers[playerPos]->hand->checkValidHand() ) {
        this->invalidateRound();
    }
}

void Round::invalidateRound() {
    this->isValidRound = false;
}
bool Round::isRoundValid() {
    return this->isValidRound;
}

void Round::addPlayer(int pos, Player *player) {
    ESCREVEMEMLOG( (long int) (&this->enrolledPlayers[pos]), sizeof(Player), this->roundId );
    this->enrolledPlayers[pos] = player;
}

// Lembre-se de alterar quando a classe "Match" for criada.
void Round::addOpeningBetToPot(int openingBetTotal) {
    this->pot += openingBetTotal;
}

void Round::pushBet(int bet) {
    ESCREVEMEMLOG( (long int) (&this->betsQueue), sizeof(int), this->roundId );
    this->betsQueue->enqueue(bet);
}

void Round::pushCardToPlayer(int pos, std::string cardCode) {
    ESCREVEMEMLOG( (long int) (&this->enrolledPlayers[pos]->hand), sizeof(Card), this->roundId );
    this->enrolledPlayers[pos]->addCard(cardCode, this->cardDeck);
}

void Round::collectBets() {
    for (int i = 0; i < this->playersAmount; i++) {
        int bet = this->betsQueue->dequeue();
        this->enrolledPlayers[i]->makeBet(bet);
        this->pot += bet;
        ESCREVEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
    }
}

void Round::sortEnrolledPlayers() {
    for (int i = 0; i < this->playersAmount; i++) {
        int maxPlayer = i;
        for (int j = i; j < this->playersAmount; j++) {
            LEMEMLOG( (long int) (&this->enrolledPlayers[j]), sizeof(int), this->roundId );
            if (*this->enrolledPlayers[j] > *this->enrolledPlayers[maxPlayer]) {
                maxPlayer = j;
            }
        }
        swapPlayers(this->enrolledPlayers[i], this->enrolledPlayers[maxPlayer]);
        ESCREVEMEMLOG( (long int) (&this->enrolledPlayers[maxPlayer]), sizeof(Player), this->roundId );
        ESCREVEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(Player), this->roundId );
    }
}

void Round::decideWinningPlayers() {
    this->sortEnrolledPlayers();

    int highestCombination = this->enrolledPlayers[0]->hand->bestCombination;
    LEMEMLOG( (long int) (&this->enrolledPlayers[0]), sizeof(int), this->roundId );
    this->winningPlayersAmount++;
    for (int i = 1; i < this->playersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if (this->enrolledPlayers[i]->hand->bestCombination == highestCombination) {
            this->winningPlayersAmount++;
            continue;
        }
    }
}

void Round::straightFlushTieBreaker() {
    int highestStraight = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest > highestStraight) {
            highestStraight = this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
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
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind > highestFourOfAKind) {
            highestFourOfAKind = this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind == highestFourOfAKind) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fourOfAKind == highestFourOfAKind) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::fullHouseTieBreaker() {
    int highestTrio = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio > highestTrio) {
            highestTrio = this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio == highestTrio) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.fullHouseTrio == highestTrio) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::flushTieBreaker() {
    int highestCard = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard > highestCard) {
            highestCard = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::straightTieBreaker() {
    int highestStraight = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest > highestStraight) {
            highestStraight = this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.straightHighest == highestStraight) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::threeOfAKindTieBreaker() {
    int highestTrio = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind > highestTrio) {
            highestTrio = this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestTrio) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.threeOfAKind == highestTrio) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::twoPairsTieBreaker() {
    // ============================= Desempata pelo maior par ==================================

    int highestPair = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair > highestPair) {
            highestPair = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // =========================== Desempata pelo menor par ======================================

    int lowestPair = -1;
    for (int i = 0; i < tieWinners; i++) {
        LEMEMLOG( (long int) (&this->winners[i]), sizeof(int), this->roundId );
        if(this->winners[i]->hand->bestCombinationInfo.lowestPair > lowestPair) {
            lowestPair = this->winners[i]->hand->bestCombinationInfo.lowestPair;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // ========================= Desempata pela maior carta =============================

    int highestCard = -1;
    for (int i = 0; i < tieWinners; i++) {
        LEMEMLOG( (long int) (&this->winners[i]), sizeof(int), this->roundId );
        if(this->winners[i]->hand->bestCombinationInfo.twoPairHighestCard > highestCard) {
            highestCard = this->winners[i]->hand->bestCombinationInfo.twoPairHighestCard;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.twoPairHighestCard == highestCard) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.lowestPair == lowestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.highestPair == highestPair &&
            this->enrolledPlayers[i]->hand->bestCombinationInfo.twoPairHighestCard == highestCard) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::onePairTieBreaker() {
    // ============================= Decidindo empate pelo maior par ==============================
    int highestSinglePair = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair > highestSinglePair) {
            highestSinglePair = this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair == highestSinglePair) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair == highestSinglePair) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }

    if (tieWinners == 1) {
        this->winningPlayersAmount = tieWinners;
        return;
    }

    // ============================ Decidindo empate pela maior carta ===========================
    int highestCard = -1;
    for (int i = 0; i < tieWinners; i++) {
        LEMEMLOG( (long int) (&this->winners[i]), sizeof(int), this->roundId );
        if(this->winners[i]->hand->bestCombinationInfo.singlePairHighestCard > highestCard) {
            highestCard = this->winners[i]->hand->bestCombinationInfo.singlePairHighestCard;
        }
    }
    
    tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair == highestSinglePair &&
           this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePairHighestCard == highestCard) {

            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePair == highestSinglePair &&
           this->enrolledPlayers[i]->hand->bestCombinationInfo.singlePairHighestCard == highestCard) {

            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::highestCardTieBreaker() {
    int highestCard = -1;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard > highestCard) {
            highestCard = this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard;
        }
    }
    
    int tieWinners = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            tieWinners++;
        }
    }

    this->winners = new Player*[tieWinners];
    int playerPos = 0;
    for (int i = 0; i < this->winningPlayersAmount; i++) {
        LEMEMLOG( (long int) (&this->enrolledPlayers[i]), sizeof(int), this->roundId );
        if(this->enrolledPlayers[i]->hand->bestCombinationInfo.highestCard == highestCard) {
            this->winners[playerPos] = this->enrolledPlayers[i];
            playerPos++;
            ESCREVEMEMLOG( (long int) (&this->winners[playerPos]), sizeof(Player), this->roundId );
        }
    }
    
    this->winningPlayersAmount = tieWinners;
    return;
}

void Round::tieBreaker() {
    this->decideWinningPlayers();
    if (this->winningPlayersAmount == 1) {
        this->winners = new Player*[1];
        ESCREVEMEMLOG( (long int) (&this->winners[0]), sizeof(Player), this->roundId );
        this->winners[0] = this->enrolledPlayers[0];
        return;
    }

    Hand cardCombinations;

    LEMEMLOG( (long int) (&this->enrolledPlayers[0]), sizeof(int), this->roundId );

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.RSF) {
        this->winners = new Player*[winningPlayersAmount];
        for (int i = 0; i < this->winningPlayersAmount; i++) {
            ESCREVEMEMLOG( (long int) (&this->winners[i]), sizeof(Player), this->roundId );
            this->winners[i] = this->enrolledPlayers[i];
        }
        
        return;
    }
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.SF) {
        this->straightFlushTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FK) {
        this->fourOfAKindTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.FH) {
        this->fullHouseTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.F) {
        this->flushTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.S) {
        this->straightTieBreaker();
        return;
    }
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.TK) {
        this->threeOfAKindTieBreaker();
        return;
    }
    
    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.TP) {
        this->twoPairsTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.OP) {
        this->onePairTieBreaker();
        return;
    }

    if (this->enrolledPlayers[0]->hand->bestCombination == cardCombinations.HC) {
        this->highestCardTieBreaker();
        return;
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
    std::cout << "Combinação vencedora: " << this->enrolledPlayers[0]->hand->getBestCombinationCode() << std::endl;
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
        ESCREVEMEMLOG( (long int) (&this->winners[i]), sizeof(int), this->roundId );
    }
    
}
