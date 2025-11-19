//- OK - INSERE TURMA: permite a inserção de uma turma na lista de turmas, de forma ordenada. Não pode ter número de turma repetido.
//- INSERE ESTUDANTE: permite a inserção de um estudante em uma das turmas, desde que a turma já exista. 
//Não pode haver nomes repetidos de estudantes na mesma turma, e entre as turmas, se houver nome repetido, caracterizar o nome de cada estudante como pertencente a uma turma específica
//- REMOVE TURMA: remove uma turma, removendo também todos os estudantes associados a ela
//- REMOVE ESTUDANTE: remove um estudante de uma turma específica (remove o nodo com o nome do estudante), mantendo a ABP na qual ele estava situado ordenada.
//- CONTA ESTUDANTES: mostra cada turma com o número total de estudantes de cada turma.
//- EXIBE TURMA: exibe a lista dos nomes dos estudantes de uma turma em ordem alfabética (de A a Z) ou em ordem alfabética inversa (de Z a A).
//- EXIBE TURMA PRÉ: exibe a lista dos nomes dos estudantes de uma turma em ordem pré-fixada pela esquerda.
//- EXIBE TODOS ESTUDANTES: exibe uma lista única, com o nome de todos os estudantes de todas as turmas, em ordem alfabética (colocar a turma ao lado de cada nome)
//- NOMES REPETIDOS: exibe os nomes repetidos mais de uma vez (entre as turmas)
//- MAIOR TURMA: exibe a turma com maior número de estudantes: número da turma e quantidade de estudantes. Se houver igualdade, exibir todas as turmas com esse maior número
//- MENOR TURMA: exibe a turma com menor número de estudantes: número da turma e quantidade de estudantes. 
//Se houver igualdade, exibir todas as turmas com esse menor número

//Turmas/estudantes a serem incluídos inicialmente: 
//103: joao, ana, mauro, clarice, luiz, samuel, diego
//201: carlos, maria, beatriz, lucas, vitor, denise
//305: maria, eduardo, paulo, cintia, marisa, alvaro, sandra
//202: patricia, anelise, douglas, diego, marcos, vania
//105: eduardo, lucas, maria, vinicius, felipe, clara

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct estudante {
    char nome[50];
    struct estudante *pai;
    struct estudante *esq;
    struct estudante *dir;
} Estudante;

typedef struct turma {
    int codigo;
    int quantidadeEstudantes;
    Estudante *estudantes;
    struct turma *prox;
} Turma;

Turma *turmas = NULL; 

Estudante* novoEstudante(char nome[N]) {
    Estudante *novo = (Estudante*)malloc(sizeof(Estudante));

    strcpy(novo->nome, nome);
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

Turma* novaTurma(int codigo) {
    Turma *novo = (Turma*)malloc(sizeof(Turma));

    novo->codigo = codigo;
    novo->estudantes = NULL;
    novo->prox = NULL;
    novo->quantidadeEstudantes = 0;

    return novo;
}

void inserirTurma(int codigo) {
    Turma *novo = novaTurma(codigo);

    if (turmas == NULL) {
        turmas = novo;
    }
    else if (codigo < turmas->codigo) {
        novo->prox = turmas;
        turmas = novo;
    }
    else {
        Turma *ant = turmas;
        Turma *aux = turmas->prox;
    
        while (aux != NULL && aux->codigo < codigo) {
            ant = aux;
            aux = aux->prox;
        }
    
        if (aux != NULL && aux->codigo == codigo) {
            printf("Erro: turma %d ja cadastrada!\n", codigo);
            free(novo);
            return;
        }
    
        ant->prox = novo;
        novo->prox = aux;
    
    }
    
    printf("Turma '%d' cadastrada com sucesso!\n", codigo);
}

Estudante* inserirEstudanteRecursivo(Estudante* estudantes, char nome[N], Estudante* pai) {
    if (estudantes == NULL) {
        Estudante *novo = novoEstudante(nome);
        novo->pai = pai;
        return novo;
    }

    if (strcmp(nome, estudantes->nome) < 0) {
        estudantes->esq = inserirEstudanteRecursivo(estudantes->esq, nome, estudantes);
    }
    else if (strcmp(nome, estudantes->nome) > 0) {
        estudantes->dir = inserirEstudanteRecursivo(estudantes->dir, nome, estudantes);
    }
    else {
        printf("Erro: nome '%s' ja existe nesta turma!\n", nome);
    }

    return estudantes;
}

void inserirEstudante(int codigoturma, char nome[N]) {
    Turma *aux = turmas;
    
    while(aux != NULL && aux->codigo != codigoturma) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Turma nao encontrada!\n");
        return;
    }

    aux->estudantes = inserirEstudanteRecursivo(aux->estudantes, nome, NULL);
    (aux->quantidadeEstudantes)++;
}

void centralEstudante(Estudante* a) {
    if (a != NULL) {
        centralEstudante(a->esq);
        printf("- %s \n", a->nome);
        centralEstudante(a->dir);
    }
}

void consultarTodasTurmas() {
    Turma *auxT = turmas;
    
    printf("\n\n--- Lista de Turmas ---\n");
    while(auxT != NULL) {
        printf("Cod: %2d Estudantes: %d\n", auxT->codigo, auxT->quantidadeEstudantes);
        Estudante *auxE = auxT->estudantes;

        centralEstudante(auxE);

        auxT = auxT->prox;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

void inicializar () {
    turmas = NULL;
}

int main() {
    inicializar();

    inserirTurma(103);
    inserirTurma(201);
    inserirTurma(305);
    inserirTurma(305);
    inserirTurma(202);
    inserirTurma(105);

    inserirEstudante(103, "Joao");
    inserirEstudante(103, "Ana");
    inserirEstudante(103, "Mauro");
    inserirEstudante(103, "Clarice");
    inserirEstudante(103, "Luiz");
    inserirEstudante(103, "Samuel");
    inserirEstudante(103, "Diego");
    
    inserirEstudante(201, "Carlos");
    inserirEstudante(201, "Maria");
    inserirEstudante(201, "Beatriz");
    inserirEstudante(201, "Lucas");
    inserirEstudante(201, "Vitor");
    inserirEstudante(201, "Denise");
    
    inserirEstudante(305, "Maria");
    inserirEstudante(305, "Eduardo");
    inserirEstudante(305, "Paulo");
    inserirEstudante(305, "Cintia");
    inserirEstudante(305, "Marisa");
    inserirEstudante(305, "Alvaro");
    inserirEstudante(305, "Sandra");
    
    inserirEstudante(202, "Patricia");
    inserirEstudante(202, "Anelise");
    inserirEstudante(202, "Douglas");
    inserirEstudante(202, "Diego");
    inserirEstudante(202, "Marcos");
    inserirEstudante(202, "Vania");
    
    inserirEstudante(105, "Eduardo");
    inserirEstudante(105, "Lucas");
    inserirEstudante(105, "Maria");
    inserirEstudante(105, "Vinicius");
    inserirEstudante(105, "Felipe");
    inserirEstudante(105, "Clara");

    consultarTodasTurmas();
}