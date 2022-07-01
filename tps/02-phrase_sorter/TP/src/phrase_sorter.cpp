#include "phrase_sorter.hpp"

#include <fstream>
#include <sstream>

PhraseSorter::PhraseSorter(std::string inputFile, int medianSize, int insertionSize) {
    std::ifstream inputPhrases(inputFile); // Abre o arquivo de texto com as entradas.

    this->medianSize = medianSize; 
    this->insertionSize = insertionSize;

    std::string hashBlocksAux; // Variável para coletar blocos de #TEXTO e #ORDEM
    std::getline(inputPhrases, hashBlocksAux); // Coleta o bloco de #ORDEM

    std::string newLexOrder; // Variável para conter a nova ordem lexicográfica.
    std::getline(inputPhrases, newLexOrder);
    this->lexOrder = new LexOrder( this->toLower(newLexOrder) );

    std::getline(inputPhrases, hashBlocksAux); // Coleta o bloco de #TEXTO

    this->wordList = new WordList();

    // Leitura das frases abaixo do bloco #TEXTO e inserção na lista.
    std::string auxLine, word;
    while( std::getline(inputPhrases, auxLine) ) {
        std::stringstream line(auxLine);
        while ( std::getline(line, word, ' ') ) {
            word = this->toLower(word);
            if (word[word.length() - 1] == ',' ||
                word[word.length() - 1] == '.' ||
                word[word.length() - 1] == '!' ||
                word[word.length() - 1] == '?' ||
                word[word.length() - 1] == ':' ||
                word[word.length() - 1] == ';' ||
                word[word.length() - 1] == '_')
            {
                word.erase(word.length() - 1);
            }

            this->wordList->push(word);
        }
    }

    this->size = this->wordList->size;
    this->words = new Word*[this->wordList->size];

    // Inserção dos elementos da lista no array.
    for (int i = 0; i < this->size; i++) {
        this->words[i] = this->wordList->popFromStart();
    }

    inputPhrases.close(); // Fechamento do arquivo.
}

PhraseSorter::~PhraseSorter() {
    for (int i = 0; i < this->size; i++) {
        delete this->words[i];
        this->words[i] = nullptr;
    }

    delete []this->words;
    this->words = nullptr;
}

void PhraseSorter::print(std::string outputFile) {
    std::ofstream sortingResults(outputFile);

    // this->insertionSort(0, this->size);
    this->quickSort();
    for (int i = 0; i < this->size; i++) {
        sortingResults << this->words[i];
    }
    
    sortingResults << "#FIM" << std::endl;
}

std::string PhraseSorter::toLower(std::string str) {
    const uint diff = 'a' - 'A';

    std::string lower;
    lower.reserve(str.length());

    for (long unsigned int i = 0; i < str.size(); i++) {
        lower += (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + diff : str[i];
    }

    return lower;
}

void PhraseSorter::insertionSort(int esq, int dir) {
    Word *aux;
    for (int i = esq + 1; i < dir; i++) {
        aux = this->words[i];
        int j = i - 1;
        while (( j >= 0 ) &&
               ( aux->isLessThan(this->words[j], this->lexOrder) )) {
            this->words[j + 1] = this->words[j];
            j--;
        }
        this->words[j + 1] = aux;
    }
}

void PhraseSorter::qsPartition(int Esq, int Dir, int *i, int *j) {
    *i = Esq;
    *j = Dir;

    // Definição do pivô
    Word *x;
    if (*j - *i > this->medianSize) {
        this->insertionSort(Esq, this->medianSize);
        x = this->words[(*i + this->medianSize) / 2];
    }
    else {
        this->insertionSort(Esq, Dir);
        x = this->words[(*i + *j) / 2];
    }

    // Particionamento do array
    Word *w;
    do {
        while ( x->isGreaterThan(this->words[*i], this->lexOrder) ) (*i)++; 
        while ( x->isLessThan(this->words[*j], this->lexOrder) ) (*j)--;
        if (*i <= *j) {
            w = this->words[*i];
            this->words[*i] = this->words[*j];
            this->words[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void PhraseSorter::sort(int Esq, int Dir) {
    int i, j;

    this->qsPartition(Esq, Dir, &i, &j);

    if (Esq < j)
        this->sort(Esq, j);
    if (i < Dir)
        this->sort(i, Dir);
}

void PhraseSorter::quickSort() {
    this->sort(0, this->size - 1);
}
