#include "word_list.hpp"
#include <sstream>

int main() {
    WordList *wordList;
    wordList = new WordList();
    wordList->push("Era");
    wordList->push("umas");
    wordList->push("umas");
    wordList->push("uma");
    wordList->push("uma");
    wordList->push("era");
    wordList->push("Uma");

    LexOrder *lexOrder;
    std::string aaa;
    std::getline(std::cin, aaa);
    lexOrder = new LexOrder(wordList->toLower(aaa));

    // Word *aux;
    // for (int i = 0; i < 3; i++) {
    //     int minStr = i;
    //     for (int j = i + 1; j < 3; j++) {
    //         if ( word[j]->isLessThan(word[minStr], lexOrder) ) {
    //             minStr = j;
    //         }
    //     }
    //     aux = word[i];
    //     word[i] = word[minStr];
    //     word[minStr] = aux;
    // }

    wordList->print();
    
    return 0;
}