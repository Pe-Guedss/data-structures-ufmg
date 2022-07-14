#include "emailContent.hpp"

int main() {
    EmailContent a;
    try {
        a = EmailContent(3, "Eu sou Pedro!");
        std::cout << &a << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}