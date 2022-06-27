#include "lex_order.hpp"
#include <sstream>
#include <iostream>

int main() {
    std::string aaa;
    LexOrder *lexOrder;

    std::getline(std::cin, aaa);
    lexOrder = new LexOrder(aaa);

    std::string test[3];
    test[0] = "Era", test[1] = "uma", test[2] = "umas";
    for (int i = 0; i < 3; i++) {
        std::string aux = "";
        int minStr = i;
        for (int j = i; j < 3; j++) {
            if ( lexOrder->isLessThan(test[j], test[minStr]) ) {
                minStr = j;
            }
        }
        aux = test[i];
        test[i] = test[minStr];
        test[minStr] = aux;
    }
    
    std::cout << test[0] << std::endl;
    std::cout << test[1] << std::endl;
    std::cout << test[2] << std::endl;

    return 0;
}