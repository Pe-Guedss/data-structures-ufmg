#include "word.hpp"

Word::Word(std::string word) {
    this->word = word;
    this->occurrences = 1;
}

bool Word::matches(std::string newWord) {
    return this->word == newWord;
}
