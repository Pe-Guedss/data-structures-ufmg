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

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}