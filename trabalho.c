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

Estudante *estudantes;
HeaderEstudante *headerestudante;

void insereEstudante(char nome[N], char curso[N]) {
    Estudante *novo, *aux = estudantes, *ant = estudantes;

    novo = (Estudante*)malloc(sizeof(Estudante));
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    
    if(estudantes==NULL) {
        novo->codigo = 0;
        estudantes = novo;
        headerestudante->ultimoInserido = novo;
    } else if(strcmp(novo->nome , estudantes->nome) < 0) {
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

void removeEstudante(int codigo, char nome[N]) {
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

int main() {
    estudantes = NULL;
    headerestudante = (HeaderEstudante*) malloc(sizeof(HeaderEstudante));
    headerestudante->ultimoInserido = NULL;

    insereEstudante("Miguel", "Engenharia de Sotware");
    insereEstudante("Ana", "Nutricao");
    insereEstudante("Pedro", "Administracao");
    insereEstudante("Gustavo", "Gastronomia");
    insereEstudante("Douglas", "Medicina");

    consultarTodosEstudantes();
    
    removeEstudante(2, "");
    consultarTodosEstudantes();

    return 0;
}
