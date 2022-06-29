#include "phrase_sorter.hpp"

#include <fstream>
#include <sstream>

PhraseSorter::PhraseSorter(std::string inputFile, int median, int insertionSize) {
    std::ifstream inputPhrases(inputFile);

    std::string hashBlocksAux;
    std::getline(inputPhrases, hashBlocksAux);

    std::string newLexOrder;
    std::getline(inputPhrases, newLexOrder);
    this->lexOrder = new LexOrder( this->toLower(newLexOrder) );

    std::getline(inputPhrases, hashBlocksAux);

    this->wordList = new WordList();

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
    this->words = new Word*[wordList->size];

    for (int i = 0; i < this->size; i++) {
        this->words[i] = this->wordList->popFromStart();
    }

    inputPhrases.close();
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

    // this->selectionSort();
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

void PhraseSorter::selectionSort() {
    Word *aux;
    for (int i = 0; i < this->size; i++) {
        int minStr = i;
        for (int j = i + 1; j < this->size; j++) {
            if ( this->words[j]->isGreaterThan(this->words[minStr], this->lexOrder) ) {
                minStr = j;
            }
        }
        aux = this->words[i];
        this->words[i] = this->words[minStr];
        this->words[minStr] = aux;
    }
}

void PhraseSorter::qsPartition(int Esq, int Dir, int *i, int *j) {
    *i = Esq;
    *j = Dir;

    Word *x, *w;
    x = this->words[(*i + *j)/2];
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
