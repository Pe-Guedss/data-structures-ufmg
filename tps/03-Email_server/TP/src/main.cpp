#include "server.hpp"

int main() {
    Server *server;
    server = new Server(5);

    server->sendEmail(10, 1, 5, "Olá, eu sou Pedro! Prazer!");
    server->sendEmail(17, 12, 5, "Olá, eu sou Vinícius! Prazer!");
    server->sendEmail(1, 5, 5, "Olá, eu sou Carlos! Prazer!");
    server->sendEmail(5, 85, 5, "Olá, eu sou João! Prazer!");
    server->sendEmail(19, 9, 5, "Olá, eu sou Outro! Prazer!");

    server->searchEmail(5, 85);
    server->searchEmail(10, 85);
    server->searchEmail(1, 5);

    server->eraseEmail(19, 9);

    OperationsQueue *log;
    log = server->getServerLog();
    while (log->getSize() > 0) std::cout << log->dequeue() << std::endl;
    
    return 0;
}