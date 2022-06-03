#include <regex>
#include "round.hpp"

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
    Player **players;
    int playersAmount = 0, initialCoins = 1000, openingBet = 0;


    Round *round;

    std::cin >> playersAmount;
    players = new Player*[playersAmount];
    std::cin >> openingBet;

    round = new Round(playersAmount, openingBet);

    std::regex cardRegexp("^[0-9]+[A-Za-z]");
    for (int i = 0; i < playersAmount; i++) {
        std::string aux = "";

        std::string currentPlayerName = readName(aux);
        players[i] = new Player(currentPlayerName, initialCoins);

        int currentPlayerBet = readBet(aux);
        if (!players[i]->sanityTest(currentPlayerBet + openingBet)) {
            std::cout << "Jogador \"" << players[i]->getName() << "\" não possui fichas o suficiente." << std::endl;
            round->invalidateRound();
        }

        round->pushBet(currentPlayerBet);
        round->addPlayer(i, players[i]);
        
        for (int j = 0; j < 5; j++) {
            std::cin >> aux;
            if (std::regex_match(aux, cardRegexp)) {
                round->pushCardToPlayer(i, aux);
            }
        }
    }

    if (round->isRoundValid()) {

        round->demandOpeningBet();
        round->collectBets();
        round->transferPotCoinsToWinners();
        round->printRoundInfo();
    }
    
    // for (int i = 0; i < playersAmount; i++) {
    //     delete players[i];
    // }
    // delete []players;

    return 0;
}