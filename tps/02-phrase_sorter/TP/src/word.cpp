#include "word.hpp"

Word::Word(std::string word) {
    this->word = word;
    this->occurrences = 1;
}

bool Word::matches(std::string newWord) {
    return this->word == newWord;
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