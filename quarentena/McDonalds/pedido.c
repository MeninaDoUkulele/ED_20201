#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"
#include "produto.h"

typedef struct celula Celula;

struct celula{
    TProduto* item;
    Celula* proximo;
};

struct pedido{
    char* dono;
    Celula* primeiro;
    Celula* ultimo;
};

TPedido* InicPedido (char* dono){
    TPedido* pedido = (TPedido*) malloc(sizeof(TPedido));
    pedido->dono = strdup(dono);
    pedido->primeiro = NULL;
    pedido->ultimo = NULL;

    return pedido;
};

void IncluiProdutoPedido (TPedido* pedido, TProduto* prod){
    Celula* celula = (Celula*) malloc(sizeof(Celula));
    celula->item = prod;
    celula->proximo = NULL;

    if(pedido->primeiro == NULL){
        pedido->primeiro = pedido->ultimo = celula;
        return;
    }
    else{
        pedido->ultimo->proximo = celula;
        pedido->ultimo = pedido->ultimo->proximo;
    }
}

void ImprimePedido (TPedido* pedido){
    printf("%s:\n", pedido->dono);
    for(Celula* i = pedido->primeiro; i != NULL; i = i->proximo){
        ImprimeIngredientes(i->item);
    }
}

void RetiraProdutoPedido (TPedido* pedido, char* prod){
    TProduto* retorno;
    if(pedido == NULL)
        return;

    for(Celula* c = pedido->primeiro; c->proximo != NULL; c = c->proximo){
        // unico
        if(strcmp(RetornaNome(c->item), prod) == 0 && c == pedido->primeiro && c == pedido->ultimo){
            retorno = c->item;
            free(c);
            pedido->primeiro = pedido->ultimo = NULL;
            return;
        }
        // primeiro
        if(strcmp(RetornaNome(c->item), prod) == 0 && c == pedido->primeiro){
            retorno = c->item;
            pedido->primeiro = c->proximo;
            free(c);
            return;
        }
        // ultimo
        if(strcmp(RetornaNome(c->proximo->item), prod) == 0 && c == pedido->ultimo){
            retorno = c->proximo->item;
            pedido->ultimo = c;
            c->proximo = NULL;
            free(c->proximo);
            return;
        }
        // outro
        if(strcmp(RetornaNome(c->proximo->item), prod) == 0){
            retorno = c->proximo->item;
            c->proximo = c->proximo->proximo;
            free(c->proximo);
            return;
        }
    }
}

int EnviaPedido (TPedido* pedido, int restricao_calorica, char* restricao_alimentar){
    int aux;
    for(Celula* i = pedido->primeiro; i != NULL; i = i->proximo){
        if((VerificaIngrediente(i->item, restricao_alimentar) == 1) || (Calorias(i->item) > restricao_calorica)){
            aux = 0;
        }
    }


    if(aux == 0){
        return 0;
    }

    return 1;
}
