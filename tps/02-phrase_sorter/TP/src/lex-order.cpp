#include "lex-order.hpp"
#include <sstream>

LexOrder::LexOrder(std::string lexOrder) {
    std::string letter;
    int value = 0;

    std::stringstream auxLexOrder(lexOrder);
    while ( std::getline(auxLexOrder, letter, ' ') ) {
        this->setLetterValue(letter, value);
        value++;
    }
    
}

int LexOrder::getLetterValue(std::string letter) {

}

void LexOrder::setLetterValue(std::string letter, int value) {

}

bool LexOrder::isLessThan(std::string a, std::string b) {

}