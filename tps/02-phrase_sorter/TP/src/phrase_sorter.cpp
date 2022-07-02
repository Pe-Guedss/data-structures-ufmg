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
            word = this->toLower(word); // Transformação para casa baixa.
            int pos = word.length() - 1;
            while (word[word.length() - 1] == ',' ||
                word[word.length() - 1] == '.' ||
                word[word.length() - 1] == '!' ||
                word[word.length() - 1] == '?' ||
                word[word.length() - 1] == ':' ||
                word[word.length() - 1] == ';' ||
                word[word.length() - 1] == '_')
            {
                word.erase(pos);
                pos--;
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
        sortingResults << this->words[i] << std::endl;
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

void printArr(Word **arr, int n) {
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    
}

void PhraseSorter::qsPartition(int esq, int dir, int *i, int *j) {
    // std::cout << "----------------------------" << std::endl;
    // printArr(this->words, this->size);
    *i = esq;
    *j = dir;

    if (dir - esq <= this->insertionSize) this->insertionSort(esq, dir);

    // std::cout << "----------------------------" << std::endl;
    // std::cout << "Array antes do pivo: " << std::endl;
    // printArr(this->words, this->size);
    // Definição do pivô
    Word *x;
    if (this->medianSize < *j - *i) {
        this->insertionSort(*i, *i + this->medianSize);
        x = this->words[(*i + *i + this->medianSize) / 2];
    }
    else {
        x = this->words[(*i + *j) / 2];
    }
    // std::cout << "_________________________________" << std::endl;
    // std::cout << "Array depois do pivo: " << std::endl;
    // printArr(this->words, this->size);
    // std::cout << "Pivo escolhido: " << x << std::endl;
    // std::cout << "----------------------------" << std::endl;

    // Particionamento do array
    Word *w;
    // printArr(this->words, this->size);
    do {
        // std::cout << "I: " << *i << "\tEsq: " << esq << std::endl;
        // std::cout << "J: " << *j << "\tDir: " << dir << std::endl;
        while ( x->isGreaterThan(this->words[*i], this->lexOrder) ) (*i)++; 
        while ( x->isLessThan(this->words[*j], this->lexOrder) ) (*j)--;
        if (*i <= *j) {
            w = this->words[*i];
            this->words[*i] = this->words[*j];
            this->words[*j] = w;
            (*i)++;
            (*j)--;
        }
        // printArr(this->words, this->size);
    } while (*i <= *j);
    // std::cout << "----------------------------" << std::endl;
}

void PhraseSorter::sort(int esq, int dir) {
    int i, j;

    this->qsPartition(esq, dir, &i, &j);

    // std::cout << "I: " << i << "\tEsq: " << esq << std::endl;
    // std::cout << "J: " << j << "\tDir: " << dir << std::endl;

    // std::cout << "Ordenando da esquerda a j..." << std::endl;
    if (esq < j)
        this->sort(esq, j);
    // std::cout << "Ordenando de i à direita..." << std::endl;
    if (i < dir)
        this->sort(i, dir);

}

void PhraseSorter::quickSort() {
    this->sort(0, this->size - 1);
}
