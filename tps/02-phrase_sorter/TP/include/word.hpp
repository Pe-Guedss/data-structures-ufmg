//---------------------------------------------------------------------
// Arquivo	: word.hpp
// Conteudo	: definicoes da classe Word
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef WORD_H
#define WORD_H

#include "lex_order.hpp"

class Word {
    public:
        Word(std::string word);

        void matches(std::string newWord);

        bool isLessThan(Word *word, LexOrder *lexOrder);

    private:
        std::string word;
        int occurrences;
};

#endif