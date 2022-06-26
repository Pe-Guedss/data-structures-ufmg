#include "round_queue.hpp"

QueuedRound::QueuedRound() {
    this->round = nullptr;
    this->next = nullptr;
}

RoundsChainedQueue::RoundsChainedQueue() : Queue() {
    this->front = new QueuedRound(); // Célula cabeça;
    this->back = this->front;
}

void RoundsChainedQueue::enqueue(Round *round) {
    QueuedRound *newQueuedRound;
    newQueuedRound = new QueuedRound();
    newQueuedRound->round = round;

    this->back->next = newQueuedRound;
    this->back = newQueuedRound;

    this->size++;
}

Round* RoundsChainedQueue::dequeue() {
    QueuedRound *deQueuedRound;
    Round *aux;

    if (this->size == 0) {
        throw "Fila está vazia!";
    }

    aux = this->front->next->round;
    deQueuedRound = this->front;
    this->front = this->front->next;

    delete deQueuedRound;
    this->size--;

    return aux;
}

void RoundsChainedQueue::clear() {
    QueuedRound *queuedRound;
    queuedRound = this->front->next;

    while(queuedRound != nullptr) {
        this->front->next = queuedRound->next;
        delete queuedRound;
        queuedRound = this->front->next;
    }

    this->size = 0;
    this->back = this->front;
}

RoundsChainedQueue::~RoundsChainedQueue() {
    this->clear();
    delete this->front;
    this->front = nullptr;
}