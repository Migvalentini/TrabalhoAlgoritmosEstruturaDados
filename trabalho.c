#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 30
struct estudante {
    int codigo;
    char nome[N];
    char curso[N];
    struct estudante *prox;
}; typedef struct estudante Estudante;

struct inscrito {
    Estudante *estudante;
    struct inscrito *prox;
}; typedef struct inscrito Inscrito;

struct headerestudante {
    struct estudante *ultimoInserido;
}; typedef struct headerestudante HeaderEstudante;

struct atividade {
    char nome[N];
    char local[N];
    struct inscrito *estudantes;
    struct atividade *prox;
}; typedef struct atividade Atividade;

struct headeragenda {
    char data[N];
    char horario[N];
    struct atividade *atividades;
}; typedef struct headeragenda HeaderAgenda;

Estudante *estudantes;
HeaderEstudante *headerestudante;
HeaderAgenda *headeragenda;

void inserirEstudante(char nome[N], char curso[N]) {
    Estudante *novo, *aux = estudantes, *ant = estudantes;

    novo = (Estudante*)malloc(sizeof(Estudante));
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    
    if(estudantes==NULL) {
        novo->codigo = 0;
        estudantes = novo;
        headerestudante->ultimoInserido = novo;
    } else if(strcmp(novo->nome, estudantes->nome) < 0) {
        novo->prox = estudantes;
        novo->codigo = headerestudante->ultimoInserido->codigo + 1;
        estudantes = novo;
        headerestudante->ultimoInserido = novo;
    } else {
        while (aux != NULL && strcmp(aux->nome, novo->nome) < 0 ){
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = novo;
        novo->prox = aux;
        novo->codigo = headerestudante->ultimoInserido->codigo + 1;
        headerestudante->ultimoInserido = novo;
    }
}

void removerEstudante(int codigo, char nome[N]) {
    if(estudantes == NULL) { //Lista vazia
        return;
    }

    if(estudantes->prox == NULL && (estudantes->codigo == codigo || strcmp(estudantes->nome, nome) == 0)) { //Primeiro e Único
        free(estudantes);
        estudantes = NULL;
    } else if(estudantes->codigo == codigo || strcmp(estudantes->nome, nome) == 0) { //Primeiro, mas não único
        Estudante *aux=estudantes;
        estudantes = estudantes->prox;
        free(aux);
    } else { //Remove Meio ou Último
        Estudante *aux=estudantes, *ant=estudantes;
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
    Estudante *aux = estudantes;
    
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
    
    if(headeragenda->atividades==NULL) {
        novo->prox = NULL;
    } else {
        novo->prox = headeragenda->atividades;
    }
    headeragenda->atividades = novo;
}

void removerAtividade(char nome[N]) {
    if(headeragenda->atividades == NULL) { //Lista vazia
        return;
    }
    if(headeragenda->atividades->prox == NULL && strcmp(headeragenda->atividades->nome, nome) == 0) { //Primeiro e Único
        free(headeragenda->atividades);
        headeragenda->atividades = NULL;
    } else if(strcmp(headeragenda->atividades->nome, nome) == 0) { //Primeiro, mas não único
        Atividade *aux=headeragenda->atividades;
        headeragenda->atividades = headeragenda->atividades->prox;
        free(aux);
    } else { //Remove Meio ou Último
        Atividade *aux=headeragenda->atividades, *ant=headeragenda->atividades;
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
    Atividade *aux = headeragenda->atividades;
    
    printf("\nLista de Atividades:\n");
    while(aux != NULL) {
        printf("Nome: %30s | Local: %30s\n", aux->nome, aux->local);
        aux = aux->prox;
    }
}

void consultarAtividade(char nome[N]) {
    Atividade *aux = headeragenda->atividades;
    
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
    Estudante *auxE = estudantes;
    Atividade *auxA = headeragenda->atividades;
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
    
    if(existeEstudante && existeAtividade) {
        Inscrito *novo = (Inscrito*)malloc(sizeof(Inscrito));
        novo->estudante = auxE;
        novo->prox = auxA->estudantes;
        auxA->estudantes = novo;

        printf("\nParticipante '%s' inserido(a) com sucesso na atividade '%s'!\n", auxE->nome, auxA->nome);
    } else {
        printf("\nErro: estudante ou atividade nao encontrados.\n");
    }
}

int main() {
    estudantes = NULL;
    headerestudante = (HeaderEstudante*) malloc(sizeof(HeaderEstudante));
    headerestudante->ultimoInserido = NULL;
    headeragenda = (HeaderAgenda*) malloc(sizeof(HeaderAgenda));
    strcpy(headeragenda->data, "25/09/2025");
    strcpy(headeragenda->horario, "10h");
    headeragenda->atividades = NULL;

    inserirEstudante("Miguel", "Engenharia de Sotware");
    inserirEstudante("Ana", "Nutricao");
    inserirEstudante("Pedro", "Administracao");
    inserirEstudante("Gustavo", "Gastronomia");
    inserirEstudante("Douglas", "Medicina");

    consultarTodosEstudantes();
    
    //removerEstudante(2, "");
    //consultarTodosEstudantes();

    inserirAtividade("Jogos de Cartas", "Sala de Jogos");
    inserirAtividade("Livros de Ficcao", "Biblioteca");
    inserirAtividade("Tenis de Mesa", "Ginasio");
    inserirAtividade("Esports", "www.site.com");

    consultarTodasAtividades();

    //removerAtividade("Nome4");
    //consultarTodasAtividades();

    //consultarAtividade("Nome3");

    inserirParticipante("Livros de Ficcao", 1);

    return 0;
}
