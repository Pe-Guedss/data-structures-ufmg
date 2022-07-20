#include <getopt.h>
#include <regex>

#include "session.hpp"

void uso() {
    std::cout << "============= Utilização do programa =============\n" << std::endl;
    std::cout << "\t-i / -I \t<input.txt> (arquivo com as frases a serem ordenadas)" << std::endl;
    std::cout << "\t-o / -O \t<output.txt> (arquivo para registrar as frases ordenadas)" << std::endl;
    std::cout << "\t-m / -M \t<numero_inteiro> (quantidade de elementos a serem considerados na mediana para escolha do pivô. 5 por padrão)" << std::endl;
    std::cout << "\t-s / -S \t<numero_inteiro> (Tamanho da subpartição a ser ordenada por inserção. 20 por padrão)" << std::endl;
    std::cout << "\t-p \t<arquivo_de_logs.out> (arquivo para registrar os resultados computacionais de performance e/ou memória da partida)" << std::endl;
    std::cout << "\t-l \tCaso esta flag esteja presente, o acesso à memória é registrado no arquivo de logs de -p" << std::endl << std::endl;

    std::cout << "Por padrão, o programa acessará os arquivos \"in.txt\" e \"out.txt\", localizados na pasta raiz do trabalho." << std::endl << "Além disso, também não é necessário informar os parâmetros \"m/M\" e \"s/S\", que são definidos por padrão como 5 e 20, respectivamente." << std::endl;
    std::cout << std::endl;
}

std::string operations = "entrada.txt";
std::string resultsLog = "saida.txt";

std::string logNameStr = "log.out";
bool memoryRegister = false;

void parse_args(int argc, char **argv) {
    // variaveis externas do getopt
    extern char *optarg;

    // variavel auxiliar
    int c;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while (( c = getopt(argc, argv, "i:I:o:O:m:M:s:S:hp:l") ) != EOF){
        switch(c) {
            case 'I':
            case 'i':                
                operations = optarg;
            break;

            case 'O':
            case 'o':                
                resultsLog = optarg;
            break;
            
            case 'H':
            case 'h':
                uso();
                exit(1);
            break;

            case 'p':
                logNameStr = optarg;
            break;

            case 'l':
                memoryRegister = true;
            break;

            default:
                uso();
                exit(1);
        }
    }

}

int main(int argc, char **argv) {
    parse_args(argc, argv);

    // iniciar registro de acesso
    char *logNameChars;
    logNameChars = new char[logNameStr.length()];
    std::strcpy(logNameChars, logNameStr.c_str());
    iniciaMemLog(logNameChars);

    // ativar ou nao o registro de acesso
    if (memoryRegister){ 
        ativaMemLog();
    }
    else{
        desativaMemLog();
    }

    defineFaseMemLog(0);
    Session *session;
    session = new Session(operations);

    defineFaseMemLog(1);
    session->finish(resultsLog);
    
    delete session;
    session = nullptr;

    return finalizaMemLog();
}