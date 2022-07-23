//---------------------------------------------------------------------
// Arquivo	: session.hpp
// Conteudo	: definicoes da classe Session
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef SESSION_H
#define SESSION_H

#include "server.hpp"

/**
 * @brief Classe Inbox. Define o sistema de armazenamento de e-mails para os usuários.
 * 
 */
class Session {
    public:
        /**
         * @brief Construtor padrão da classe Session. Inicia um novo servidor vazio.
         * 
         */
        Session();

        /**
         * @brief Inicializa uma nova sessão no servidor de e-mails, o que o habilita para realizar operações.
         * 
         * @param sessionInputs Arquivo de texto que contém as operações a serem realizadas no servidor.
         */
        Session(std::string sessionInputs);

        /**
         * @brief Destrutor da classe Session. Apaga todos os dados do servidor.
         * 
         */
        ~Session();

        /**
         * @brief Finaliza a sessão no servidor, imprimindo todos os logs de execução no arquivo executado.
         * 
         * @param sessionLogs Caminho para o arquivo de texto onde os resultados das operações efetuadas durante a sessão serão registrados.
         */
        void finish(std::string sessionLogs);


    private:
        Server *server;

};

#endif