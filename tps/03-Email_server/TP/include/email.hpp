//---------------------------------------------------------------------
// Arquivo	: email.hpp
// Conteudo	: definicoes da classe Email
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef EMAIL_H
#define EMAIL_H

#include "emailContent.hpp"

/**
 * @brief Classe Email. Define os atributos que identificam e posicionam um e-mail.
 * 
 */
class Email {
    public:
        /**
         * @brief Construtor padrão da classe Email.
         * 
         */
        Email();

        /**
         * @brief Constrói um objeto de e-mail definindo seus identificadores.
         * 
         * @param emailID Identificador do e-mail.
         * @param userID Identificador do usuário que recebe (destinatário).
         */
        Email(int emailID, int userID);

        /**
         * @brief Define o e-mail pai do e-mail atual.
         * 
         * @param parent Referência para o e-mail pai do atual.
         */
        void setParent(Email *parent);

        /**
         * @brief Define o e-mail à esquerda do e-mail atual.
         * 
         * @param leftEmail Referência para o e-mail que se quer deixar à esquerda do atual.
         */
        void setLeftEmail(Email *leftEmail);

        /**
         * @brief Define o e-mail à direita do e-mail atual.
         * 
         * @param rightEmail Referência para o e-mail que se quer deixar à direita do atual.
         */
        void setRightEmail(Email *rightEmail);

        /**
         * @brief Define o conteúdo deste e-mail.
         * 
         * @param wordsAmount Quantidade de palavras que o e-mail armazena.
         * @param msg Mensagem que o e-mail armazena.
         */
        void setContent(int wordsAmount, std::string msg);

        /**
         * @brief Retorna o ID deste e-mail.
         * 
         * @return int -> Identificador do e-mail.
         */
        int getID();

        /**
         * @brief Retorna o ID do usuário que recebeu este e-mail.
         * 
         * @return int -> Identificador do usuário recebedor do e-mail.
         */
        int getAddressee();

    private:
        int id; // ID referente ao e-mail.
        int addressee; // ID do usuário ao qual o e-mail foi destinado.

        EmailContent content;

        Email *parent; // E-mail pai na árvore da caixa de entrada.
        Email *leftEmail; // E-mail à esquerda deste e-mail atual.
        Email *rightEmail; // E-mail à direita deste e-mail atual.

    /**
     * @brief Método para imprimir o conteúdo do e-mail.
     */
    friend std::ostream &operator<<(std::ostream &out, const Email *email);

    friend class Inbox;
};

#endif