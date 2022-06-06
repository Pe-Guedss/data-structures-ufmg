#include "bets_queue.hpp"

Bet::Bet() {
    this->bet = -1;
    this->next = nullptr;
}

BetsChainedQueue::BetsChainedQueue() : Queue() {
    this->front = new Bet(); // Célula cabeça;
    this->back = this->front;
}

void BetsChainedQueue::enqueue(int bet) {
    Bet *newBet;
    newBet = new Bet();
    newBet->bet = bet;

    this->back->next = newBet;
    this->back = newBet;

    this->size++;
}

int BetsChainedQueue::dequeue() {
    Bet *dequeuedBet;
    int aux;

    if (this->size == 0) {
        throw "Fila está vazia!";
    }

    aux = this->front->next->bet;
    dequeuedBet = this->front;
    this->front = this->front->next;

    delete dequeuedBet;
    this->size--;

    return aux;
}

void BetsChainedQueue::clear() {
    Bet *bet;
    bet = this->front->next;

    while(bet != nullptr) {
        this->front->next = bet->next;
        delete bet;
        bet = this->front->next;
    }

    this->size = 0;
    this->back = this->front;
}

BetsChainedQueue::~BetsChainedQueue() {
    this->clear();
    delete this->front;
}