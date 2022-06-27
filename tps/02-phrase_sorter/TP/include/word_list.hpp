//---------------------------------------------------------------------
// Arquivo	: word_list.hpp
// Conteudo	: definicoes da classe WordList
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef WORDLIST_H
#define WORDLIST_H

#include "word.hpp"

/**
 * @brief Classe WordList. Define uma lista encadeada das palavras lidas no texto.
 * 
 */
class WordList {
    public:
        /**
         * @brief Construtor da classe WordList.
         * 
         */
        WordList();

        /**
         * @brief Destrutor da classe WordList.
         * 
         */
        ~WordList();


        /**
         * @brief Adiciona uma nova palavra ao fim da lista.
         * 
         * @param word Palavra que se quer adicionar.
         */
        void push(std::string word);

        /**
         * @brief Insere uma palavra em uma posição específica da lista.
         * 
         * @param pos Posição que se quer inserir a palavra na lista.
         * @param word Palavra que se quer inserir na lista.
         */
        void insert(int pos, std::string word);

        /**
         * @brief Remove a primeira palavra da lista.
         * 
         * @return Word* Ponteiro para a palavra removida.
         */
        Word *popFromStart();

        /**
         * @brief Remove a palavra armazenada na posição informada.
         * 
         * @param pos Posição que se quer remover a palavra.
         * @return Word* Ponteiro para a palavra removida.
         */
        Word *removeFromPos(int pos);

        /**
         * @brief Imprime a lista de palavras.
         * 
         */
        void print();

        /**
         * @brief Limpa a lista de palavras.
         * 
         */
        void clean();

    private:
        int size; // Tamanho da lista de palavras.
        Word *first; // Primeira palavra da lista.
        Word *last; // Última palavra da lista.

        /**
         * @brief Método de auxílio à inserção de palavras em posições específicas da lista.
         * 
         * @param pos Posição em que se quer inserir a palavra.
         * @param before True(1) se for para inserir antes, ou false(0) caso contrário.
         * @return Word* 
         */
        Word *insertHelper(int pos, bool before);
};

#endif