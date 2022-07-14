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
        if (word.length() > 40) throw "Uma das palavras do e-mail tem tamanho maior que o permitido.";
        
        this->msg += word;
        wordCounter++;
    }

    if (wordCounter != wordsAmount) throw "A quantidade de palavras na frase não bate com a informada na entrada.";
    
    this->wordsAmount = wordsAmount;
}