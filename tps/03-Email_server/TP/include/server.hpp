//---------------------------------------------------------------------
// Arquivo	: server.hpp
// Conteudo	: definicoes da classe Server 
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "inbox.hpp"
#include "operations.hpp"

/**
 * @brief Classe Inbox. Define o sistema de armazenamento de e-mails para os usuários.
 * 
 */
class Server {
    public:
        /**
         * @brief Construtor padrão da classe Server. Inicia um novo servidor vazio.
         * 
         */
        Server();

        /**
         * @brief Constrói um novo servidor de e-mail para a quantidade de usuários especificada.
         * 
         * @param usersAmount Quantidade de usuários do servidor de e-mail.
         */
        Server(int usersAmount);

        /**
         * @brief Destrutor da classe Server. Exclui todos os registros dos usuários ao fim da sessão.
         * 
         */
        ~Server();

        /**
         * @brief Realiza a operação de envio de e-mail.
         * 
         * @param emailID Identificador do e-mail.
         * @param userID Identificador do destinatário.
         * @param wordsAmount Quantidade de palavras no e-mail.
         * @param msg Mensagem a ser enviada para o destinatário.
         * 
         */
        void sendEmail(int addressee, int emailID, int wordsAmount, std::string msg);

        /**
         * @brief Procura um e-mail na caixa de entrada de um dos usuários.
         * 
         * @param userID Identificador do usuário que se quer ler o e-mail.
         * @param emailID Identificador do e-mail que se quer ler.
         */
        void searchEmail(int userID, int emailID);

        /**
         * @brief Deleta um e-mail de um usuário específico que se está buscando.
         * 
         * @param userID Identificador do usuário que se quer deletar o e-mail.
         * @param emailID Identificador do e-mail que se quer deletar.
         */
        void eraseEmail(int userID, int emailID);

        /**
         * @brief Retorna o Log de operações executadas no servidor.
         * 
         * @return OperationsQueue* -> Log de operações
         */
        OperationsQueue *getServerLog();


    private:
        OperationsQueue *operationsLog; // Log de execução das operações no servidor.

        Inbox *usersInbox; // Caixas de entrada dos usuários.

        int usersAmount; // Quantidade de usuários do servidor.

};

#endif