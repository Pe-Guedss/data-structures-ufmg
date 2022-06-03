#include "players_queue.hpp"

QueuedPlayer::QueuedPlayer() {
    this->player = nullptr;
    this->next = nullptr;
}

PlayersChainedQueue::PlayersChainedQueue() : Queue() {
    this->front = new QueuedPlayer(); // Célula cabeça;
    this->back = this->front;
}

void PlayersChainedQueue::enqueue(Player *player) {
    QueuedPlayer *newQueuedPlayer;
    newQueuedPlayer = new QueuedPlayer();
    newQueuedPlayer->player = player;

    this->back->next = newQueuedPlayer;
    this->back = newQueuedPlayer;

    this->size++;
}

Player* PlayersChainedQueue::dequeue() {
    QueuedPlayer *dequeuedPlayer;
    Player *aux;

    if (this->size == 0) {
        throw "Fila está vazia!";
    }

    aux = this->front->next->player;
    dequeuedPlayer = this->front;
    this->front = this->front->next;

    delete dequeuedPlayer;
    this->size--;

    return aux;
}

void PlayersChainedQueue::clear() {
    QueuedPlayer *queuedPlayer;
    queuedPlayer = this->front->next;

    while(queuedPlayer != nullptr) {
        this->front->next = queuedPlayer->next;
        delete queuedPlayer;
        queuedPlayer = this->front->next;
    }

    this->size = 0;
    this->back = this->front;
}

PlayersChainedQueue::~PlayersChainedQueue() {
    this->clear();
    delete this->front;
    this->front = nullptr;
}