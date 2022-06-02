//---------------------------------------------------------------------
// Arquivo	: queue.hpp
// Conteudo	: definicoes das classes de fila utilizadas.
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef PLAYERS_QUEUE_H
#define PLAYERS_QUEUE_H

#include "player.hpp"

/**
 * @brief Classe Fila. É pai de todas as outras filas, declarando métodos comuns.
 * 
 */
class Queue {
    public:
        /**
         * @brief Construtor padrão da fila pai. Apenas inicia o tamanho como 0.
         * 
         */
        Queue() {
            size = 0;
        };

        /**
         * @brief Retorna o tamanho atual da fila.
         * 
         * @return int this->size.
         */
        int getSize() {
            return size;
        };

        /**
         * @brief Verifica se a fila está vazia.
         * 
         * @return true (1) ou false (0), dependendo se a fila está vazia ou não.
         */
        bool isEmpty() {
            return size == 0;
        };

    protected:
        int size; // Atributo para registrar o tamanho da fila.
};

/**
 * @brief Classe para armazenar um item do tipo Aposta na fila.
 * 
 */
class QueuedPlayer {
    public:
        /**
         * @brief Construtor padrão da classe Aposta.
         * 
         */
        QueuedPlayer();

    private:
        Player *player; // Valor da aposta que se vai empilhar.
        QueuedPlayer *next; // Referência à próxima aposta da fila.

    friend class PlayersChainedQueue;
};

/**
 * @brief Classe Fila Encadeada de Apostas. Herda as propriedades da classe pai Fila.
 * 
 */
class PlayersChainedQueue : public Queue {
    public:
        /**
         * @brief Construtor padrão da classe Fila Encadeada de Apostas.
         * 
         */
        PlayersChainedQueue();

        /**
         * @brief Destrutor padrão da classe Fila Encadeada de Apostas.
         * 
         */
        virtual ~PlayersChainedQueue();

        /**
         * @brief Método para enfileirar uma nova aposta.
         * 
         * @param bet Valor da aposta que se quer enfileirar.
         */
        void enqueue(Player *player);

        /**
         * @brief Método para desenfileirar a primeira aposta da fila.
         * 
         * @return int Valor da aposta desenfileirada.
         */
        Player* dequeue();

        /**
         * @brief Limpador padrão da fila.
         * 
         */
        void clear();

    private:
        QueuedPlayer* front; // Primeiro elemento da fila.
        QueuedPlayer* back; // Último elemento da fila.
};

#endif