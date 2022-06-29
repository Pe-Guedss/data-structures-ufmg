//---------------------------------------------------------------------
// Arquivo	: phrase_sorter.hpp
// Conteudo	: definicoes da classe PhraseSorter
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef PHRASESORTER_H
#define PHRASESORTER_H

#include "word_list.hpp"

class PhraseSorter {
    public:
        PhraseSorter(std::string inputFile, int median, int insertionSize);

        ~PhraseSorter();

        void print(std::string outputFile);

    private:
        LexOrder *lexOrder;

        WordList *wordList;
        Word **words;

        int size;
        int median;
        int insertionSize;
};

#endif