#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 30

typedef struct atividade {
    char nome[N];
    char local[N];
    int quantidade;
    struct inscrito *inscritos;
    struct atividade *prox;
} Atividade;

typedef struct estudante {
    int codigo;
    char nome[N];
    char curso[N];
    struct estudante *prox;
    Atividade *atividade;
} Estudante;

typedef struct inscrito {
    Estudante *estudante;
    struct inscrito *prox;
} Inscrito;

typedef struct headerestudante {
    Estudante *ultimoInserido;
    Estudante *estudantes;
} HeaderEstudante;

typedef struct headeragenda {
    char data[N];
    char horario[N];
    struct atividade *atividades;
} HeaderAgenda;

HeaderAgenda headeragenda;
HeaderEstudante headerestudante;

void inicializar() {
    headerestudante.ultimoInserido = NULL;
    headerestudante.estudantes = NULL;

    strcpy(headeragenda.data, "25/09/2025");
    strcpy(headeragenda.horario, "10h");
    headeragenda.atividades = NULL;
}

void inserirEstudante(char nome[N], char curso[N]) {
    Estudante *novo;

    novo = (Estudante*)malloc(sizeof(Estudante));
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    novo->atividade = NULL;
    
    if(headerestudante.estudantes==NULL) {
        novo->codigo = 0;
        headerestudante.estudantes = novo;
        headerestudante.ultimoInserido = novo;
    } else if(strcmp(novo->nome, headerestudante.estudantes->nome) <= 0) {
        novo->prox = headerestudante.estudantes;
        novo->codigo = headerestudante.ultimoInserido->codigo + 1;
        headerestudante.estudantes = novo;
        headerestudante.ultimoInserido = novo;
    } else {
        Estudante *aux = headerestudante.estudantes, *ant = headerestudante.estudantes;

        while (aux != NULL && strcmp(aux->nome, novo->nome) < 0 ) {
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = novo;
        novo->prox = aux;
        novo->codigo = headerestudante.ultimoInserido->codigo + 1;
        headerestudante.ultimoInserido = novo;
    }
}

void removerEstudante(int codigo, char nome[N]) {
    if(headerestudante.estudantes == NULL) { //Lista vazia
        return;
    }

    if(headerestudante.estudantes->prox == NULL && (headerestudante.estudantes->codigo == codigo || strcmp(headerestudante.estudantes->nome, nome) == 0)) { //Primeiro e Único
        free(headerestudante.estudantes);
        headerestudante.estudantes = NULL;
    } else if(headerestudante.estudantes->codigo == codigo || strcmp(headerestudante.estudantes->nome, nome) == 0) { //Primeiro, mas não único
        Estudante *aux=headerestudante.estudantes;
        headerestudante.estudantes = headerestudante.estudantes->prox;
        free(aux);
    } else { //Remove Meio ou Último
        Estudante *aux=headerestudante.estudantes, *ant=headerestudante.estudantes;
        while (aux != NULL && strcmp(aux->nome, nome) != 0 && aux->codigo != codigo) { 
            ant = aux;
            aux = aux->prox;
        }
        if (aux != NULL) {
            ant->prox = aux->prox;
            free(aux);
        }
    }
}

void consultarTodosEstudantes() {
    Estudante *aux = headerestudante.estudantes;
    
    printf("\nLista de Estudantes:\n");
    while(aux != NULL) {
        printf("Cod: %2d | Nome: %30s | Curso: %30s\n", aux->codigo, aux->nome, aux->curso);
        aux = aux->prox;
    }
}

void inserirAtividade(char nome[N], char local[N]) {
    Atividade *novo;

    novo = (Atividade*)malloc(sizeof(Atividade));
    strcpy(novo->nome, nome);
    strcpy(novo->local, local);
    novo->quantidade = 0;
    
    if(headeragenda.atividades==NULL) {
        novo->prox = NULL;
    } else {
        novo->prox = headeragenda.atividades;
    }
    headeragenda.atividades = novo;
}

void removerAtividade(char nome[N]) {
    if(headeragenda.atividades == NULL) { //Lista vazia
        return;
    }
    if(headeragenda.atividades->prox == NULL && strcmp(headeragenda.atividades->nome, nome) == 0) { //Primeiro e Único
        free(headeragenda.atividades);
        headeragenda.atividades = NULL;
    } else if(strcmp(headeragenda.atividades->nome, nome) == 0) { //Primeiro, mas não único
        Atividade *aux=headeragenda.atividades;
        headeragenda.atividades = headeragenda.atividades->prox;
        free(aux);
    } else { //Remove Meio ou Último
        Atividade *aux=headeragenda.atividades, *ant=headeragenda.atividades;
        while (aux != NULL && strcmp(aux->nome, nome) != 0) { 
            ant = aux;
            aux = aux->prox;
        }
        if (aux != NULL) {
            ant->prox = aux->prox;
            free(aux);
        }
    }
}

void consultarTodasAtividades() {
    Atividade *aux = headeragenda.atividades;
    
    printf("\nLista de Atividades:\n");
    while(aux != NULL) {
        printf("Nome: %30s | Local: %30s\n", aux->nome, aux->local);
        aux = aux->prox;
    }
}

void consultarAtividade(char nome[N]) {
    Atividade *aux = headeragenda.atividades;
    
    printf("\nAtividade:\n");
    while(aux != NULL) {
        if(strcmp(aux->nome, nome) == 0) {
            printf("Nome: %30s | Local: %30s\n", aux->nome, aux->local);
            break;
        }
        aux = aux->prox;
    }
}

void inserirParticipante(char nomeAtividade[N], int codigoEstudante) {
    Estudante *auxE = headerestudante.estudantes;
    Atividade *auxA = headeragenda.atividades;
    int existeEstudante = 0, existeAtividade = 0;

    while(auxE != NULL) {
        if(auxE->codigo == codigoEstudante) {
            existeEstudante = 1;
            break;
        }
        auxE = auxE->prox;
    }
    while(auxA != NULL) {
        if(strcmp(auxA->nome, nomeAtividade) == 0) {
            existeAtividade = 1;
            break;
        }
        auxA = auxA->prox;
    }

    if(existeEstudante && existeAtividade && auxE->atividade == NULL) {
        Inscrito *novo = (Inscrito*)malloc(sizeof(Inscrito));
        novo->estudante = auxE;
        novo->prox = auxA->inscritos;
        auxA->inscritos = novo;
        (auxA->quantidade)++;

        auxE->atividade = auxA;

        printf("\nParticipante '%s' inserido(a) com sucesso na atividade '%s'!\n", auxE->nome, auxA->nome);
    }
    else if (auxE != NULL && auxE->atividade != NULL && (existeEstudante || existeAtividade)) {
        printf("\nErro: estudante %s ja inscrito na atividade %s!\n", auxE->nome, auxA->nome);
    }
    else {
        printf("\nErro: estudante %d ou atividade nao encontrados.\n", codigoEstudante);
    }
}

void consultaQuantidades() {
    Atividade *aux = headeragenda.atividades;

    printf("\n-------------------------\n");
    while(aux != NULL) {
        printf("Atividade: %s Quantidade de inscritos: %d\n", aux->nome, aux->quantidade);
        aux = aux->prox;
    }
    printf("\n-------------------------\n");
}

void consultarParticipantes(char nome[N]) {    
    Atividade *auxA = headeragenda.atividades;

    while (auxA != NULL && strcmp(auxA->nome, nome) != 0)
    {
       auxA = auxA->prox;
    }

    if (auxA != NULL) {
        printf("\n-------------------------\n");
        printf("Atividade: %s\n", auxA->nome);
        printf("Local: %s\n", auxA->local);

        Inscrito *auxE = auxA->inscritos;

        while (auxE != NULL) 
        {
            printf("Cod: %2d | Nome: %30s | Curso: %30s\n", auxE->estudante->codigo, auxE->estudante->nome, auxE->estudante->curso);
            auxE = auxE->prox;
        }
        
        printf("\n-------------------------\n");
    }
}

void removerParticipante(char nome[N]) {
    Estudante *auxE = headerestudante.estudantes;

    while (auxE != NULL && strcmp(auxE->nome, nome) != 0)
    {
        auxE = auxE->prox;
    }

    if (auxE->atividade == NULL) {
        printf("Nao ha inscritos com este nome...");
        return;
    }

    Inscrito *auxI = auxE->atividade->inscritos, *antI = NULL;

    while (auxI != NULL && strcmp(auxI->estudante->nome, nome) != 0)
    {
        antI = auxI;
        auxI = auxI->prox;
    }
    
    if (antI != NULL && auxI != NULL) {
        antI->prox = auxI->prox;
    }
    else if (antI != NULL) {
        antI->prox = auxI;
    }
    else {
        auxE->atividade->inscritos = NULL;
    }

    free(auxI);

}

void consultarInscritos() {}

void consultarAtividadesPorCurso(char nome[N]) {}

int main() {

    inicializar();

    inserirEstudante("Ana", "Nutricao");
    inserirEstudante("Miguel", "Engenharia de Sotware");
    inserirEstudante("Pedro", "Administracao");
    inserirEstudante("Gustavo", "Gastronomia");
    inserirEstudante("Douglas", "Medicina");

    consultarTodosEstudantes();
    
    removerEstudante(2, "");
    consultarTodosEstudantes();

    inserirAtividade("Jogos de Cartas", "Sala de Jogos");
    inserirAtividade("Livros de Ficcao", "Biblioteca");
    inserirAtividade("Tenis de Mesa", "Ginasio");
    inserirAtividade("Esports", "www.site.com");

    // consultarTodasAtividades();

    // removerAtividade("Nome4");
    // consultarTodasAtividades();

    // consultarAtividade("Nome3");

    // inserirParticipante("Esports", 0);
    // inserirParticipante("Livros de Ficcao", 0);
    // inserirParticipante("Livros de Ficcao", 3);
    // inserirParticipante("Jogos de Cartas", 1);
    inserirParticipante("Esports", 2);

    inserirParticipante("Esports", 4);
    inserirParticipante("Jogos de Cartas", 7);
    
    
    consultaQuantidades();
    consultarParticipantes("Jogos de Cartas");

    inserirParticipante("Livros de Ficcao", 1);
    removerParticipante("Miguel");

    return 0;
}
