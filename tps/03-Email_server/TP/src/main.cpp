#include "inbox.hpp"

int main() {
    Inbox *inbox;
    inbox = new Inbox();

    inbox->addEmail(10, 15, 5, "Olá, eu sou Pedro! Prazer!");
    inbox->addEmail(11, 12, 5, "Olá, eu sou Pedro! Prazer!");
    inbox->addEmail(1, 16, 5, "Olá, eu sou Pedro! Prazer!");

    std::cout << "Consulta U E: " << inbox->searchEmail(1) << std::endl;

    inbox->deleteEmail(10);

    inbox->print();
    
    return 0;
}