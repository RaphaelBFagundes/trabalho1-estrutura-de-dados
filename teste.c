#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <PILHAEFILA.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
}data;

typedef struct pet{
    int id;
    char nome[50];
    char epecie[30];
    int idade;
    int prioridade;
    data nasc;
    pet *prox;
}pet;


void inserirPet(pet *p, fila *fila0, fila *fila1, char *nome, char *epecie, int id, int idade, int prioridade){


}

void atenderPet(fila *fila0, fila *fila1, pet *p){
    
}

int main() {
    srand(time(NULL));
    fila* fila0 = criafila();
    fila* fila1 = criafila();

    return 0;
}