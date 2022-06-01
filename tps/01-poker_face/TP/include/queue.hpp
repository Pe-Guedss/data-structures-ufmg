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
        Bet *next;

    friend class BetsChainedQueue;
};

class BetsChainedQueue : public Queue {
    public:
        BetsChainedQueue();

        virtual ~BetsChainedQueue();

        void enqueue(int bet);

        int dequeue();

        void clear();

    private:
        Bet* front;
        Bet* back;
};

#endif