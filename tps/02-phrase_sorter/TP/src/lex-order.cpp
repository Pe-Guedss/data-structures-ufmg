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

void LexOrder::setLetterValue(std::string letter, int value) {
    if (letter == "a") this->a = value;
    else if (letter == "b") this->b = value;
    else if (letter == "c") this->c = value;
    else if (letter == "d") this->d = value;
    else if (letter == "e") this->e = value;
    else if (letter == "f") this->f = value;
    else if (letter == "g") this->g = value;
    else if (letter == "h") this->h = value;
    else if (letter == "i") this->i = value;
    else if (letter == "j") this->j = value;
    else if (letter == "k") this->k = value;
    else if (letter == "l") this->l = value;
    else if (letter == "m") this->m = value;
    else if (letter == "n") this->n = value;
    else if (letter == "o") this->o = value;
    else if (letter == "p") this->p = value;
    else if (letter == "q") this->q = value;
    else if (letter == "r") this->r = value;
    else if (letter == "s") this->s = value;
    else if (letter == "t") this->t = value;
    else if (letter == "u") this->u = value;
    else if (letter == "v") this->v = value;
    else if (letter == "w") this->w = value;
    else if (letter == "x") this->x = value;
    else if (letter == "y") this->y = value;
    else if (letter == "z") this->z = value;
}

int LexOrder::getLetterValue(std::string letter) {

}

bool LexOrder::isLessThan(std::string a, std::string b) {

}