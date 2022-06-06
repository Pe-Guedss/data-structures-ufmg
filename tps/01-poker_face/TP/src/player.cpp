#include "player.hpp"

Player::Player() {
    this->name = "";
    this->coins = -1;
    this->hand = nullptr;
}

Player::Player(std::string name, int coins) {
    this->name = name;
    this->coins = coins;
    this->hand = new Hand();
}

std::string Player::getName() {
    return this->name;
}

int Player::getCoins() {
    return this->coins;
}

bool Player::sanityTest(int coinAmount) {
    return (this->coins - coinAmount < 0) ? false : true;
}

void Player::makeBet(int bet) {
    this->coins -= bet;
}

void Player::addCard(std::string cardCode, Deck *cardDeck) {
    this->hand->addCard(cardCode, cardDeck);
}

std::ostream &operator<<(std::ostream &out, const Player *player) {
    out << "===== Player Info =====" << std::endl;
    out << "Name: " << player->name << std::endl;
    out << "Current amount of coins: " << player->coins << std::endl;
    out << "Current hand: " << player->hand << std::endl;
    
    return out;
}

std::ostream &operator<<(std::ostream &out, const Player player) {
    out << "===== Player Info =====" << std::endl;
    out << "Name: " << player.name << std::endl;
    out << "Current amount of coins: " << player.coins << std::endl;
    out << "Current hand: " << player.hand << std::endl;
    
    return out;
}

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}