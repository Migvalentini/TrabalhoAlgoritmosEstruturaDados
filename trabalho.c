//- INSERE TURMA: permite a inserção de uma turma na lista de turmas, de forma ordenada. Não pode ter número de turma repetido.
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

void inserirTurma(int codigo) {
    Turma *novo = (Turma*) malloc(sizeof(Turma));

    novo->codigo = codigo;
    novo->quantidadeEstudantes = 0;
    novo->estudantes = NULL;
    novo->prox = NULL;

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
    
        if ((ant != NULL && ant->codigo == codigo) ||
            (aux != NULL && aux->codigo == codigo)) {
            printf("Erro: turma %d já cadastrada!\n", codigo);
            free(novo);
            return;
        }
    
        ant->prox = novo;
        novo->prox = aux;
    
    }
    
    printf("Turma '%d' cadastrada com sucesso!\n", codigo);
}

void consultarTodasTurmas() {
    Turma *aux = turmas;

    printf("\n\n--- Lista de Turmas ---\n");
    while(aux != NULL) {
        printf("Cod: %2d\n", aux->codigo);
        aux = aux->prox;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

void inicializar () {
    turmas = NULL;
}

int main() {
    inicializar();

    inserirTurma(100);
    inserirTurma(300);
    inserirTurma(200);
    inserirTurma(400);

    consultarTodasTurmas();
}