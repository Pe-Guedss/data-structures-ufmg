#include "email.hpp"

int main() {
    Email a;
    a = Email(3, 5);

    a.setContent(5, "Olá, eu sou Pedro! Prazer!");

    std::cout << &a << std::endl;
    
    return 0;
}