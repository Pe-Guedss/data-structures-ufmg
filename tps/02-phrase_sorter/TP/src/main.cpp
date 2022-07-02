#include <getopt.h>

#include "phrase_sorter.hpp"

void uso() {
    std::cout << "============= Utilização do programa =============\n" << std::endl;
    std::cout << "\t-i / -I \t<input.txt> (arquivo com as frases a serem ordenadas)" << std::endl;
    std::cout << "\t-o / -O \t<output.txt> (arquivo para registrar as frases ordenadas)" << std::endl;
    std::cout << "\t-m / -M \t<numero_inteiro> (quantidade de elementos a serem considerados na mediana para escolha do pivô - 5 por padrão)" << std::endl;
    std::cout << "\t-s / -S \t<numero_inteiro> (Tamanho da subpartição a ser ordenada por inserção - 20 por padrão)" << std::endl;
    std::cout << "\t-p \t<arquivo_de_logs.out> (arquivo para registrar os resultados computacionais de performance e/ou memória da partida)" << std::endl;
    std::cout << "\t-l \tCaso esta flag esteja presente, o acesso à memória é registrado no arquivo de logs de -p" << std::endl << std::endl;

    std::cout << "Por padrão, o programa acessará os arquivos \"in.txt\" e \"out.txt\", localizados na pasta raiz do trabalho." << std::endl << "Além disso, também não é necessário informar os parâmetros \"m/M\" e \"s/S\", que são definidos por padrão como 5 e 20, respectivamente." << std::endl;
    std::cout << std::endl;
}

std::string input = "in.txt";
std::string output = "out.txt";

std::string medianSizeStr = "5";
int medianSize = 5;
std::string insertionSizeStr = "20";
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
                input = optarg;
            break;

            case 'O':
            case 'o':                
                output = optarg;
            break;

            case 'M':
            case 'm':
                medianSizeStr = optarg;
                medianSize = std::stoi(medianSizeStr);
                erroAssert(medianSize > 0, "A quantidade de elementos para a mediana não pode ser negativa.");
            break;

            case 'S':
            case 's':
                insertionSizeStr = optarg;
                insertionSize = std::stoi(insertionSizeStr);
                erroAssert(insertionSize > 0, "A quantidade de elementos para a ordenação por inserção não pode ser negativa.");
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
    std::cout << input << std::endl << output << std::endl << medianSize << std::endl << insertionSize << std::endl;

    PhraseSorter *phraseSorter;
    phraseSorter = new PhraseSorter(input, medianSize, insertionSize);

    phraseSorter->print(output);

    delete phraseSorter;
    phraseSorter = nullptr;
    return 0;
}