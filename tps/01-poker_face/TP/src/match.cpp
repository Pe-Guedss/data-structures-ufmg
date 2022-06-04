#include "match.hpp"
#include <fstream>
#include <regex>

#define swapPlayers(A, B) \
    {                      \
        Player *aux = A;       \
        A = B;             \
        B = aux;           \
    }

Match::Match() {
    this->initialPlayerCoins = 0;
    this->players = nullptr;
    this->rounds = nullptr;
}

Match::Match(std::string matchDataPath) {
    std::ifstream matchInput(matchDataPath);
    
    int roundAmount = 0, initialCoins = 0;
    matchInput >> roundAmount;
    matchInput >> initialCoins;

    this->rounds = new RoundsChainedQueue();

    std::regex nameRegexp("[A-za-z]+");
    std::regex betRegexp("[0-9]+");
    std::regex cardRegexp("^[0-9]+[A-Za-z]");

    for (int i = 0; i < roundAmount; i++) {
        int playersAmount = 0, openingBet = 0;
        matchInput >> playersAmount >> openingBet;

        Round *round;
        round = new Round(playersAmount, openingBet);

        if (i == 0) {
            this->playersAmount = playersAmount;
            this->players = new Player*[playersAmount];
        } else {
            for (int k = 0; k < playersAmount; k++) {
                if(!this->players[k]->sanityTest(openingBet)) round->invalidateRound();
                continue;
            }
        }

        for (int j = 0; j < playersAmount; j++) {
            // ==================== Handles player name readings ========================
            std::string currentPlayerName = "";

            std::string aux = "";
            matchInput >> aux;
            while (std::regex_match(aux, nameRegexp)) {
                currentPlayerName += aux + " ";
                matchInput >> aux;
            }
            currentPlayerName[currentPlayerName.length() - 1] = *"";

            if (i == 0) {
                this->players[j] = new Player(currentPlayerName, initialCoins);
                round->addPlayer(j, players[j]);
            }
            else {
                Player *aux;
                aux = this->findPlayer(currentPlayerName);
                if (!aux) {
                    round->invalidateRound();
                    continue;
                }
                
                round->addPlayer(j, aux);
                round->enrolledPlayers[j]->hand->cleanHand();
            }

            // ================== Handles pleyer bet reading =============================
            if (!std::regex_match(aux, betRegexp)) {
                round->invalidateRound();
                continue;
            }

            int currentPlayerBet = atoi(aux.c_str());
            if (currentPlayerBet % 50 != 0) {
                round->invalidateRound();
                continue;
            }
            
            if (i == 0) {
                if (!round->enrolledPlayers[j]->sanityTest(currentPlayerBet + openingBet)) {
                    round->invalidateRound();
                    continue;
                }
            }
            else {
                if (!round->enrolledPlayers[j]->sanityTest(currentPlayerBet)) {
                    round->invalidateRound();
                    continue;
                }
            }

            round->pushBet(currentPlayerBet);

            // ======================== Handles player card reading ============================
            for (int k = 0; k < 5; k++) {
                matchInput >> aux;
                if (std::regex_match(aux, cardRegexp)) {
                    round->pushCardToPlayer(j, aux);
                }
            }
            
            round->checkPlayerHand(j);
        }

        if (round->isRoundValid()) {

            this->chargeOpeningBet(openingBet);
            round->addOpeningBetToPot(this->playersAmount * openingBet);
            round->collectBets();
            round->transferPotCoinsToWinners();
        }

        this->rounds->enqueue(round);
    }

    matchInput.close();
}

void Match::chargeOpeningBet(int openingBet) {
    for (int i = 0; i < this->playersAmount; i++) {
        this->players[i]->makeBet(openingBet);
    }
}

Player *Match::findPlayer(std::string playerName) {
    for (int i = 0; i < this->playersAmount; i++) {
        if (this->players[i]->getName() == playerName){
            return this->players[i];
        }
    }
    
    return nullptr;
}

void Match::sortPlayersByCoins() {
    for (int i = 0; i < this->playersAmount; i++) {
        int maxPlayer = i;
        for (int j = i; j < this->playersAmount; j++) {
            if (this->players[j]->getCoins() > this->players[maxPlayer]->getCoins()) {
                maxPlayer = j;
            }
        }
        swapPlayers(this->players[i], this->players[maxPlayer]);
    }
}

void Match::printMatchResults() {
    this->sortPlayersByCoins();

    while (!this->rounds->isEmpty()) {
        this->rounds->dequeue()->printRoundInfo();
    }

    std::cout << "=============== Ranking ================" << std::endl;
    for (int i = 0; i < this->playersAmount; i++) {
        std::cout << this->players[i] << std::endl;
    }
}

void Match::play(std::string matchResultsPath) {
    this->sortPlayersByCoins();

    std::ofstream matchResults(matchResultsPath);
    Round *aux;

    while (!this->rounds->isEmpty()) {
        aux = this->rounds->dequeue();
        if (aux->isRoundValid()) {
            matchResults << aux->winningPlayersAmount << " " << aux->pot << " " << aux->winners[0]->hand->getBestCombinationCode() << std::endl;
            for (int i = 0; i < aux->winningPlayersAmount; i++) {
                matchResults << aux->winners[i]->getName() << std::endl;
            }
        }
        else {
            matchResults << "0 0 I" << std::endl;
        }
    }

    matchResults << "####" << std::endl;

    for (int i = 0; i < this->playersAmount; i++) {
        matchResults << this->players[i]->getName() << " " << this->players[i]->getCoins() << std::endl;
    }

    matchResults.close();
}

Match::~Match() {
    for (int i = 0; i < this->playersAmount; i++) {
        delete this->players[i];
        this->players[i] = nullptr;
    }
    delete [] this->players;
    this->players = nullptr;

    delete this->rounds;
    this->rounds = nullptr;
}