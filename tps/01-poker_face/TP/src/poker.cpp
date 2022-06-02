#include <regex>
#include "player.hpp"
#include "bets_queue.hpp"

std::string readName(std::string &aux) {
    std::regex nameRegexp("[A-za-z]+");
    std::string playerName = "";

    std::cin >> aux;
    // Reads the player name
    while (std::regex_match(aux, nameRegexp)) {
        playerName += aux + " ";
        std::cin >> aux;
    }
    playerName[playerName.length() -1] = *"";

    return playerName;
}

int readBet(std::string &aux) {
    std::regex betRegexp("[0-9]+");

    if (!std::regex_match(aux, betRegexp)) {
        std::cout << "A aposta não é válida!" << std::endl;
        return 1;
    }

    return atoi(aux.c_str());
}

int main() {
    BetsChainedQueue *betsQueue;
    betsQueue = new BetsChainedQueue();

    Deck *cardDeck;
    cardDeck = new Deck();

    Player **players;
    int pot = 0;
    int playersAmount = 0, initialCoins = 1000, openingBet = 0;

    std::cin >> playersAmount;
    players = new Player*[playersAmount];
    std::cin >> openingBet;

    std::regex cardRegexp("^[0-9]+[A-Za-z]");
    for (int i = 0; i < playersAmount; i++) {
        std::string aux = "";

        std::string currentPlayerName = readName(aux);
        players[i] = new Player(currentPlayerName, initialCoins);

        int currentPlayerBet = openingBet + readBet(aux);
        if (!players[i]->sanityTest(currentPlayerBet)) {
            std::cout << "Jogador \"" << players[i]->getName() << "\" não possui fichas o suficiente." << std::endl;
            return 1;
        }
        pot += currentPlayerBet;
        betsQueue->enqueue(currentPlayerBet);
        
        for (int j = 0; j < 5; j++) {
            std::cin >> aux;
            if (std::regex_match(aux, cardRegexp)) {
                players[i]->addCard(aux, cardDeck);
            }
        }
    }

    std::cout << "The pot currently is: " << pot << std::endl;
    for (int i = 0; i < playersAmount; i++) {
        players[i]->makeBet(betsQueue->dequeue());
        std::cout << players[i] << std::endl;
    }

    for (int i = 0; i < playersAmount; i++) {
        delete players[i];
    }
    delete []players;

    return 0;
}