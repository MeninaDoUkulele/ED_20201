#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct aluno{
    char* nome;
    int matricula;
};

typedef struct celula TCelula;
struct celula{
    TAluno* aluno;
    TCelula* proximo;
};

struct lista{
    TCelula* primeiro;
    TCelula* ultimo;
};


// ================================================

TLista* CriaLista(){
    TLista* lista = (TLista*) malloc(sizeof(TLista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

TAluno* InicializaAluno(char* nome, int matricula){
    TAluno* aluno = (TAluno*) malloc(sizeof(TAluno));
    aluno->nome = strdup(nome);
    aluno->matricula = matricula;

    return aluno;
}

void InsereAluno (TLista* lista, TAluno* aluno){
    TCelula* celula =  (TCelula*) malloc(sizeof(TCelula));
    celula->aluno = aluno;
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

TAluno* Retira (TLista* lista, int mat){
    TAluno* retorno;
    // vazio
    if(lista == NULL) 
        return NULL;

    for(TCelula* l = lista->primeiro; l->proximo != NULL; l = l->proximo){
        // unico
        if(l->aluno->matricula == mat && l == lista->primeiro && l == lista->ultimo){
            retorno = l->aluno;
            // free(l);
            lista->primeiro = lista->ultimo = NULL;
            return retorno;
        }
        // primeiro
        if(l->aluno->matricula == mat && l == lista->primeiro){
            retorno = l->aluno;
            lista->primeiro = l->proximo;
            // free(l);
            return retorno;
        }
        // ultimo
        if(l->proximo->aluno->matricula == mat && l == lista->ultimo){
            retorno = l->proximo->aluno;
            lista->ultimo = l;
            l->proximo = NULL;
            // free(l->proximo);
            return retorno;
        }
        // outro
        // outro
        if(l->proximo->aluno->matricula == mat){
            retorno = l->proximo->aluno;
            l->proximo = l->proximo->proximo;
            // free(l->proximo);
            return retorno;
        }
    }

    return NULL;
}

void RetiraRepetidos (TLista* lista){
    for(TCelula* l = lista->primeiro; l != NULL; l = l->proximo){
        for(TCelula* c = l->proximo; c != NULL; c = c->proximo){
            if(c->aluno->matricula == l->aluno->matricula){
                TAluno* lixo = Retira(lista, c->aluno->matricula);
                break;
            }
        }
    }
}

TLista* Merge (TLista* turma1, TLista* turma2){
    TLista* nova = CriaLista();

    for(TCelula* l = turma1->primeiro; l != NULL; l = l->proximo){
        TAluno* aux = InicializaAluno(l->aluno->nome, l->aluno->matricula);
        InsereAluno(nova, aux);
    }

    for(TCelula* l = turma2->primeiro; l != NULL; l = l->proximo){
        TAluno* aux = InicializaAluno(l->aluno->nome, l->aluno->matricula);
        InsereAluno(nova, aux);
    }

    return nova;
}

void LiberaAluno (TAluno* aluno){
    free(aluno->nome);
    free(aluno);
}

void Imprime (TLista* lista){
    for(TCelula* l = lista->primeiro; l != NULL; l = l->proximo){
        printf("%i %s\n", l->aluno->matricula, l->aluno->nome);
    }
}

void LiberaLista (TLista* lista){
    RetiraRepetidos(lista);
    for(TCelula* c = lista->primeiro; c != lista->ultimo; c = c->proximo){
        LiberaAluno(c->aluno);
        free(c);
    }
    LiberaAluno(lista->ultimo->aluno);
    free(lista->ultimo);

    free(lista);
}