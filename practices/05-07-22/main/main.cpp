#include <iostream>
#include <string>
#include <sstream>

class Cell {
    public:
        Cell() {
            this->value = -1;
            this->next = nullptr;
        }

        Cell(int value) {
            this->value = value;
            this->next = nullptr;
        }

    private:
        int value;
        Cell *next;

    friend class CellList;
};

class CellList {
    public:
        CellList() {
            this->first = new Cell();
            this->last = this->first;
            this->size = 0;
        }

        ~CellList() {
            this->clean();
        }

        void push(int value) {
            Cell *newCell;
            newCell = new Cell(value);

            this->last->next = newCell;
            this->last = newCell;

            this->size++;
        }

        void insert(int pos, int value) {
            Cell *aux;
            aux = this->insertHelper(pos, true);

            Cell *newCell;
            newCell = new Cell(value);

            newCell->next = aux->next;
            aux->next = newCell;
            if(newCell->next == nullptr) this->last = newCell;

            this->size++;
        }

        Cell *popFromStart() {
            if (this->size == 0) throw "ERRO: Lista vazia!";

            Cell *w;
            w = this->first->next;

            this->first->next = w->next;
            if(this->first->next == nullptr) this->last = this->first;

            this->size--;
            return w;
        }

        Cell *removeFromPos(int pos) {
            if (this->size == 0) throw "ERRO: Lista vazia!";

            Cell *CellBefore;
            CellBefore = this->insertHelper(pos, true);

            Cell *Cell;
            Cell = CellBefore->next;

            CellBefore->next = Cell->next;
            if(CellBefore->next == nullptr) this->last = CellBefore;

            this->size--;
            return Cell;
        }

        void print() {
            Cell *aux;
            aux = this->first->next;
            while (aux != nullptr) {
                std::cout << aux->value << " -> ";
                aux = aux->next;
            }
            std::cout << "\\" << std::endl;
        }

        void clean() {
            Cell *aux;
            aux = this->first->next;
            while (aux != nullptr) {
                this->first->next = aux->next;
                delete aux;
                aux = this->first->next;
            }
            this->last = this->first;
            this->size = 0;
        }

    private:
        int size;
        Cell *first;
        Cell *last;

        Cell *insertHelper(int pos, bool before) {
            Cell *w;
            if ( (pos > this->size + 1) || (pos <= 0) ) throw "ERRO: Posicao Invalida!";

            w = this->first;
            for(int i = 1; i < pos; i++) {
                w = w->next;
            }

            if(!before) w = w->next;

            return w;
        }
};

class Hash_LE {
    public:
        Hash_LE(int size);

        Hash_LE();

        ~Hash_LE();

        void Insere(int item);

        void Imprime();
        
    CellList *tabela;

    private:
        int size;
};

Hash_LE::Hash_LE(){
    this->tabela = nullptr;
    size = -1;
}

Hash_LE::Hash_LE(int n){
    this->tabela = new CellList[n];
    size = n;
}

void Hash_LE::Insere(int item){
    int index = item%size;
    this->tabela[index].push(item);
}
void Hash_LE::Imprime(){
    for(int i =0; i < this->size; i++) {
        std::cout << i << " -> ";
        this->tabela[i].print();
    }
}

int main(){
    int hashNum;
    std::cin >> hashNum;

    Hash_LE **hash = new Hash_LE*[hashNum];

    int listsAmount, cells, value;
    for(int i =0; i < hashNum; i++) {
        std::cin >> listsAmount;
        hash[i] = new Hash_LE(listsAmount);
        std::cin >> cells;
        for(int j = 0; j < cells; j++) {
            std::cin >> value;
            hash[i]->Insere(value);
        }
    }

    int i = -1;
    for (i = 0; i < hashNum - 1; i++) {
        hash[i]->Imprime();
        std::cout << std::endl;
    }
    hash[i]->Imprime();
    

    return 0;
}