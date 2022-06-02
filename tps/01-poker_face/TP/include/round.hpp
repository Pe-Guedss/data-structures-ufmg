//---------------------------------------------------------------------
// Arquivo	: round.hpp
// Conteudo	: definicoes da classe Round (Rodada).
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef ROUND_H
#define ROUND_H

#include "bets_queue.hpp"
#include "player.hpp"

/**
 * @brief Classe Rodada. Define os atributos e métodos relacionados a uma das rodadas do jogo.
 * 
 */
class Round {
    public:
        /**
         * @brief Constrói uma nova rodada.
         * 
         */
        Round();

        /**
         * @brief Constrói uma nova rodada com os dados lidos do arquivo.
         * 
         */
        Round(int playersAmount, int openingBet);

        /**
         * @brief Destrói a rodada atual.
         * 
         */
        ~Round();

        /**
         * @brief Adiciona um novo jogador ao array dinâmico.
         * 
         * @param pos Posição do array em que se deve inserir o jogador.
         * @param player Jogador que se irá inserir na partida
         */
        void addPlayer(int pos, Player *player);

        /**
         * @brief Adiciona uma nova aposta à fila
         * 
         * @param bet Aposta a ser feita
         */
        void pushBet(int bet);

        /**
         * @brief Cobra o pingo de todos os jogadores da partida.
         * 
         */
        void demandOpeningBet();

        /**
         * @brief Coleta as apostas de todos os jogadores da rodada.
         * 
         */
        void collectBets();

        /**
         * @brief Ordena o array de jogadores de forma decrescente, deixando os que possuem melhores combinações de cartas primeiro.
         * 
         */
        void sortEnrolledPlayers();

        /**
         * @brief Após o array de jogadores ordenado, seleciona os com melhores combinações e remove os de combinações inferiores do array.
         * 
         */
        void decideWinningPlayers();

        /**
         * @brief Decide, entre os jogadores restantes no array, qual o vencedor, de acordo com critérios de desempate.
         * 
         */
        void tieBreaker();

        /**
         * @brief Depois do desempate da rodada, divide o prêmio do pote de fichas para o(s) jogador(es) vencedor(es).
         * 
         */
        void transferPotCoinsToWinners();

    private:
        int openingBet; // Mínimo de aposta inicial que será feita neste Round.
        int playersAmount; // Quantidade de players disputando o round atual.
        int pot; // Pote de dinheiro do Round.
        bool isValidRound; // Atributo que guarda true (1) quando a rodada é válida e false (0) caso contrário.

        Deck *cardDeck; // Baralho de cartas do Round.

        BetsChainedQueue *betsQueue; // Fila de apostas dos jogadores do round.

        Player **enrolledPlayers; // Jogadores participando da rodada.

        int winningPlayersAmount; // Quantidade de jogadores vencendo.
        Player **winners;

        /**
         * @brief Desempata jogadores com straight Flush
         * 
         */
        void straightFlushTieBreaker();
        /**
         * @brief Desempata jogadores com quadras 
         * Obs: nesta implementação, é impossível haver jogadores com quadras iguais
         * 
         */
        void fourOfAKindTieBreaker();
        /**
         * @brief Desempata jogadores com full house
         * Obs: nesta implementação, é impossível haver jogadores com trios iguais
         * 
         */
        void fullHouseTieBreaker();
        /**
         * @brief Desempata jogadores com Flush
         * 
         */
        void flushTieBreaker();
        /**
         * @brief Desempata jogadores com Straight
         * 
         */
        void straightTieBreaker();
        /**
         * @brief Desempata jogadores com trios
         * Obs: nesta implementação, é impossível haver jogadores com trios iguais
         * 
         */
        void threeOfAKindTieBreaker();
        /**
         * @brief Desempata jogadores com dois pares.
         * 
         */
        void twoPairsTieBreaker();
        /**
         * @brief Desempata jogadores com um par.
         * 
         */
        void onePairTieBreaker();
        /**
         * @brief Desempata jogadores que não tenham nenhuma combinação.
         * 
         */
        void highestCardTieBreaker();

};

#endif