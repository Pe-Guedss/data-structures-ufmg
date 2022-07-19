#include "inbox.hpp"

Inbox::Inbox() {
    this->root = nullptr;
}

Inbox::~Inbox() {
    this->cleanInbox(this->root);
}

std::string Inbox::searchEmail(int emailID) {
    Email *aux;
    aux = this->root;

    while (aux != nullptr) {
        if (aux->getID() == emailID) return aux->content.getMessage();
        
        else if (emailID < aux->getID()) aux = aux->leftEmail;

        else if (emailID > aux->getID()) aux = aux->rightEmail;
    }

    return "MENSAGEM INEXISTENTE";
}

void Inbox::addEmail(int emailID, int userID,
                      int wordsAmount, std::string msg) {
    EmailContent emailContent;
    emailContent = EmailContent(wordsAmount, msg);

    return this->insertEmail(emailID, userID, emailContent, this->root);
}

void Inbox::insertEmail(int emailID, int userID,
                        EmailContent emailContent, Email* &email) {
    if (email == nullptr) {
        email = new Email(emailID, userID);
        email->content = emailContent;
    }
    else {
        if (emailID < email->getID()) this->insertEmail(emailID, userID, emailContent, email->leftEmail);

        if (emailID > email->getID()) this->insertEmail(emailID, userID, emailContent, email->rightEmail);
    }
}

bool Inbox::deleteEmail(int emailID) {
    return this->removeEmail(this->root, emailID);
}

bool Inbox::removeEmail(Email* &email, int emailID) {
    if (email == nullptr) return false;

    else if (emailID < email->getID()) return this->removeEmail(email->leftEmail, emailID);

    else if (emailID > email->getID()) return this->removeEmail(email->rightEmail, emailID);

    else {
        Email *aux;
        if (email->rightEmail == nullptr) {
            aux = email;
            email = email->leftEmail;

            delete aux;
            aux = nullptr;
        }
        else if (email->leftEmail == nullptr) {
            aux = email;
            email = email->rightEmail;
            
            delete aux;
            aux = nullptr;
        }
        else
            this->replacePredecessor(email, email->leftEmail);
        
        return true;
    }
}

void Inbox::replacePredecessor(Email *deletedEmail, Email* &substitute) {
    if(substitute->rightEmail != nullptr) {
        this->replacePredecessor(deletedEmail, substitute->rightEmail);
        return;
    }

    deletedEmail->content = substitute->content;
    deletedEmail->id = substitute->id;
    deletedEmail->addressee = substitute->addressee;
    deletedEmail = substitute;
    substitute = substitute->leftEmail;

    delete deletedEmail;
    deletedEmail = nullptr;
}

void Inbox::cleanInbox(Email *root) {
    if(root != nullptr){
        this->cleanInbox(root->leftEmail);
        this->cleanInbox(root->rightEmail);
        delete root;
        root = nullptr;
    }
}

void Inbox::preOrderPrint(Email *email) {
    if (email != nullptr) {
        std::cout << "-------------------" << std::endl;
        std::cout << email << std::endl;
        std::cout << "-------------------" << std::endl;

        this->preOrderPrint(email->leftEmail);
        this->preOrderPrint(email->rightEmail);
    }
    
}

void Inbox::print() {
    this->preOrderPrint(this->root);
}