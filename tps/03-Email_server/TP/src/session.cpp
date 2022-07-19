#include "session.hpp"
#include "msgassert.hpp"

#include <fstream>
#include <sstream>

Session::Session() {
    this->server = nullptr;
}

Session::Session(std::string sessionInputs) {
    std::ifstream serverSession(sessionInputs); // Abre o arquivo de texto com as entradas.
    erroAssert(serverSession, "Ocorreu um erro ao abrir o arquivo de entrada.");

    int usersAmount; // Variável para coletar a quantidade de usuários do servidor
    serverSession >> usersAmount;
    this->server = new Server(usersAmount);

    // Leitura das operações a serem realizadas no servidor
    std::string auxLine, word;
    while( std::getline(serverSession, auxLine) ) {
        int userID, emailID;

        std::stringstream line(auxLine);
        line >> word >> userID >> emailID;

        if (word == "ENTREGA") {
            int wordsAmount;
            line >> wordsAmount;

            std::string msg;
            std::getline(line, msg);

            this->server->sendEmail(userID, emailID, wordsAmount, msg.substr(1, -1));
        }
        else if (word == "CONSULTA") {
            this->server->searchEmail(userID, emailID);
        }
        else if (word == "APAGA") {
            this->server->eraseEmail(userID, emailID);
        }
    }

    serverSession.close(); // Fechamento do arquivo.
}

Session::~Session() {
    this->server->~Server();
    this->server = nullptr;
}

void Session::finish(std::string sessionLogs) {
    std::ofstream sessionResults(sessionLogs);
    erroAssert(sessionResults, "Ocorreu um erro ao abrir o arquivo de saída.");

    OperationsQueue *logs;
    logs = this->server->getServerLog();
    while (logs->getSize() > 0) sessionResults << logs->dequeue() << std::endl;

    sessionResults.close();
}