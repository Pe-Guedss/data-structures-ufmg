#include "phrase_sorter.hpp"
#include <sstream>

int main() {
    PhraseSorter *phraseSorter;
    phraseSorter = new PhraseSorter("in.txt", 3, 10);

    phraseSorter->print("out.txt");

    delete phraseSorter;
    phraseSorter = nullptr;
    return 0;
}