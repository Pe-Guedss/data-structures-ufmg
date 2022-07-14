//---------------------------------------------------------------------
// Arquivo	: email.hpp
// Conteudo	: definicoes da classe Email
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
         * @param charactersAmount Quantidade de caracteres da mensagem
         * @param msg Mensagem armazenada pelo e-mail
         */
        EmailContent(int charactersAmount, std::string msg);

    private:
        std::string msg;
        int charactersAmount;
};

#endif