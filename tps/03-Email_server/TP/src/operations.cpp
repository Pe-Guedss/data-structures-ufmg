#include "operations.hpp"

Operation::Operation() {
    this->operation = "";
    this->next = nullptr;
}

OperationsQueue::OperationsQueue() : Queue() {
    this->front = new Operation(); // Célula cabeça;
    this->back = this->front;
}

void OperationsQueue::enqueue(std::string operation) {
    Operation *newOperation;
    newOperation = new Operation();
    newOperation->operation = operation;

    this->back->next = newOperation;
    this->back = newOperation;

    this->size++;
}

std::string OperationsQueue::dequeue() {
    Operation *dequeuedOperation;
    std::string aux;

    if (this->size == 0) {
        throw "Fila está vazia!";
    }

    aux = this->front->next->operation;
    dequeuedOperation = this->front;
    this->front = this->front->next;

    delete dequeuedOperation;
    this->size--;

    return aux;
}

void OperationsQueue::clear() {
    Operation *operation;
    operation = this->front->next;

    while(operation != nullptr) {
        this->front->next = operation->next;
        delete operation;
        operation = this->front->next;
    }

    this->size = 0;
    this->back = this->front;
}

OperationsQueue::~OperationsQueue() {
    this->clear();
    delete this->front;
}