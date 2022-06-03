#include <iostream>

int main() {
    int **original;
    original = new int*[5];
    for (int i = 0; i < 5; i++) {
        original[i] = new int(i);
    }
    std::cout << "Array original antes:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << *original[i] << std::endl;
    }
    

    int **copy;
    copy = new int*[2];
    copy[0] = original[1];
    copy[1] = original[3];
    *original[1] = 150;
    std::cout << "Array copy antes:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << *copy[i] << std::endl;
    }

    int **copyOfCopy;
    copyOfCopy = copy;

    delete []copy;
    copy = nullptr;

    std::cout << "Array copyOfCopy depois:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << *copyOfCopy[i] << std::endl;
    }

    std::cout << "Array copy depois:" << std::endl;
    std::cout << copy << std::endl;

    delete []original;
    original = nullptr;
    return 0;
}