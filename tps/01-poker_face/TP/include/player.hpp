//---------------------------------------------------------------------
// Arquivo	: player.hpp
// Conteudo	: definicoes da classe Jogador
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.hpp"

/**
 * @brief Classe Jogador. Guarda os atributos relacionados a ele, além de realizar operações como aposta.
 * 
 */
class Player {
    public:
        /**
         * @brief Construtor padrão de um novo jogador.
         * 
         */
        Player();
        /**
         * @brief Construtor do jogador inicializando o nome do mesmo e o total de fichas iniciais que ele possui.
         * 
         * @param name Nome atribuído ao jogador.
         * @param coins Total de fichas que o jogador possui inicialmente.
         */
        Player(std::string name, int coins);
        /**
         * @brief Destrutor padrão do jogador. Desaloca a mão e a torna um ponteiro nulo.
         * 
         */
        ~Player();

        /**
         * @brief Retorna o nome do jogador.
         * 
         * @return std::string this->name.
         */
        std::string getName();

        /**
         * @brief Retorna a quantidade de fichas do jogador.
         * 
         * @return int this->coins.
         */
        int getCoins();

        /**
         * @brief Realiza o teste de sanidade do jogador, ou seja, se ele pode ou não realizar a aposta.
         * 
         * @param coinAmount Quantidade de fichas a serem apostadas na rodada (incluindo o pingo).
         * 
         * @return true (1) ou false (0), dependendo se a aposta pode ou não ser realizada.
         * 
         */
        bool sanityTest(int coinAmount);

        /**
         * @brief Realiza a aposta do jogador.
         * 
         * @param bet Quantidade de fichas investidas na aposta.
         */
        void makeBet(int bet);

        // TODO:
        // - Declarar métodos de comparação dos usuários. Verificar se a mão de um é maior que a do outro, igual, menor, etc...
        // - Declarar método de impressão do usuário para debug. (Nome - fichas - Mão)

    private:
        std::string name; // Nome do jogador.
        int coins; // Total de moedas do jogador.
        Hand *hand; // Mão atual do jogador.

};

#endif