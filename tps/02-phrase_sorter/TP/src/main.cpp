#include "word.hpp"
#include <sstream>
#include <iostream>

int main() {
    LexOrder *lexOrder;

    Word *word[3];
    word[0] = new Word("Era"), word[1] = new Word("uma"), word[2] = new Word("umas");

    std::string aaa;
    std::getline(std::cin, aaa);
    lexOrder = new LexOrder(word[0]->toLower(aaa));

    Word *aux;
    for (int i = 0; i < 3; i++) {
        int minStr = i;
        for (int j = i + 1; j < 3; j++) {
            if ( word[j]->isLessThan(word[minStr], lexOrder) ) {
                minStr = j;
            }
        }
        aux = word[i];
        word[i] = word[minStr];
        word[minStr] = aux;
    }

    for (int i = 0; i < 3; i++) {
        std::cout << word[i] << std::endl;
        delete word[i];
        word[i] = nullptr;
    }
    
    return 0;
}