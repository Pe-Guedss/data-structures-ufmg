//---------------------------------------------------------------------
// Arquivo	: deck.hpp
// Conteudo	: definicoes da classe Baralho
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef HAND_H
#define HAND_H

#include "deck.hpp"

class Hand {
    public:
        Hand();
        ~Hand();

    private:
        const int maxCards = 5;
        Card *cards[5];
        std::string bestCombination;
};

#endif