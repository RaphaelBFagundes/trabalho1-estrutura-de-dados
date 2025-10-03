#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Pet {
    int ID;
    char Nome[51];
    char Especie[31];
    int Idade;
    Data DataNascimento;
    int Prioridade; // 0 para Emergência, 1 para Normal
} Pet;

typedef struct PetNo {
    Pet* petInfo;
    struct PetNo* prox;
} PetNo;

typedef struct PetFila {
    PetNo* ini;
    PetNo* fim;
} PetFila;

PetFila* criaFila() {
    PetFila* f = (PetFila*)malloc(sizeof(PetFila));
    f->ini = f->fim = NULL;
    return f;
}

int filaVazia(PetFila* f) {
    return (f->ini == NULL);
}

void insereFila(PetFila* f, Pet* p) {
    PetNo* novo = (PetNo*)malloc(sizeof(PetNo));
    novo->petInfo = p;
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    }
    f->fim = novo;

    if (f->ini == NULL) {
        f->ini = f->fim;
    }
}

Pet* retiraFila(PetFila* f) {
    if (filaVazia(f)) {
        return NULL;
    }
    PetNo* temp = f->ini;
    Pet* petRemovido = temp->petInfo;
    f->ini = temp->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free(temp);
    return petRemovido;
}

int idExiste(int id, PetFila* emergencia, PetFila* normal, PetFila* atendidos) {
    PetNo* atual;
    for (atual = emergencia->ini; atual != NULL; atual = atual->prox)
        if (atual->petInfo->ID == id) return 1;

    for (atual = normal->ini; atual != NULL; atual = atual->prox) 
        if (atual->petInfo->ID == id) return 1;

    for (atual = atendidos->ini; atual != NULL; atual = atual->prox) 
        if (atual->petInfo->ID == id) return 1;

    return 0;
}

int gerarIDUnico(PetFila* emergencia, PetFila* normal, PetFila* atendidos) {
    int id;
    do {
        id = 100 + rand() % 900;
    } while (idExiste(id, emergencia, normal, atendidos));
    return id;
}

void inserirPet(PetFila* filaEmergencia, PetFila* filaNormal, PetFila* filaAtendidos) {
    Pet* novoPet = (Pet*)malloc(sizeof(Pet));

    novoPet->ID = gerarIDUnico(filaEmergencia, filaNormal, filaAtendidos);
    printf("\n--- Cadastro de Novo Pet (ID Gerado: %d) ---\n", novoPet->ID);

    printf("Nome do Pet: ");
    scanf(" %50[^\n]", novoPet->Nome);
    printf("Especie (ex: Cachorro, Gato): ");
    scanf(" %30[^\n]", novoPet->Especie);
    printf("Idade: ");
    scanf("%d", &novoPet->Idade);
    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &novoPet->DataNascimento.dia, &novoPet->DataNascimento.mes, &novoPet->DataNascimento.ano);

    do {
        printf("Prioridade (0 - Emergencia, 1 - Normal): ");
        scanf("%d", &novoPet->Prioridade);
    } while (novoPet->Prioridade != 0 && novoPet->Prioridade != 1);

    if (novoPet->Prioridade == 0) {
        insereFila(filaEmergencia, novoPet);
        printf("\n=> Pet '%s' inserido na fila de EMERGENCIA!\n", novoPet->Nome);
    } else {
        insereFila(filaNormal, novoPet);
        printf("\n=> Pet '%s' inserido na fila NORMAL!\n", novoPet->Nome);
    }
}

void mostrarProximo(PetFila* filaEmergencia, PetFila* filaNormal) {
     printf("\n--- Proximo a Ser Atendido ---\n");
    if (!filaVazia(filaEmergencia)) {
        printf("Nome: %s\n", filaEmergencia->ini->petInfo->Nome);
        printf("Especie: %s\n", filaEmergencia->ini->petInfo->Especie);
        printf("Tipo de Atendimento: Emergencia\n");
    } else if (!filaVazia(filaNormal)) {
        printf("Nome: %s\n", filaNormal->ini->petInfo->Nome);
        printf("Especie: %s\n", filaNormal->ini->petInfo->Especie);
        printf("Tipo de Atendimento: Normal\n");
    } else {
        printf("Nao ha pets nas filas para atender.\n");
    }
}

