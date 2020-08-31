#include "list.hpp"
#include <limits>
#include <algorithm>
#include <iostream>

// Construir lista vazia
list::list() {
    this->primeiro = nullptr;
    this->tamanho = 0;
}

// Construir lista com "tamanho" cópias do valor "inicial".
list::list(unsigned int tamanho, int inicial) {

    this->tamanho = tamanho;
    this->primeiro = nullptr;
     for(unsigned int j = 0; j < this->tamanho; j++){
        no_encadeado* no= new no_encadeado(inicial, this->primeiro);
        this->primeiro = no;
     }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
void list::inserir(int elemento) {

       if(this->tamanho == 0){
            no_encadeado *no = new no_encadeado(elemento, this->primeiro);
            this->primeiro = no;
            this->tamanho++;
       }else{
            no_encadeado* anterior = obter_no_em(tamanho - 1);
            no_encadeado* no = new no_encadeado(elemento);
            anterior->proximo = no;
            this->tamanho++;
       }
    
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool list::remover(int elemento) {
    
    if(this->tamanho == 0 ) return false;
    
    bool elementoPertence = pertence(elemento);
    if(!elementoPertence) return false;

        unsigned int indiceRemocao = obter_indice_de(elemento);
        no_encadeado* anterior = obter_no_em(indiceRemocao - 1);
        no_encadeado* aSerRemovido = obter_no_em(indiceRemocao);

            if(indiceRemocao <= 0){
                this->primeiro = aSerRemovido->proximo;
                this->tamanho--;
                return true;
            }else{
                anterior->proximo = aSerRemovido->proximo;
                this->tamanho--;
                return true; 
            }

    return false;
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool list::pertence(int elemento) {

   if(this->tamanho == 0) return false;

    no_encadeado* no = this->primeiro;

    while(no != nullptr){
        if(no->valor == elemento){
            return true;
        }
        no = no->proximo;
    }
    return false;
}


// --- Métodos de "Lista" ---

// Inserir "elemento" na lista de forma que ele passe a constar no índice "indice".
// NOTE Necessário preservar a ordem relativa dos demais elementos.
bool list::inserir_em(unsigned int indice, int elemento) {
    if(indice == 0) {
        no_encadeado* novo_no = new no_encadeado(elemento, this->primeiro);
        this->primeiro = novo_no;

        this->tamanho++;

        return true;
    } else {
        no_encadeado* anterior = obter_no_em(indice - 1);

        if(anterior != nullptr) {
            no_encadeado* novo_no = new no_encadeado(elemento);
            novo_no->proximo = anterior->proximo;
            anterior->proximo = novo_no;

            this->tamanho++;

            return true;
        } else {
            return false;
        }
    }
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool list::remover_de(unsigned int indice) {

    unsigned int elementoObtido = obter_elemento_em(indice - 1);
    if(this->tamanho == 0) return false;
    if(indice > elementoObtido) return false;
 
    no_encadeado* anterior = this->primeiro;

    while(anterior != nullptr){
        if(elementoObtido <= 0){
            this->primeiro = this->primeiro->proximo;
            this->tamanho--;
        }else{
            remover(anterior->valor);
            return true;            
        }
            anterior = anterior->proximo;
    }
        
    return false;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int list::obter_elemento_em(unsigned int indice) {

    if(this->tamanho == 0)return std::numeric_limits<int>::max();

    if (indice > this->tamanho) return std::numeric_limits<int>::max();
    unsigned int cont = 0;

    no_encadeado* no = this->primeiro;

    while(no != nullptr){
        if(cont == indice){
            return no->valor;
        }
        no = no->proximo;
        cont++;
    }       

    return std::numeric_limits<int>::max();
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int list::obter_indice_de(int elemento) {

    if(this->tamanho == 0) return std::numeric_limits<unsigned int>::max();
    unsigned int indice = 0;

        bool elementoPertence = pertence(elemento);
            if(elementoPertence){
                no_encadeado* no = this->primeiro;
                
                while(no != nullptr){
                    if(no->valor == elemento){
                        return indice;
                    }
                    indice++;
                    no = no->proximo;
                }
            }
            
        return std::numeric_limits<unsigned int>::max();
}

// --- Métodos Auxiliares ---

// Construtor de um nó, onde a informação do próximo, no momento construção, é opcional
list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
    this->valor = valor;
    this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
list::no_encadeado* list::obter_no_em(unsigned int indice) {
    
    if(this->tamanho == 0 || indice > this->tamanho) return nullptr;

    no_encadeado* no = this->primeiro;
    unsigned int cont = 0;

    while(no != nullptr){
        if(cont == indice){
            return no;
        }
        no = no->proximo;
        cont++;

    }

    return nullptr;

}
// Desejamos obter o próprio nó que veja **antes** de algum com o valor informado.
// (ou seja, `anterior.proximo.valor == valor`)
// Auxilia processos que dependem de encontrar nós baseado em um valor.
// Deve retornar `nullptr` quando tal nó não existe.
list::no_encadeado* list::obter_no_anterior_a(int valor) {
    
    if(this->tamanho == 0) nullptr;

    unsigned int indiceElemento = obter_indice_de(valor);
    no_encadeado* noAnterior = obter_no_em(indiceElemento - 1);

        while(noAnterior != nullptr){ 
            if(noAnterior->proximo->valor == valor){
                return noAnterior;
            }
            noAnterior = noAnterior->proximo;
    }
    return nullptr;
}
