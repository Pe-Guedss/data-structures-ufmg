//---------------------------------------------------------------------
// Arquivo	: match.hpp
// Conteudo	: definicoes da classe Match (Partida).
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef MATCH_H
#define MATCH_H

#include "round_queue.hpp"

class Match {
    public:
        Match();
        Match(std::string matchDataPath);
        ~Match();
        void sortPlayersByCoins();
        void chargeOpeningBet(int openingBet);
        Player *findPlayer(std::string playerName);
        void printMatchResults();
        void play(std::string matchResultsPath);

    private:
        int initialPlayerCoins;

        int playersAmount;
        Player **players;

        RoundsChainedQueue *rounds;
        
};

#endif