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

    private:
        std::string name; // Nome do jogador.
        int coins; // Total de moedas do jogador.
        Hand *hand; // Mão atual do jogador.

};

#endif