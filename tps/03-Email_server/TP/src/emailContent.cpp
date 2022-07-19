#include "emailContent.hpp"

#include <sstream>
#include "msgassert.hpp"

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
        avisoAssert(word.length() < 40, "Uma das palavras do e-mail tem tamanho maior que o permitido.\n");

        wordCounter++;
    }

    // Verifica se a quantidade de palavras bate com a quantidade informada no arquivo de entrada.
    avisoAssert(wordCounter == wordsAmount, "A quantidade de palavras na frase não bate com a informada na entrada.");
    
    this->wordsAmount = wordsAmount;
    this->msg = msg;
}

std::string EmailContent::getMessage() {
    return this->msg;
}

std::ostream &operator<<(std::ostream &out, const EmailContent *emailContent) {
    out << "Este e-mail possui " << emailContent->wordsAmount << " palavras." << std::endl;
    out << "A mensagem dele é:" << std::endl;
    out << emailContent->msg;
    
    return out;
}