#include <iostream>
#include <string>
#include <sstream>

enum {
    I = 1,
    P = 2,
    INFIXA = 3,
    PREFIXA = 4,
    POSFIXA = 5
};

class TipoNo {
    public:
        TipoNo() {
            this->item = "";
            esq = nullptr;
            dir = nullptr;
        }

        TipoNo(std::string value) {
            this->item = value;
            esq = nullptr;
            dir = nullptr;
        }

    private:
        std::string item;
        TipoNo *esq;
        TipoNo *dir;

    friend class ArvoreBinaria;
};

class ArvoreBinaria {

    public:
        ArvoreBinaria() {
            this->raiz = nullptr;
        }

        ~ArvoreBinaria() {
            this->Limpa();
        }

        void Insere(std::string item) {
            this->InsereRecursivo(this->raiz, item);
        }

        void Caminha(int tipo) {
            std::string *aux = new std::string("");
            switch (tipo) {
                case INFIXA:
                    this->InOrdem(this->raiz, aux);
                break;

                case PREFIXA:
                    this->PreOrdem(this->raiz, aux);
                break;

                case POSFIXA:
                    this->PosOrdem(this->raiz, aux);
                break;
                
                default:
                break;
            }

            this->resultado.append(*aux + "\n");
        }

        bool Pesquisa(std::string item) {
            return this->Existe(item, this->raiz);
        }

        void Limpa() {
            ApagaRecursivo(raiz);
            raiz = nullptr;
        }

        void ImprimeResultado() {
            std::cout << this->resultado << std::endl;
        }

    private:
        void InsereRecursivo(TipoNo* &p, std::string item) {
            if(p == nullptr) {
                p = new TipoNo();
                p->item = item;
            }
            else {
                if(item < p->item) InsereRecursivo(p->esq, item);

                else InsereRecursivo(p->dir, item);
            }
        }

        void ApagaRecursivo(TipoNo* p) {
            if(p != nullptr){
                ApagaRecursivo(p->esq);
                ApagaRecursivo(p->dir);
                delete p;
            }
        }

        bool Existe(std::string item, TipoNo* &no) {
            if (no == nullptr) {
                this->resultado.append(item + " nao existe\n");
                return false;
            }

            if (no->item == item) {
                this->resultado.append(item + " existe\n");
                return true;
            }
            else if (item > no->item) {
                return Existe(item, no->dir);
            }

            return Existe(item, no->esq);
        }

        void PreOrdem(TipoNo* p, std::string *frase) {
            if(p != nullptr){
                frase->assign(*frase + p->item + " ");
                PreOrdem(p->esq, frase);
                PreOrdem(p->dir, frase);
            }
        }

        void InOrdem(TipoNo* p, std::string *frase) {
            if(p != nullptr){
                InOrdem(p->esq, frase);
                frase->assign(*frase + p->item + " ");
                InOrdem(p->dir, frase);
            }
        }

        void PosOrdem(TipoNo* p, std::string *frase) {
            if(p != nullptr){
                PosOrdem(p->esq, frase);
                PosOrdem(p->dir, frase);
                frase->assign(*frase + p->item + " ");
            }
        }

        TipoNo *raiz;
        std::string resultado;
};

int main() {
    ArvoreBinaria *binTree;
    binTree = new ArvoreBinaria();

    std::string aux;
    while (std::getline(std::cin, aux)) {
        if (aux.length() == 3) {
            std::string elemento = aux.substr(2, 3);
            switch (aux[0]) {
                case 'I':
                    binTree->Insere(elemento);
                break;

                case 'P':
                    binTree->Pesquisa(elemento);
                break;
            
                default:
                break;
            }
        }
        
        else {
            if (aux == "INFIXA") {
                binTree->Caminha(INFIXA);
            }
            else if (aux == "PREFIXA") {
                binTree->Caminha(PREFIXA);
            }
            else if (aux == "POSFIXA") {
                binTree->Caminha(POSFIXA);
            }
        }
        
    }

    binTree->ImprimeResultado();

    delete binTree;
    binTree = nullptr;
    return 0;
}