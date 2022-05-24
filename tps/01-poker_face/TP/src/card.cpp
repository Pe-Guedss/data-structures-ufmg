#include "card.hpp"


Card::Card() {
    this->nipe = "";
    this->number = -1;
}

Card::Card(const std::string &cardCode) {
    int it = 0;
    for (auto &&i : cardCode)
    {
        if (isalpha(i))
            break;
        it++;
    }

    std::string num = cardCode.substr(0, it);
    std::string nipe = cardCode.substr(it, cardCode.length() - 1);

    this->number = atoi(num.c_str());
    this->nipe = nipe;
}


std::ostream &operator<<(std::ostream &out, const Card *card)
{
    out << "===== Card Info =====" << std::endl;
    out << "Card Number: " << card->number << std::endl;
    out << "Card Nipe: " << card->nipe << std::endl;

    return out;
}

std::ostream &operator<<(std::ostream &out, const Card card)
{
    out << "===== Card Info =====" << std::endl;
    out << "Card Number: " << card.number << std::endl;
    out << "Card Nipe: " << card.nipe << std::endl;

    return out;
}