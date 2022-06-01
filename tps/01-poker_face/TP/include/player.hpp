//---------------------------------------------------------------------
// Arquivo	: player.hpp
// Conteudo	: definicoes da classe Jogador
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.hpp"

class Player {
    public:
        Player();
        ~Player();

    private:
        std::string name;
        int coins;
        Hand *hand;

};

#endif