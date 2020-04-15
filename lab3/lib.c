#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

struct aluno{
    char* nome;
    int matricula;
    float cr;
};

/* ======================== */

Aluno* inicializa_aluno(char* nome, int matricula, float cr){
    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
    aluno->nome = (nome);
    aluno->matricula = matricula;
    aluno->cr = cr;

    return aluno;
}

void imprime_aluno(Aluno* aluno){
    printf("nome:%s, matricula:%i, cr:%.2f\n", aluno->nome, aluno->matricula, aluno->cr);
}

char* retorna_nome(Aluno* aluno){
    return aluno->nome;
}

int retorna_matricula(Aluno* aluno){
    return aluno->matricula;
}

float retorna_cr(Aluno* aluno){
    return aluno->cr;
}

void free_aluno(Aluno* aluno){
    free(aluno->nome);
    free(aluno);
}

/* ====================================================================== */

struct lista{
    Celula* primeiro;
    Celula* ultimo;
};

struct celula{
    Aluno* item;
    Celula* proximo;
};

/* ======================== */

Lista* inicializa_lista(){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

void insere(Lista* lista, Aluno* aluno){
    Celula* celula = (Celula*) malloc(sizeof(Celula));
    celula->item = aluno;
    celula->proximo = NULL;

    if(lista->primeiro == NULL){
        lista->primeiro = lista->ultimo = celula;
        return;
    }
    else{
        lista->ultimo->proximo = celula;
        lista->ultimo = lista->ultimo->proximo;
    }
}

void imprime_lista(Lista* lista){
    for(Celula* c = lista->primeiro; c != NULL; c = c->proximo){
        imprime_aluno(c->item);
    }
}

Aluno* retira_lista(Lista* lista, char* nome){
    Aluno* retorno;
    if(lista == NULL)
        return NULL;

    for(Celula* c = lista->primeiro; c->proximo != NULL; c = c->proximo){
        // unico
        if(strcmp(retorna_nome(c->item), nome) == 0 && c == lista->primeiro && c == lista->ultimo){
            retorno = c->item;
            free(c);
            lista->primeiro = lista->ultimo = NULL;
            return retorno;
        }
        // primeiro
        if(strcmp(retorna_nome(c->item), nome) == 0 && c == lista->primeiro){
            retorno = c->item;
            lista->primeiro = c->proximo;
            free(c);
            return retorno;
        }
        // ultimo
        if(strcmp(retorna_nome(c->proximo->item), nome) == 0 && c == lista->ultimo){
            retorno = c->proximo->item;
            lista->ultimo = c;
            c->proximo = NULL;
            free(c->proximo);
            return retorno;
        }
        // outro
        if(strcmp(retorna_nome(c->proximo->item), nome) == 0){
            retorno = c->proximo->item;
            c->proximo = c->proximo->proximo;
            free(c->proximo);
            return retorno;
        }
    }

    return NULL;
}

void free_lista(Lista* lista){
    for(Celula* c = lista->primeiro; c != NULL; c = c->proximo){
        free_aluno(c->item);
        free(c);
    }
    free(lista);
}
