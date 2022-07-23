#include "email.hpp"

Email::Email() {
    this->addressee = -1;
    this->id = -1;

    this->content = EmailContent();

    this->parent = nullptr;
    this->leftEmail = nullptr;
    this->rightEmail = nullptr;
}

Email::Email(int emailID, int userID) {
    this->addressee = userID;
    this->id = emailID;

    this->content = EmailContent();

    this->parent = nullptr;
    this->leftEmail = nullptr;
    this->rightEmail = nullptr;
}

void Email::setParent(Email *parent) {
    this->parent = parent;
}

void Email::setLeftEmail(Email *leftEmail) {
    this->leftEmail = leftEmail;
}

void Email::setRightEmail(Email *rightEmail) {
    this->rightEmail = rightEmail;
}

void Email::setContent(int wordsAmount, std::string msg) {
    this->content = EmailContent(wordsAmount, msg);
}

int Email::getID() {
    return this->id;
}

int Email::getAddressee() {
    return this->addressee;
}

std::ostream &operator<<(std::ostream &out, const Email *email) {
    out << "O ID deste e-mail é: " << email->id << std::endl;
    out << "Ele foi recebido pelo usuário de ID: " << email->addressee << std::endl;
    out << &email->content;
    
    return out;
}