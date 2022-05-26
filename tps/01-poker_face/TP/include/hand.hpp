//---------------------------------------------------------------------
// Arquivo	: deck.hpp
// Conteudo	: definicoes da classe Baralho
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef HAND_H
#define HAND_H

#include "deck.hpp"

/**
 * @brief Classe para armazenar as cartas na mão do jogador.
 * 
 */
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
        /**
         * @brief Construtor da mão de cartas do jogador.
         * 
         */
        Hand();
        /**
         * @brief Destrutor da mão de cartas do jogador
         * 
         */
        ~Hand();

        bool operator < (Hand const &hand) {
            return this->bestCombination < hand.bestCombination;
        }

        bool operator > (Hand const &hand) {
            return this->bestCombination > hand.bestCombination;
        }

        /**
         * @brief Operador de comparação de igualdade entre mãos de cartas dos jogadores.
         * Se uma mão foi declarada como ponteiro (Hand *h;), lembre-se de desreferenciá-la (*h == *g).
         * 
         * @param card 
         * @return true (1) ou false (0) dependendo da igualdade
         */
        bool operator == (Hand const &hand) {
            return ( !(this->bestCombination > hand.bestCombination) && 
                     !(this->bestCombination < hand.bestCombination) );
        }

        /**
         * @brief Ordena a mão de cartas do jogador, deixando a menor carta na primeira posição do array e a maior na última.
         * 
         */
        void sortHand();
        /**
         * @brief Encontra a melhor combinação de cartas presente na mão do usuário.
         * 
         */
        void findBestCombination();
        /**
         * @brief Depois de definida a melhor combinação de cartas na mão do jogador, mapeia a enumeração para os respectivos códigos em string, retornando o código encontrado.
         * 
         * @return String contendo o código da melhor combinação presente na mão.
         */
        std::string getBestCombinationCode();
        /**
         * @brief Adiciona uma nova carta à mão do jogador.
         * 
         * @param cardCode Código da carta (Ex.: "13E")
         */
        void addCard(std::string cardCode);

    private:
        const int maxCards = 5;
        Card *cards[5];
        int bestCombination;
};

#endif