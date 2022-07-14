#include "emailContent.hpp"
#include <sstream>

EmailContent::EmailContent() {
    this->wordsAmount = -1;
    this->msg = "";
}

EmailContent::EmailContent(int wordsAmount, std::string msg) {
    this->msg = "";
    std::string word;
    int wordCounter = 0;

    std::stringstream emailMessage(msg);
    while (emailMessage >> word) {
        // Verifica se as palavras não excedem o limite de caracteres
        if (word.length() > 40) throw std::invalid_argument("Uma das palavras do e-mail tem tamanho maior que o permitido.");

        wordCounter++;
    }

    // Verifica se a quantidade de palavras bate com a quantidade informada no arquivo de entrada.
    if (wordCounter != wordsAmount) throw std::invalid_argument("A quantidade de palavras na frase não bate com a informada na entrada.");
    
    this->wordsAmount = wordsAmount;
    this->msg = msg;
}

std::ostream &operator<<(std::ostream &out, const EmailContent *emailContent) {
    out << "Este e-mail possui " << emailContent->wordsAmount << " palavras." << std::endl;
    out << "A mensagem dele é:" << std::endl;
    out << emailContent->msg;
    
    return out;
}