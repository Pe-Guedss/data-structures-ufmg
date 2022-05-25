//---------------------------------------------------------------------
// Arquivo	: deck.hpp
// Conteudo	: definicoes da classe Baralho
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef DECK_H
#define DECK_H

#include "card.hpp"
#include <iostream>
#include <string>

/**
 * @brief Classe que armazena todas as cartas do baralho, removendo-as para as mãos dos jogadores a cada nova rodada e restringindo que cartas repetidas sejam distribuídas.
 * Há um baralho de 52 cartas em que as cartas estão organizadas de maneira crescente por número e naipes na seguinte sequência (O < E < C < P)
 * 
 */
class Deck {
    public:
        /**
         * @brief Construtor da classe deck, onde o baralho será inicializado com as cartas na ordem pré-definida.
         * 
         */
        Deck();
        /**
         * @brief Destrutor da classe deck, todas as cartas serão deletadas.
         * 
         */
        ~Deck();

        

    private:
        Card *cardDeck[52];
};

#endif