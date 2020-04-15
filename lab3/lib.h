#ifndef lib_h_
#define lib_h_

typedef struct aluno Aluno;

/* ======================== */

Aluno* inicializa_aluno(char* nome, int matricula, float cr);
void imprime_aluno(Aluno* aluno);
char* retorna_nome(Aluno* aluno);
int retorna_matricula(Aluno* aluno);
float retorna_cr(Aluno* aluno);
void free_aluno(Aluno* aluno);

/* ====================================================================== */

typedef struct lista Lista;
typedef struct celula Celula;

/* ======================== */

Lista* inicializa_lista();
void insere(Lista* lista, Aluno* aluno);
void imprime_lista(Lista* lista);
Aluno* retira_lista(Lista* lista, char* nome);
void free_lista(Lista* lista);
#endif /* lib_h_ */