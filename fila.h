#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Pet
{
    int ID;
    char Nome[51];
    char Especie[31];
    int Idade;
    Data DataNascimento;
    int Prioridade;
}Pet;

typedef struct no
{
    Pet info;
    struct no *prox;
} no;

typedef struct Fila
{
    no * ini;
    no * fim;
} Fila;

int vaziaFila (Fila* f)
{
    if (f->ini==NULL){
        return 1;
    }
    return 0;
}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

no* ins_fim (no *fim, Pet pet)
{
    no *novoPet = (no*)malloc(sizeof(no));
    
    if(novoPet != NULL){
        novoPet->info = pet;
        novoPet->prox = NULL;
        
        if(fim != NULL){
            fim->prox = novoPet;
        }
    }
    return novoPet;
}

void insereFila (Fila* f, Pet pet)
{
    no* novoPet = ins_fim(f->fim, pet);
    if(novoPet != NULL){
        f->fim = novoPet;

        if(f->ini == NULL){
            f->ini = f->fim;
        }
    }
}

no* retira_ini (no* ini)
{
    no* p = ini->prox;
    free(ini);
    return p;
}

Pet retiraFila (Fila* f)
{
    Pet removido;

    if(vaziaFila(f)){
        printf("\nFila Vazia!\n");
        exit(1);
    }

    removido = f->ini->info;
    f->ini = retira_ini(f->ini);
    
    if(f->ini == NULL){
        f->fim = NULL;
    }
    return removido;
}

void liberaFila (Fila* f)
{
    no* q = f->ini;

    while (q!=NULL)
    {
        no* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

#endif