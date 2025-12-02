//- OK - INSERE TURMA: permite a inserção de uma turma na lista de turmas, de forma ordenada. Não pode ter número de turma repetido.
//- OK - INSERE ESTUDANTE: permite a inserção de um estudante em uma das turmas, desde que a turma já exista. 
//Não pode haver nomes repetidos de estudantes na mesma turma, e entre as turmas, se houver nome repetido, caracterizar o nome de cada estudante como pertencente a uma turma específica
//- REMOVE TURMA: remove uma turma, removendo também todos os estudantes associados a ela
//- REMOVE ESTUDANTE: remove um estudante de uma turma específica (remove o nodo com o nome do estudante), mantendo a ABP na qual ele estava situado ordenada.
//- OK - CONTA ESTUDANTES: mostra cada turma com o número total de estudantes de cada turma.
//- OK - EXIBE TURMA: exibe a lista dos nomes dos estudantes de uma turma em ordem alfabética (de A a Z) ou em ordem alfabética inversa (de Z a A).
//- OK - EXIBE TURMA PRÉ: exibe a lista dos nomes dos estudantes de uma turma em ordem pré-fixada pela esquerda.
//- OK - EXIBE TODOS ESTUDANTES: exibe uma lista única, com o nome de todos os estudantes de todas as turmas, em ordem alfabética (colocar a turma ao lado de cada nome)
//- OK - NOMES REPETIDOS: exibe os nomes repetidos mais de uma vez (entre as turmas)
//- OK - MAIOR TURMA: exibe a turma com maior número de estudantes: número da turma e quantidade de estudantes. Se houver igualdade, exibir todas as turmas com esse maior número
//- OK - MENOR TURMA: exibe a turma com menor número de estudantes: número da turma e quantidade de estudantes. Se houver igualdade, exibir todas as turmas com esse menor número

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
    char nome[N];
    struct estudante *esq;
    struct estudante *dir;
} Estudante;

typedef struct listaestudante {
    char nome[N];
    int turma;
    struct listaestudante *prox;
} ListaEstudante;

typedef struct turma {
    int codigo;
    int quantidadeEstudantes;
    Estudante *estudantes;
    struct turma *prox;
} Turma;

Turma *turmas = NULL; 
ListaEstudante *listaEstudantes = NULL;

Estudante* novoEstudante(char nome[N]) {
    Estudante *novo = (Estudante*)malloc(sizeof(Estudante));

    strcpy(novo->nome, nome);
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

Turma* novaTurma(int codigoTurma) {
    Turma *novo = (Turma*)malloc(sizeof(Turma));

    novo->codigo = codigoTurma;
    novo->estudantes = NULL;
    novo->prox = NULL;
    novo->quantidadeEstudantes = 0;

    return novo;
}

void inserirTurma(int codigoTurma) {
    Turma *novo = novaTurma(codigoTurma);

    if (turmas == NULL) {
        turmas = novo;
    }
    else if (codigoTurma < turmas->codigo) {
        novo->prox = turmas;
        turmas = novo;
    }
    else {
        Turma *ant = turmas;
        Turma *aux = turmas->prox;
    
        while (aux != NULL && aux->codigo < codigoTurma) {
            ant = aux;
            aux = aux->prox;
        }
    
        if (ant->codigo == codigoTurma || (aux != NULL && aux->codigo == codigoTurma)) {
            printf("Erro: turma %d ja cadastrada!\n", codigoTurma);
            free(novo);
            return;
        }
    
        ant->prox = novo;
        novo->prox = aux;
    
    }
    
    printf("Turma '%d' cadastrada com sucesso!\n", codigoTurma);
}

Estudante* inserirEstudanteRecursivo(Estudante* estudantes, char nome[N]) {
    if (estudantes == NULL) {
        Estudante *novo = novoEstudante(nome);
        return novo;
    }

    if (strcmp(nome, estudantes->nome) < 0) {
        estudantes->esq = inserirEstudanteRecursivo(estudantes->esq, nome);
    }
    else if (strcmp(nome, estudantes->nome) > 0) {
        estudantes->dir = inserirEstudanteRecursivo(estudantes->dir, nome);
    }
    else {
        printf("Erro: nome '%s' ja existe nesta turma!\n", nome);
        return NULL;
    }

    return estudantes;
}

void inserirEstudante(int codigoTurma, char nome[N]) {
    Turma *aux = turmas;
    
    while(aux != NULL && aux->codigo != codigoTurma) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Turma nao encontrada!\n");
        return;
    }

    Estudante* arvore = inserirEstudanteRecursivo(aux->estudantes, nome);

    if (arvore != NULL) {
        aux->estudantes = arvore;
        (aux->quantidadeEstudantes)++;
    }
}

void inserirListaEstudante(char nome[N], int codigoTurma) {
    ListaEstudante *novo = (ListaEstudante*)malloc(sizeof(ListaEstudante));
    strcpy(novo->nome, nome);

    novo->turma = codigoTurma;
    novo->prox = NULL;

    if (listaEstudantes == NULL || strcmp(nome, listaEstudantes->nome) < 0) {
        novo->prox = listaEstudantes;
        listaEstudantes = novo;
        return;
    }

    ListaEstudante *ant = listaEstudantes;
    ListaEstudante *aux = listaEstudantes->prox;

    while (aux != NULL && strcmp(aux->nome, nome) < 0) {
        ant = aux;
        aux = aux->prox;
    }

    ant->prox = novo;
    novo->prox = aux;
}

void centralEstudanteAlfabetico(Estudante* a) {
    if (a != NULL) {
        centralEstudanteAlfabetico(a->esq);
        printf("- %s \n", a->nome);
        centralEstudanteAlfabetico(a->dir);
    }
}

