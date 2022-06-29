#include <iostream>
#include <string>
#include <sstream>

class PassCell {
    public:
        PassCell(std::string pass) {
            this->pass = pass;
            this->next = nullptr;
        }

    private:
        std::string pass;
        PassCell *next;

    friend class Password;
};

class Password {
    public:
        Password() {
            this->size = 0;
            this->first = nullptr;
            this->last = nullptr;
        }

        void addPass(std::string pass) {
            if (this->size == 0) {
                this->first = new PassCell(pass);
                this->last = this->first;

                this->size++;
                return;
            }
            
            this->last->next = new PassCell(pass);
            this->last = this->last->next;
            this->size++;
        }

        std::string popPass() {
            this->size--;

            PassCell *aux;
            std::string pass;

            aux = this->first;
            this->first = aux->next;

            pass = aux->pass;
            delete aux;
            aux = nullptr;

            return pass != "" ? pass : "-1";
        }

        int getSize() {
            return this->size;
        }

    private:
        int size;
        PassCell *first;
        PassCell *last;
};

int main() {
    std::string trash;

    Password *pass;
    pass = new Password();

    int pass_dig = 0;
    std::cin >> pass_dig;

    std::getline(std::cin, trash);
    for (int i = 0; i < pass_dig; i++) {
        int letterCounter = 0;

        std::string phrase, word, delimiter;
        std::getline(std::cin, phrase);
        std::stringstream auxPhrase(phrase);
        std::getline(std::cin, delimiter);

        std::string password = "";
        while ( getline(auxPhrase, word, ' ') ) {
            if (word != delimiter) {
                letterCounter += word.length() + 1;
                continue;
            }
            password += std::to_string(letterCounter) + *" ";
            letterCounter += word.length() + 1;
        }
        // password[password.length() - 1] = *"";
        pass->addPass(password);
    }

    while (pass->getSize() > 0) {
        std::string code = pass->popPass();
        if (code != "-1") {
            std::cout << code.substr(0, code.length()-1) << std::endl;
            continue;
        }
        std::cout << code << std::endl;
    }
    delete pass;
    pass = nullptr;

    return 0;
}