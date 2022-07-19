//---------------------------------------------------------------------
// Arquivo	: operations.hpp
// Conteudo	: Definições da classe OperationsQueue, que enfileira as operações realizadas no servidor.
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef OPERATIONS_QUEUE_H
#define OPERATIONS_QUEUE_H

#include <string>

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
 * @brief Classe para armazenar uma operação realizada no servidor.
 * 
 */
class Operation {
    public:
        /**
         * @brief Construtor padrão da classe Operation.
         * 
         */
        Operation();

    private:
        std::string operation; // Operação realizada.
        Operation *next; // Referência à próxima operação da fila.

    friend class OperationsQueue;
};

/**
 * @brief Classe Fila OperationsQueue. Herda as propriedades da classe pai "Queue".
 * 
 */
class OperationsQueue : public Queue {
    public:
        /**
         * @brief Construtor padrão da classe OperationsQueue.
         * 
         */
        OperationsQueue();

        /**
         * @brief Destrutor padrão da classe OperationsQueue.
         * 
         */
        virtual ~OperationsQueue();

        /**
         * @brief Método para enfileirar uma nova Operação.
         * 
         * @param operation Operação que se quer enfileirar.
         */
        void enqueue(std::string operation);

        /**
         * @brief Método para desenfileirar a primeira operação da fila.
         * 
         * @return std::string -> Operação desenfileirada.
         */
        std::string dequeue();

        /**
         * @brief Limpador padrão da fila.
         * 
         */
        void clear();

    private:
        Operation* front; // Primeiro elemento da fila.
        Operation* back; // Último elemento da fila.
};

#endif