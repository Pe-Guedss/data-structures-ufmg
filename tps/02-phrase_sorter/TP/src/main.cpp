#include <getopt.h>
#include "msgassert.hpp"
#include "phrase_sorter.hpp"

void uso() {
    std::cout << "============= Utilização do programa =============\n" << std::endl;
    std::cout << "\t-i / -I \t<input.txt> (arquivo com as frases a serem ordenadas)" << std::endl;
    std::cout << "\t-o / -O \t<output.txt> (arquivo para registrar as frases ordenadas)" << std::endl;
    std::cout << "\t-m / -M \t<numero_inteiro> (quantidade de elementos a serem considerados na mediana para escolha do pivô - 5 por padrão)" << std::endl;
    std::cout << "\t-s / -S \t<numero_inteiro> (Tamanho da subpartição a ser ordenada por inserção - 20 por padrão)" << std::endl;
    std::cout << "\t-p \t<arquivo_de_logs.out> (arquivo para registrar os resultados computacionais de performance e/ou memória da partida)" << std::endl;
    std::cout << "\t-l \tCaso esta flag esteja presente, o acesso à memória é registrado no arquivo de logs de -p" << std::endl;
    std::cout << std::endl;
}

std::string input = "";
std::string output = "";
int medianSize = 5;
int insertionSize = 20;
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
                avisoAssert(input == "entrada.txt", "Ja havia sido informado um arquivo para as entradas do programa.");
                
                input = optarg;
            break;

            case 'O':
            case 'o':
                avisoAssert(output == "saida.txt", "Ja havia sido informado um arquivo para a saída do programa.");
                
                output = optarg;
            break;

            case 'M':
            case 'm':
                medianSize = (int) optarg;
            break;

            case 'S':
            case 's':
                insertionSize = (int) optarg;
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

    PhraseSorter *phraseSorter;
    phraseSorter = new PhraseSorter("in.txt", medianSize, insertionSize);

    phraseSorter->print("out.txt");

    delete phraseSorter;
    phraseSorter = nullptr;
    return 0;
}