void centralEstudanteInverso(Estudante* a) {
    if (a != NULL) {
        centralEstudanteInverso(a->dir);
        printf("- %s \n", a->nome);
        centralEstudanteInverso(a->esq);
    }
}

void preencherListaEstudantes(Estudante *a, int codigoTurma) {
    if (a != NULL) {
        preencherListaEstudantes(a->esq, codigoTurma);
        inserirListaEstudante(a->nome, codigoTurma);
        preencherListaEstudantes(a->dir, codigoTurma);
    }
}

void preFixadoEstudante(Estudante* a) {
    if (a != NULL) {
        printf("- %s \n", a->nome);
        preFixadoEstudante(a->esq);
        preFixadoEstudante(a->dir);
    }
}

void exibeTurma(int codigoTurma, int ordenacao) {
    Turma *auxT = turmas;
    
    while(auxT != NULL && auxT->codigo != codigoTurma) {        
        auxT = auxT->prox;
    }

    if (auxT != NULL) {
        if (ordenacao == 1) {
            printf("\n\n--- Lista de Estudantes da Turma %d - Ordem Alfabetica ---\n", auxT->codigo);
            centralEstudanteAlfabetico(auxT->estudantes);    
        }
        else if (ordenacao == 2) {
            printf("\n\n--- Lista de Estudantes da Turma %d - Ordem Alfabetica Inversa ---\n", auxT->codigo);
            centralEstudanteInverso(auxT->estudantes);   
        }
    }
    else {
        printf("Turma %d nao encontrada\n", codigoTurma);
    }
    printf("----------------------------------------------------------------------------\n");
}

void exibeTurmaPre(int codigoTurma) {
    Turma *auxT = turmas;
    
    while(auxT != NULL && auxT->codigo != codigoTurma) {        
        auxT = auxT->prox;
    }

    if (auxT != NULL) {
        printf("\n\n--- Lista de Estudantes da Turma %d - Pre Fixado ---\n", auxT->codigo);
    
        preFixadoEstudante(auxT->estudantes);    
    }
    else {
        printf("Turma %d nao encontrada\n", codigoTurma);
    }
    printf("----------------------------------------------------------------------------\n");
}

void contaEstudantes() {
    Turma *auxT = turmas;
    
    printf("\n\n--- Contagem de Estudantes por Turma ---\n");
    while(auxT != NULL) {
        printf("Codigo: %2d - Total de Estudantes: %d\n", auxT->codigo, auxT->quantidadeEstudantes);

        auxT = auxT->prox;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

void maiorTurma() {
    Turma *auxT = turmas;
    int maior = turmas->quantidadeEstudantes;
    
    printf("\n\n--- Turma com Mais Estudantes ---\n");
    while(auxT != NULL) {
        if (auxT->quantidadeEstudantes > maior) {
            maior = auxT->quantidadeEstudantes;
        }
        
        auxT = auxT->prox;
    }

    auxT = turmas;

    while(auxT != NULL) {
        if (auxT->quantidadeEstudantes == maior) {
            printf("Maior turma: Cod: %2d Total de Estudantes: %d\n", auxT->codigo, auxT->quantidadeEstudantes);
        }
        
        auxT = auxT->prox;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

void menorTurma() {
    Turma *auxT = turmas;
    int menor = turmas->quantidadeEstudantes;
    
    printf("\n\n--- Turma com Menos Estudantes ---\n");
    while(auxT != NULL) {
        if (auxT->quantidadeEstudantes < menor) {
            menor = auxT->quantidadeEstudantes;
        }
        
        auxT = auxT->prox;
    }

    auxT = turmas;

    while(auxT != NULL) {
        if (auxT->quantidadeEstudantes == menor) {
            printf("Menor turma: Cod: %2d Total de Estudantes: %d\n", auxT->codigo, auxT->quantidadeEstudantes);
        }
        
        auxT = auxT->prox;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

void exibeTodosEstudantes() {
    listaEstudantes = NULL;
    Turma *auxT = turmas;

    while (auxT != NULL) {
        preencherListaEstudantes(auxT->estudantes, auxT->codigo);
        auxT = auxT->prox;
    }

    printf("\n\n--- TODOS OS ESTUDANTES (ALFABETICO) ---\n");

    ListaEstudante *auxLE = listaEstudantes;

    while (auxLE != NULL) {
        printf("(Turma %d) %s\n", auxLE->turma, auxLE->nome);
        auxLE = auxLE->prox;
    }
}

void nomesRepetidos() {
    listaEstudantes = NULL;
    Turma *auxT = turmas;

    while (auxT != NULL) {
        preencherListaEstudantes(auxT->estudantes, auxT->codigo);
        auxT = auxT->prox;
    }

    printf("\n--- NOMES REPETIDOS ---\n");

    ListaEstudante *auxLE = listaEstudantes;

    while (auxLE != NULL && auxLE->prox != NULL) {
        if (strcmp(auxLE->nome, auxLE->prox->nome) == 0) {
            printf("%s\n", auxLE->nome);

            while (auxLE->prox != NULL && strcmp(auxLE->nome, auxLE->prox->nome) == 0) {
                auxLE = auxLE->prox;
            }
        }
        auxLE = auxLE->prox;
    }
}

int main() {
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

    //exibeTurma(103, 1);
    //exibeTurma(103, 2);
    //exibeTurmaPre(103);

    contaEstudantes();

    menorTurma();
    maiorTurma();

    //exibeTodosEstudantes();
    //nomesRepetidos();
}