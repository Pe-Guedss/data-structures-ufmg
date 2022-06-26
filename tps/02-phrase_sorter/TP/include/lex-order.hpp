//---------------------------------------------------------------------
// Arquivo	: lex-order.hpp
// Conteudo	: definicoes da classe LexOrder
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef LEXORDER_H
#define LEXORDER_H

#include <iostream>
#include <string>

class LexOrder {
    public:
        LexOrder(std::string lexOrder);

        int getLetterValue(std::string letter);

        bool isLessThan(std::string a, std::string b);

    private:
        int a = -1, b = -1, c = -1, d = -1, e = -1,\
            f = -1, g = -1, h = -1, i = -1, j = -1, \
            k = -1, l = -1, m = -1, n = -1, o = -1,\
            p = -1, q = -1, r = -1, s = -1, t = -1, \
            u = -1, v = -1, w = -1, x = -1, y = -1, z = -1;
};

#endif