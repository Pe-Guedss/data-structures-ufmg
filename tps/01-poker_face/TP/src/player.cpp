#include "player.hpp"

Player::Player() {
    this->name = "";
    this->coins = -1;
    this->hand = nullptr;
}

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}