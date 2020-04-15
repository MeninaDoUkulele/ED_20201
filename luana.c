#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto Produto;
struct produto{
    char* nome;
    float preco;
};

typedef struct tipocelula Tipocelula;
struct tipocelula{
    Produto* item;
    Tipocelula* proximo;
};

typedef struct lista Lista;
struct lista{
    Tipocelula* primeiro;
    Tipocelula* ultimo;
};
void free_celula(Tipocelula* celula);


Produto* inicializa_item(char* nome, float preco){
    Produto* produto = (Produto*) malloc(sizeof(Produto));
    produto->nome = strdup(nome);
    produto->preco = preco;

    return produto;
}

Lista* inicializa_lista(){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

int vazia(Lista* lista){
    return (lista->primeiro == NULL);
}

void imprime_item(Produto* produto){
    printf("%s custa %.2f\n", produto->nome, produto->preco);
}

void imprime(Lista* lista){
    for(Tipocelula* c = lista->primeiro; c != NULL; c = c->proximo){
        imprime_item(c->item);
        printf("==================================\n");
    }
}

void insere(Lista* lista, Produto* produto){
    Tipocelula* celula = (Tipocelula*) malloc(sizeof(Tipocelula));
    if(vazia(lista)){
        lista->primeiro = lista->ultimo = celula;
    } else{
        lista->ultimo->proximo = celula;
        lista->ultimo = lista->ultimo->proximo;
    }
    lista->ultimo->item = produto;
    lista->ultimo->proximo = NULL;
}

void free_item(Produto* produto){
    free(produto->nome);
    free(produto);
}

void retira(Lista* lista, char* nome){
    if(vazia(lista))
        return;

    for(Tipocelula* c = lista->primeiro; c->proximo != NULL; c = c->proximo){
        // unico
        if(strcmp(c->item->nome, nome) == 0 && c == lista->primeiro && c == lista->ultimo){
            
            lista->primeiro = lista->ultimo = NULL;
            return;
        }
        // primeiro
        if(strcmp(c->item->nome, nome) == 0 && c == lista->primeiro){
            lista->primeiro = c->proximo;
            return;
        }
        // ultimo
        if(strcmp(c->proximo->item->nome, nome) == 0 && c == lista->ultimo){
            lista->ultimo = c;
            c->proximo = NULL;
            return;
        }
        // outro
        if(strcmp(c->proximo->item->nome, nome) == 0){
            c->proximo = c->proximo->proximo;
            return;
        }
    }
}


// void free_celula(Tipocelula* celula){
//     free_item(celula->item);
//     celula->proximo = NULL;
//     free(celula);
// }

void free_lista(Lista* lista){
    Tipocelula* c = lista->primeiro;
    Tipocelula* aux = NULL;

    while(c != NULL){
        free_item(c->item);
        aux = c->proximo;
        free(c);
        c = aux;
    }
    free(lista);
}

int main(){
    Lista* lista = inicializa_lista();

    Produto* sophie = inicializa_item("dog", 0);
    Produto* bea = inicializa_item("gato", 0);
    Produto* luana = inicializa_item("nutella", 1000);

    insere(lista, sophie);
    insere(lista, bea);
    insere(lista, luana);

    imprime(lista);

    retira(lista, "luana");
    imprime(lista);
    free_lista(lista);

    return 0;
}
