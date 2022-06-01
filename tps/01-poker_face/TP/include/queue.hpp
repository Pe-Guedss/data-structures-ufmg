#ifndef QUEUE_H
#define QUEUE_H

class Queue {
    public:
        Queue() {
            size = 0;
        };

        int getSize() {
            return size;
        };

        bool isEmpty() {
            return size == 0;
        };

    protected:
        int size;
};

class Bet {
    public:
        Bet();

    private:
        int bet;
        Bet *prox;

    friend class BetsChainedQueue;
};

class BetsChainedQueue : public Queue {
    public:
        BetsChainedQueue();

        virtual ~BetsChainedQueue();

        void Enqueue(int bet);

        int Dequeue();

        void Limpa();

    private:
        Bet* frente;
        Bet* tras;
};

#endif