#include "word.hpp"

Word::Word(std::string word) {
    this->word = this->toLower(word);
    this->occurrences = 1;
}

bool Word::matches(std::string newWord) {
    if (this->word == newWord) {
        this->occurrences++;
        return true;
    }
    
    return false;
}

std::string Word::toLower(std::string str) {
    const uint diff = 'a' - 'A';

    std::string lower;
    lower.reserve(str.length());

    for (long unsigned int i = 0; i < str.size(); i++) {
        lower += (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + diff : str[i];
    }

    return lower;
}

int Word::getSize() {
    return this->size;
}

bool Word::isLessThan(Word *word, LexOrder *lexOrder) {
    int smallerWordSize = (this->getSize() < word->getSize() ? this->getSize() : word->getSize());
    for ( int i = 0; i < smallerWordSize; i++) {
        if ( lexOrder->getLetterValue(this->word[i]) < lexOrder->getLetterValue(word->word[i]) ) {
            return true;
        }
        else if (this->word[i] == word->word[i]) {
            continue;
        }
        return false;
    }

    return (smallerWordSize == this->size ? true : false);
}