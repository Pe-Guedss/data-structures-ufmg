//---------------------------------------------------------------------
// Arquivo	: card.h
// Conteudo	: definicoes da classe Carta
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

/**
 * @brief Classe que armazena e gerencia as informacoes das cartas do baralho, enquanto objetos individuais.
 *
 */
class Card
{
public:
    /**
     * @brief Construtor padrão que inicializa todas as variaveis privadas da classe.
     */
    Card();
    /**
     * @brief Construtor que inicia os valores da carta como se deve.
     *
     * @param cardCode Número associado à carta (1 a 13) juntamente com o naipe associado à carta (O, E, C, P)
     */
    Card(const std::string &cardCode)
    {
        const char &i = *"";
        int it = 0;
        for (auto &&i : cardCode)
        {
            if (isalpha(cardCode[it]))
                break;
            it++;
        }

        std::string num = cardCode.substr(0, it);
        std::string nipe = cardCode.substr(it, cardCode.length() - 1);

        this->number = atoi(num.c_str());
        this->nipe = nipe;
    }

    bool operator<(Card const &card)
    {
        return this->number < card.number;
    }

    friend std::ostream &operator<<(std::ostream &out, const Card *card);
    friend std::ostream &operator<<(std::ostream &out, const Card card);

private:
    int number;
    std::string nipe;
};

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

#endif