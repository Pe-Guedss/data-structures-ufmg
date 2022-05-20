//---------------------------------------------------------------------
// Arquivo	: card.h
// Conteudo	: definicoes da classe Carta
// Autor	: Pedro de Oliveira Guedes (pedro.og2002@gmail.com)
//---------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

#include <string>

/**
 * @brief Classe que armazena e gerencia as informacoes das cartas do baralho, enquanto objetos individuais.
 *
 */
class Card
{
public:
    /**
     * @brief Construtor padrao que inicializa todas as variaveis privadas da classe.
     */
    Card();
    /**
     * @brief Construtor que inicia os valores da carta como se deve.
     *
     * @param cardCdde Número associado à carta (1 a 13) juntamente com o naipe associado à carta (O, E, C, P)
     */
    Card(const std::string &cardCode);

private:
    int number;
    char nipe;
};

#endif