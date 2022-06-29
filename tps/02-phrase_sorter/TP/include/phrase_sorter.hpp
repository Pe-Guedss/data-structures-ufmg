//---------------------------------------------------------------------
// Arquivo	: phrase_sorter.hpp
// Conteudo	: definicoes da classe PhraseSorter
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef PHRASESORTER_H
#define PHRASESORTER_H

#include "word_list.hpp"

/**
 * @brief Classe PhraseSorter. Define os atributos e métodos necessários para a ordenação das frases.
 * 
 */
class PhraseSorter {
    public:
        /**
         * @brief Constrói uma nova instância de PhraseSorter.
         * 
         * @param inputFile Caminho para o arquivo com as entradas do programa.
         * @param median Quantidade de números utilizados na heurística de mediana do Quick Sort.
         * @param insertionSize Tamanho do sub-array que será ordenado por inserção como otimização do Quick Sort.
         */
        PhraseSorter(std::string inputFile, int median, int insertionSize);

        /**
         * @brief Destrutor padrão do objeto PhraseSorter.
         * 
         */
        ~PhraseSorter();

        /**
         * @brief Método para imprimir as palavras já ordenadas.
         * 
         * @param outputFile Caminho para o arquivo em que os resultados serão impressos.
         */
        void print(std::string outputFile);

    private:
        LexOrder *lexOrder; // Objeto com a ordem lexicográfica vigente para o arquivo.

        WordList *wordList; // Lista encadeada inicial das palavras lidas.
        Word **words; // Array dinâmico de palavras para ser ordenado.

        std::string medianWord; // Palavra que deve ser considerada como a mediana para a heurística do Quick Sort.
        Word **medianArr; // Array com a quantidade this->median de elementos para que o cálculo seja feito.

        int size; // Tamanho do array de palavras.
        int insertionSize; // Tamanho do subarray que será ordenado por inserção como otimização do Quick Sort.
};

#endif