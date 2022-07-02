#include "phrase_sorter.hpp"
#include <sstream>

int main() {
    int medianSize = 4, insertionSize = 10;
    PhraseSorter *phraseSorter;
    phraseSorter = new PhraseSorter("in.txt", medianSize, insertionSize);

    phraseSorter->print("out.txt");

    delete phraseSorter;
    phraseSorter = nullptr;
    return 0;
}