//---------------------------------------------------------------------
// Arquivo	: queue.hpp
// Conteudo	: definicoes das classes de fila utilizadas.
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef ROUND_QUEUE_H
#define ROUND_QUEUE_H

#include "round.hpp"

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
 * @brief Classe para armazenar um item do tipo Rodada na fila.
 * 
 */
class QueuedRound {
    public:
        /**
         * @brief Construtor padrão da classe Rodada Enfileirada.
         * 
         */
        QueuedRound();

    private:
        Round *round; // Rodada enfileirada nesta célula.
        QueuedRound *next; // Referência à próxima rodada da fila.

    friend class RoundsChainedQueue;
};

/**
 * @brief Classe Fila Encadeada de Rodadas. Herda as propriedades da classe pai Fila.
 * 
 */
class RoundsChainedQueue : public Queue {
    public:
        /**
         * @brief Construtor padrão da classe Fila Encadeada de Rodadas.
         * 
         */
        RoundsChainedQueue();

        /**
         * @brief Destrutor padrão da classe Fila Encadeada de Rodadas.
         * 
         */
        virtual ~RoundsChainedQueue();

        /**
         * @brief Método para enfileirar uma nova Rodada.
         * 
         * @param round Ponteiro para a rodada que se quer enfileirar.
         */
        void enqueue(Round *round);

        /**
         * @brief Método para desenfileirar a primeira rodada da fila.
         * 
         * @return Round* Rodada desenfileirada.
         */
        Round* dequeue();

        /**
         * @brief Limpador padrão da fila.
         * 
         */
        void clear();

    private:
        QueuedRound* front; // Primeiro elemento da fila.
        QueuedRound* back; // Último elemento da fila.
};

#endif