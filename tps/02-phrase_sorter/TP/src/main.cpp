#include "lex_order.hpp"
#include <sstream>
#include <iostream>

std::string toLower(std::string str) {
    const uint diff = 'a' - 'A';

    std::string lower;
    lower.reserve(str.length());

    for (int i = 0; i < str.size(); i++) {
        lower += (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + diff : str[i];
    }

    return lower;
}

int main() {
    std::string aaa;
    LexOrder *lexOrder;

    std::getline(std::cin, aaa);
    aaa = toLower(aaa);
    lexOrder = new LexOrder(aaa);

    std::string test[3];
    test[0] = "Era", test[1] = "uma", test[2] = "vez";
    for (int i = 0; i < 3; i++) {
        std::string aux = "";
        int minStr = i;
        for (int j = i; j < 3; j++) {
            if ( lexOrder->isLessThan(test[j], test[i]) ) {
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