void atenderPet(PetFila* filaEmergencia, PetFila* filaNormal, PetFila* filaAtendidos) {
    Pet* petAtendido = NULL;
    int tipoAtendimento = -1;

    if (!filaVazia(filaEmergencia)) {
        petAtendido = retiraFila(filaEmergencia);
        tipoAtendimento = 0;
    } else if (!filaVazia(filaNormal)) {
        petAtendido = retiraFila(filaNormal);
        tipoAtendimento = 1;
    }

    if (petAtendido != NULL) {
        printf("\n--- Atendendo Pet Agora ---\n");

        char tipoAtendimento[11];

        if (tipoAtendimento == 0) {
            strcpy(tipoAtendimento, "Emergencia");    
        } else {
            if (tipoAtendimento == 1) {
            strcpy(tipoAtendimento, "Normal");
        }

        }
        printf("ID: %d | Nome: %s | Tipo: %s\n",
            petAtendido->ID,
            petAtendido->Nome,
            tipoAtendimento);

        insereFila(filaAtendidos, petAtendido);
        printf("=> Pet atendido e movido para a lista de historico.\n");

        mostrarProximo(filaEmergencia, filaNormal);

    } else {
        printf("\nNao ha pets nas filas para atender.\n");
    }
}

void imprimirRelatorioFilas(PetFila* emergencia, PetFila* normal) {
    PetNo* atual;
    printf("\n--- Relatorio de Pets nas Filas ---\n");

    printf("\n--- FILA DE EMERGENCIA ---\n");
    if (filaVazia(emergencia)) {
        printf("Fila de emergencia vazia.\n");
    } else {
        for (atual = emergencia->ini; atual != NULL; atual = atual->prox) {
            printf("ID: %d | Nome: %s | Especie: %s\n", atual->petInfo->ID, atual->petInfo->Nome, atual->petInfo->Especie);
        }
    }

    printf("\n--- FILA NORMAL ---\n");
    if (filaVazia(normal)) {
        printf("Fila normal vazia.\n");
    } else {
         for (atual = normal->ini; atual != NULL; atual = atual->prox) {
            printf("ID: %d | Nome: %s | Especie: %s\n", atual->petInfo->ID, atual->petInfo->Nome, atual->petInfo->Especie);
        }
    }
}

void imprimirAtendidos(PetFila* atendidos) {
    PetNo* atual;
    printf("\n--- Relatorio de Pets Atendidos ---\n");

    if (filaVazia(atendidos)) {
        printf("Nenhum pet foi atendido ainda.\n");
    } else {
        for (atual = atendidos->ini; atual != NULL; atual = atual->prox) {
             printf("ID: %d | Nome: %s | Prioridade: %s\n",
                   atual->petInfo->ID, atual->petInfo->Nome, (atual->petInfo->Prioridade == 0) ? "Emergencia" : "Normal");
        }
    }
}

int main() {
    srand(time(NULL));

    PetFila* filaEmergencia = criaFila();
    PetFila* filaNormal = criaFila();
    PetFila* filaAtendidos = criaFila();

    int opcao;
    do {
        // Exibe o menu de opções
        printf("\n\n--- Clinica Veterinaria ---\n");
        printf("1. Inserir um pet na fila\n");
        printf("2. Atender o proximo pet\n");
        printf("3. Mostrar proximo a ser atendido\n");
        printf("4. Imprimir relatorio das filas\n");
        printf("5. Imprimir relatorio de atendidos\n");
        printf("6. Finalizar o sistema\n");
        printf("---------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 2:
                atenderPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 3:
                mostrarProximo(filaEmergencia, filaNormal);
                break;
            case 4:
                imprimirRelatorioFilas(filaEmergencia, filaNormal);
                break;
            case 5:
                imprimirAtendidos(filaAtendidos);
                break;
            case 6:
                printf("\nFinalizando...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    printf("Sistema finalizado.\n");
    
    liberaFila(filaEmergencia);
    liberaFila(filaNormal);
    liberaFila(filaAtendidos);

    return 0;
}
