#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
    int info;
    struct no *prox;
}no;

typedef struct fila
{
    no * ini;
    no * fim;
} fila;

int vaziafila (fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}


fila* criafila ()
{
    fila* f = (fila*) malloc(sizeof(fila));
    f->ini = f->fim = NULL;
    return f;
}

no* ins_fim (no *fim, int A)
{
    no *p = (no*)malloc(sizeof(no));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void inserefila (fila* f, int v)
{
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

no* retira_ini (no* ini)
{
    no* p = ini->prox;
    free(ini);
    return p;
}

int retirafila (fila* f)
{
    int v;
    if (vaziafila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimefila (fila* f)
{
    no* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info);
    }
    printf("\n");
}


fila* liberafila (fila* f)
{
    no* q = f->ini;
    while (q!=NULL)
    {
        no* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

int contapar(fila *f)
{
    int cont = 0;
    if(f -> ini != NULL)
    {
        while (f -> ini !=NULL)
        {
            if(f -> ini -> info %2 == 0)
            {
                cont++;
            }
            f -> ini = f -> ini -> prox;
        }
    }
    return cont;
}


fila* apaga(fila *f, int num)
{
    fila *aux = criafila();
    if(f->ini != NULL)
    {
        while(f->ini != NULL)
        {
            if(f -> ini == num)
            {
                retirafila(f);
            }
            else
            {
                inserefila(aux,retirafila(f));
            }
        }
    }
    return aux;

}


fila* parimpar(fila *f, fila **par, fila **impar)
{
    fila *filaimpar = criafila();
    fila *filapar = criafila();
    for(;f -> ini != NULL; f -> ini = f -> ini -> prox)
    {
        if(f -> ini -> info %2 == 0)
        {
            inserefila(filapar, retirafila(f));
        }
        else
        {
            inserefila(filaimpar, retirafila(f));
        }
    }


}

typedef struct pilha
{
no *topo;
}pilha;



pilha* criapilha (void)
{
pilha *p = malloc(sizeof(pilha));
p->topo = NULL;
return p;
}



no* ins_ini (no* t, int a)
{
no* aux = (no*) malloc(sizeof(no));
aux->info = a;
aux->prox = t;
return aux;
}



void push (pilha* p, int v)
{
p->topo = ins_ini(p->topo,v);
}



no* ret_ini (no* aux)
{
no* p = aux->prox;
free(aux);
return p;
}


int pop (pilha *p)
{
int v;
if (p -> topo -> info == NULL)
{
printf("\n\n\t==> Pilha VAZIA, IMPOSSIVEL CONTINUAR.\b\n");
exit(1); /* aborta programa */
}
v = p->topo->info;
p->topo = ret_ini(p->topo);
return v;
}


int contapilha(pilha *p)
{
    int cont = 0;
    no *aux = p -> topo;
    while(aux != NULL)
    {
        aux = aux->prox;
        cont ++;
    }
    return cont;
}


pilha* invertepilha (pilha *recebida)
{
    pilha *pilhainv;
    pilhainv = criapilha();
    no *aux;
    if(recebida -> topo != NULL)
    {
        while(recebida -> topo != NULL)
        {
            aux = pop(recebida);
            push(pilhainv,aux);
        }

    }
    else
    {
        printf("\n\tpilha vazia");
    }
    return pilhainv;
}



void imprimepilha(pilha *p)
{
    no *aux = p -> topo;
    if(aux != NULL)
    {
        while(aux != NULL)
        {
            printf("%d",aux -> info);
            aux = aux -> prox;
        }
    }
}


pilha* liberapilha(pilha *p)
{
    pilha *aux;
    while(p -> topo != NULL)
    {
        aux = p -> topo;
        free(aux);
        p -> topo = p -> topo -> prox;
    }
    return p;
}

pilha* digitos(int num)
{
    pilha *aux;
    aux = criapilha();
    do
    {
        push(aux, num%10);
        num = num/10;
    }while(num > 0);
    pilha *nova = invertepilha(aux);

    return nova;
}
pilha* remover(pilha *recebida, int num)
{
    pilha *aux = criapilha();
    if (recebida != NULL)
    {
        while (recebida -> topo != NULL)
        {
            if(recebida -> topo -> info == num)
            {
                pop(recebida);
            }
            else
            {
                push(aux,pop(recebida));
            }
        }
        while(aux -> topo != NULL)
        {
            push(recebida,pop(aux));
        }
    }
    return recebida;
}
int compara(pilha *p1,pilha *p2)
{
    int i = contapilha(p1);
    int j = contapilha(p2);
    if (i==j)
    {
        return 0;
    }
    else if (i>j)
    {
        return 1;
    }
    return 2;
}
void invertefila(fila *f)
{
    pilha *p = criapilha();
    if(f -> ini != NULL)
    {
        while(f -> ini !=NULL)
        {
            push(p, retirafila(f));
        }
        while(p -> topo != NULL)
        {
            inserefila(f,pop(p));
        }
        liberapilha(p);
    }
}
