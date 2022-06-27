#include "lex_order.hpp"
#include <sstream>

LexOrder::LexOrder(std::string lexOrder) {
    std::string letter;
    int value = 0;

    lexOrder = this->toLower(lexOrder);
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

int LexOrder::getLetterValue(int letter) {
    if (letter == 'a') return this->a;
    else if (letter == 'b') return this->b;
    else if (letter == 'c') return this->c;
    else if (letter == 'd') return this->d;
    else if (letter == 'e') return this->e;
    else if (letter == 'f') return this->f;
    else if (letter == 'g') return this->g;
    else if (letter == 'h') return this->h;
    else if (letter == 'i') return this->i;
    else if (letter == 'j') return this->j;
    else if (letter == 'k') return this->k;
    else if (letter == 'l') return this->l;
    else if (letter == 'm') return this->m;
    else if (letter == 'n') return this->n;
    else if (letter == 'o') return this->o;
    else if (letter == 'p') return this->p;
    else if (letter == 'q') return this->q;
    else if (letter == 'r') return this->r;
    else if (letter == 's') return this->s;
    else if (letter == 't') return this->t;
    else if (letter == 'u') return this->u;
    else if (letter == 'v') return this->v;
    else if (letter == 'w') return this->w;
    else if (letter == 'x') return this->x;
    else if (letter == 'y') return this->y;
    else if (letter == 'z') return this->z;
    else return letter;
}

bool LexOrder::isLessThan(std::string a, std::string b) {
    a = this->toLower(a);
    b = this->toLower(b);
    long unsigned int size = (a.length() < b.length() ? a.length() : b.length());
    for (long unsigned int i = 0; i < size; i++) {
        if ( this->getLetterValue(a[i]) < this->getLetterValue(b[i]) ) {
            return true;
        }
        else if (a[i] == b[i]) {
            continue;
        }
        return false;
    }

    return (size == a.length() ? true : false);
}