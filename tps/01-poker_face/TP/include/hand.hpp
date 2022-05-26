//---------------------------------------------------------------------
// Arquivo	: deck.hpp
// Conteudo	: definicoes da classe Baralho
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef HAND_H
#define HAND_H

#include "deck.hpp"

class Hand {
    enum {
        HC,
        OP,
        TP,
        TK,
        S,
        F,
        FH,
        FK,
        SF,
        RSF
    };
        
    public:
        Hand();
        ~Hand();

        bool operator < (Hand const &hand) {
            return this->bestCombination < hand.bestCombination;
        }

        bool operator > (Hand const &hand) {
            return this->bestCombination > hand.bestCombination;
        }

        bool operator == (Hand const &hand) {
            return ( !(this->bestCombination > hand.bestCombination) && 
                     !(this->bestCombination < hand.bestCombination) );
        }

        void sortHand();
        void findBestCombination();
        std::string getBestCombinationCode();

    private:
        const int maxCards = 5;
        Card *cards[5];
        int bestCombination;
};

#endif