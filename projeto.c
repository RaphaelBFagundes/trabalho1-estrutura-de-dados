#include <stdio.h>
#include <stdlib.h>
#include <PILHAEFILA.h>
#include <time.h>


typedef struct data{
    int dia, mes, ano;
} data;

typedef struct pet{
    int id;                
    char nome[51];          
    char especie[31];       
    int idade;
    data nasc;
    int prioridade;         
    int atendido;          
} pet;
typedef struct filapet{
    pet *inicio;
    pet *fim;
}filapet;
filapet* criafilapet ()
{
    filapet* f = malloc(sizeof(filapet));
    f->ini = f->fim = NULL;
    return f;
}
void inserepet(filapet *f)
{
    pet *novo = malloc(sizeof(pet));
    novo -> id = rand() % 999 + 1;
    printf("digite o nome:");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    printf("digite a especie");
    fgets(novo->especie, sizeof(novo->especie), stdin);
    printf("digite a idade:");
    scanf("%d",&novo->idade);



    
    
   
}