#include <regex>
#include "match.hpp"

int main() {
    Match *match;
    match = new Match("entrada.txt");

    match->play("saida.txt");

    return 0;
}