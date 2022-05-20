//---------------------------------------------------------------------
// Arquivo	: card.h
// Conteudo	: definicoes da classe Carta
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

/**
 * @brief Classe que armazena e gerencia as informacoes das cartas do baralho, enquanto objetos individuais.
 *
 */
class Card {
    public:
        /**
         * @brief Construtor padrao que inicializa todas as variaveis privadas da classe.
         */
        Card();
        /**
         * @brief Construtor que inicia os valores da carta como se deve.
         * 
         * @param number Número associado à carta (1 a 13)
         * @param nipe Naipe associado à carta (O, E, C, P)
         */
        Card(const int& number, const char& nipe);

    private:
        int number;
        char nipe;
};

#endif