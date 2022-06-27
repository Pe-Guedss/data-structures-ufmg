//---------------------------------------------------------------------
// Arquivo	: word_list.hpp
// Conteudo	: definicoes da classe WordList
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef WORDLIST_H
#define WORDLIST_H

#include "word.hpp"

class WordList {
    public:
        WordList();

        ~WordList();


        void push(std::string word);

        void insert(int pos, std::string word);

        Word *popFromStart();

        Word *getWord(int pos);

        void print();

        void clean();

    private:
        int size;
        Word *first;
        Word *last;
        Word *insertHelper(int pos, bool before);
};

#endif