#include "server.hpp"

Server::Server() {
    this->usersInbox = nullptr;
    this->operationsLog = nullptr;
    this->usersAmount = -1;

    this->id = 0;
}

Server::Server(int usersAmount) {
    this->usersInbox = new Inbox[usersAmount];
    this->operationsLog = new OperationsQueue();
    this->usersAmount = usersAmount;

    this->id = 0;
}

Server::~Server() {
    for (int i = 0; i < this->usersAmount; i++) {
        this->usersInbox[i].cleanInbox(this->usersInbox[i].root);
    }

    this->operationsLog->clear();
    
    this->usersAmount = -1;
}

void Server::sendEmail(int addressee, int emailID, int wordsAmount, std::string msg) {
    int userHash = addressee % this->usersAmount;
    this->usersInbox[userHash].addEmail(emailID, addressee, wordsAmount, msg);
    ESCREVEMEMLOG((long int) &this->usersInbox[userHash], sizeof(Email), this->id);

    std::string operation = std::string("OK: MENSAGEM ");
    operation.append(std::to_string(emailID) + " PARA " + std::to_string(addressee));
    operation.append(" ARMAZENADA EM " + std::to_string(userHash));
    this->operationsLog->enqueue(operation);
    ESCREVEMEMLOG((long int) &this->operationsLog, sizeof(operation), this->id);
}

void Server::searchEmail(int userID, int emailID) {
    int userHash = userID % this->usersAmount;
    std::string emailMessage = this->usersInbox[userHash].searchEmail(emailID, userID);
    LEMEMLOG((long int) &this->usersInbox[userHash], sizeof(Email), this->id);

    std::string operation = std::string("CONSULTA ");
    operation.append(std::to_string(userID) + " " + std::to_string(emailID) + ": ");
    operation.append(emailMessage);
    this->operationsLog->enqueue(operation);
    ESCREVEMEMLOG((long int) &this->operationsLog, sizeof(operation), this->id);
}

void Server::eraseEmail(int userID, int emailID) {
    int userHash = userID % this->usersAmount;
    bool emailDeleted = this->usersInbox[userHash].deleteEmail(emailID, userID);

    if (emailDeleted) {
        this->operationsLog->enqueue("OK: MENSAGEM APAGADA");
        ESCREVEMEMLOG((long int) &this->usersInbox[userHash], sizeof(Email), this->id);
    }
    
    else this->operationsLog->enqueue("ERRO: MENSAGEM INEXISTENTE");

    ESCREVEMEMLOG((long int) &this->operationsLog, sizeof(std::string), this->id);
}

OperationsQueue* Server::getServerLog() {
    return this->operationsLog;
}