#include "session.hpp"

int main() {
    Session *session;
    session = new Session("in.txt");

    session->finish("out.txt");
    
    return 0;
}