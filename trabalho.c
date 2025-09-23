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

struct headerestudante {
    struct estudante *ultimoInserido;
}; typedef struct headerestudante HeaderEstudante;

struct atividade {
    char nome[N];
    char link[N];
    struct estudante *estudantes;
    struct atividade *prox;
}; typedef struct atividade Atividade;

Estudante *estudantes;
Atividade *atividades;
HeaderEstudante *headerestudante;

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

void inserirAtividade(char nome[N], char link[N]) {
    Atividade *novo;

    novo = (Atividade*)malloc(sizeof(Atividade));
    strcpy(novo->nome, nome);
    strcpy(novo->link, link);
    
    if(atividades==NULL) {
        novo->prox = NULL;
    } else {
        novo->prox = atividades;
    }
    atividades = novo;
}

void removerAtividade(char nome[N]) {
    if(atividades == NULL) { //Lista vazia
        return;
    }
    if(atividades->prox == NULL && strcmp(atividades->nome, nome) == 0) { //Primeiro e Único
        free(atividades);
        atividades = NULL;
    } else if(strcmp(atividades->nome, nome) == 0) { //Primeiro, mas não único
        Atividade *aux=atividades;
        atividades = atividades->prox;
        free(aux);
    } else { //Remove Meio ou Último
        Atividade *aux=atividades, *ant=atividades;
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
    Atividade *aux = atividades;
    
    printf("\nLista de Atividades:\n");
    while(aux != NULL) {
        printf("Nome: %30s | Link: %30s\n", aux->nome, aux->link);
        aux = aux->prox;
    }
}

void consultarAtividade(char nome[N]) {
    Atividade *aux = atividades;
    
    printf("\nAtividade:\n");
    while(aux != NULL) {
        if(strcmp(aux->nome, nome) == 0) {
            printf("Nome: %30s | Link: %30s\n", aux->nome, aux->link);
            break;
        }
        aux = aux->prox;
    }
}

int main() {
    estudantes = NULL;
    atividades = NULL;
    headerestudante = (HeaderEstudante*) malloc(sizeof(HeaderEstudante));
    headerestudante->ultimoInserido = NULL;

    inserirEstudante("Miguel", "Engenharia de Sotware");
    inserirEstudante("Ana", "Nutricao");
    inserirEstudante("Pedro", "Administracao");
    inserirEstudante("Gustavo", "Gastronomia");
    inserirEstudante("Douglas", "Medicina");

    consultarTodosEstudantes();
    
    //removerEstudante(2, "");
    //consultarTodosEstudantes();

    inserirAtividade("Nome1", "Link1");
    inserirAtividade("Nome2", "Link2");
    inserirAtividade("Nome3", "Link3");
    inserirAtividade("Nome4", "Link4");

    consultarTodasAtividades();

    //removerAtividade("Nome4");
    //consultarTodasAtividades();

    consultarAtividade("Nome3");

    return 0;
}
