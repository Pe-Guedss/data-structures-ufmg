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

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}