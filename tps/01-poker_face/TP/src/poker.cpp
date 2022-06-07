#include <getopt.h>
#include <regex>

#include "match.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

void uso() {
    std::cout << "============= Utilização do programa =============\n" << std::endl;
    std::cout << "\t-i \t<inputs_da_partida.txt> (arquivos de entrada para a partida)" << std::endl;
    std::cout << "\t-o \t<outputs_da_partida.txt> (arquivo para registrar os resultados da partida)" << std::endl;
    std::cout << "\t-p \t<arquivo_de_logs.txt> (arquivo para registrar os resultados computacionais de performance e/ou memória da partida)" << std::endl;
    std::cout << "\t-l \tCaso esta flag esteja presente, o acesso à memória é registrado no arquivo de logs de -p" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "\tOBS: O programa também pode ser executado sem parâmetro algum.\n\tEle está configurado para, por padrão, acessar como input o arquivo \"entrada.txt\" e como output o arquivo \"saida.txt\"." << std::endl;
}

std::string matchInputsPath = "entrada.txt";
std::string matchResultsPath = "saida.txt";
std::string logNameStr = "";
bool memoryRegister = false;

void parse_args(int argc, char **argv) {
    // variaveis externas do getopt
    extern char *optarg;

    // variavel auxiliar
    int c;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while (( c = getopt(argc, argv, "i:o:hp:l") ) != EOF){
        switch(c) {
            case 'i':
                avisoAssert(matchInputsPath == "entrada.txt", "Ja havia sido informado um arquivo para as entradas do programa.");
                
                matchInputsPath = optarg;
            break;

            case 'o':
                avisoAssert(matchResultsPath == "saida.txt", "Ja havia sido informado um arquivo para a saída do programa.");
                
                matchResultsPath = optarg;
            break;
            
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
    char *logNameChars[logNameStr.length()];
    std::strcpy(*logNameChars, logNameStr.c_str());
    iniciaMemLog(*logNameChars);

    // ativar ou nao o registro de acesso
    if (memoryRegister){ 
        ativaMemLog();
    }
    else{
        desativaMemLog();
    }

    Match *match;
    match = new Match(matchInputsPath);

    match->play(matchResultsPath);

    return finalizaMemLog();
}