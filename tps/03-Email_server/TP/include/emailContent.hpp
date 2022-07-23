//---------------------------------------------------------------------
// Arquivo	: emailContent.hpp
// Conteudo	: definicoes da classe EmailContent
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef EMAIL_CONTENT_H
#define EMAIL_CONTENT_H

#include <iostream>
#include <string>

#include "memlog.hpp"

/**
 * @brief Classe EmailContent. Define o conteúdo que um e-mail apresenta.
 * 
 */
class EmailContent {
    public:
        /**
         * @brief Construtor padrão da classe EmailContent.
         * 
         */
        EmailContent();

        /**
         * @brief Constrói um novo Conteúdo de Email com conteúdos específicos informados.
         * 
         * @param wordsAmount Quantidade de caracteres da mensagem
         * @param msg Mensagem armazenada pelo e-mail
         */
        EmailContent(int wordsAmount, std::string msg);

        /**
         * @brief Retorna a mensagem que o e-mail armazena como conteúdo.
         * 
         * @return std::string -> Mensagem armazenada pelo e-mail.
         */
        std::string getMessage();

    private:
        std::string msg;
        int wordsAmount;

    /**
     * @brief Método para imprimir o conteúdo do e-mail.
     */
    friend std::ostream &operator<<(std::ostream &out, const EmailContent *emailContent);
};

#endif