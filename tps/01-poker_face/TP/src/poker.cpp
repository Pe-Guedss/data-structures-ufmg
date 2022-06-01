#include <regex>
#include "player.hpp"

int main() {
    Deck *cardDeck;
    cardDeck = new Deck();
    Player **players;

    int playersAmount = 0, initialCoins = 1000, entryCoins = 0;

    std::cin >> playersAmount;
    players = new Player*[playersAmount];
    std::cin >> entryCoins;

    std::regex nameRegexp("[A-za-z]+");
    std::regex betRegexp("[0-9]+");
    std::regex cardRegexp("^[0-9]+[A-Za-z]");
    for (int i = 0; i < playersAmount; i++) {
        std::string aux = "", playerName = "";
        std::cin >> aux;
        // Reads the player name
        while (std::regex_match(aux, nameRegexp)) {
            playerName += aux + " ";
            std::cin >> aux;
        }
        playerName[playerName.length() -1] = *"";
        players[i] = new Player(playerName, initialCoins);

        if (!std::regex_match(aux, betRegexp)) {
            std::cout << "A aposta não é válida!" << std::endl;
            return 1;
        }
        if (!players[i]->sanityTest(entryCoins + atoi(aux.c_str()))) {
            std::cout << "Jogador \"" << players[i]->getName() << "\" não possui fichas o suficiente." << std::endl;
            return 1;
        }
        
        for (int j = 0; j < 5; j++) {
            std::cin >> aux;
            if (std::regex_match(aux, cardRegexp)) {
                players[i]->addCard(aux, cardDeck);
            }
        }
    }

    for (int i = 0; i < playersAmount; i++) {
        std::cout << players[i] << std::endl;
    }

    for (int i = 0; i < playersAmount; i++) {
        delete players[i];
    }
    delete []players;

    return 0;
}