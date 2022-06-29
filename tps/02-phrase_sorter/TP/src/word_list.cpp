#include "word_list.hpp"

WordList::WordList() {
    this->first = new Word();
    this->last = this->first;
    this->size = 0;
}

Word* WordList::insertHelper(int pos, bool before) {
    Word *w;
    if ( (pos > this->size + 1) || (pos <= 0) ) throw "ERRO: Posicao Invalida!";

    w = this->first;
    for(int i = 1; i < pos; i++) {
        w = w->next;
    }

    if(!before) w = w->next;

    return w;
}

void WordList::push(std::string word) {
    Word *aux;
    aux = this->first;
    for (int i = 0; i < this->size; i++) {
        aux = aux->next;
        if ( aux->matches(word) ) return;        
    }
    
    Word *newWord;
    newWord = new Word(word);

    this->last->next = newWord;
    this->last = newWord;

    this->size++;
}

void WordList::insert(int pos, std::string word) {
    Word *aux;
    aux = this->insertHelper(pos, true);

    Word *newWord;
    newWord = new Word(word);

    newWord->next = aux->next;
    aux->next = newWord;
    if(newWord->next == nullptr) this->last = newWord;

    this->size++;
}

Word* WordList::popFromStart() {
    if (this->size == 0) throw "ERRO: Lista vazia!";

    Word *w;
    w = this->first->next;

    this->first->next = w->next;
    if(this->first->next == nullptr) this->last = this->first;

    this->size--;
    return w;
}

Word* WordList::removeFromPos(int pos) {
    if (this->size == 0) throw "ERRO: Lista vazia!";

    Word *wordBefore;
    wordBefore = this->insertHelper(pos, true);

    Word *word;
    word = wordBefore->next;

    wordBefore->next = word->next;
    if(wordBefore->next == nullptr) this->last = wordBefore;

    this->size--;
    return word;
}

void WordList::print() {
    Word *aux;
    aux = this->first->next;
    while (aux != nullptr) {
        std::cout << aux << std::endl;
        aux = aux->next;
    }
    std::cout << std::endl;
}

void WordList::clean() {
    Word *aux;
    aux = this->first->next;
    while (aux != nullptr) {
        this->first->next = aux->next;
        delete aux;
        aux = this->first->next;
    }
    this->last = this->first;
    this->size = 0;
}
