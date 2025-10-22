#include <stdio.h>
#include <stdlib.h>
#include "FILA.H"
#include <time.h>

int buscaID(int id, Fila* f) {
    if(vaziaFila(f)){
        return 0;
    }

    no* atual = f->ini;
    while(atual != NULL){
        if(atual->info.ID == id){
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int idExiste(int id, Fila* emergencia, Fila* normal, Fila* atendidos) {
    if(buscaID(id, emergencia) || buscaID(id, normal) || buscaID(id, atendidos)){
        return 1;
    } else {
        return 0;
    }
}

int gerarIDUnico(Fila* emergencia, Fila* normal, Fila* atendidos) {
    int id;
    do {
        id = 100 + rand() % 900;
    } while (idExiste(id, emergencia, normal, atendidos));
    return id;
}

void inserirPet(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos) {
    Pet novoPet;
    char buffer_leitura[51];

    printf("\n--- Inserir Pet na Fila ---\n");
    novoPet.ID = gerarIDUnico(filaEmergencia, filaNormal, filaAtendidos);
    printf("ID Gerado: %d\n", novoPet.ID);

    printf("Nome: ");
    fgets(novoPet.Nome, sizeof(novoPet.Nome), stdin);
    novoPet.Nome[strcspn(novoPet.Nome, "\n")] = '\0';

    printf("Especie: ");
    fgets(novoPet.Especie, sizeof(novoPet.Especie), stdin);
    novoPet.Especie[strcspn(novoPet.Especie, "\n")] = '\0';

    printf("Idade: ");
    fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
    sscanf(buffer_leitura, "%d", &novoPet.Idade);

    printf("Data de Nascimento (dd/mm/aaaa): ");
    fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
    sscanf(buffer_leitura, "%d/%d/%d", &novoPet.DataNascimento.dia, &novoPet.DataNascimento.mes, &novoPet.DataNascimento.ano);
    
    do {
        printf("Prioridade (0 - Emergencia, 1 - Normal): ");
        fgets(buffer_leitura, sizeof(buffer_leitura), stdin);
        sscanf(buffer_leitura, "%d", &novoPet.Prioridade);
    } while (novoPet.Prioridade != 0 && novoPet.Prioridade != 1);

    if (novoPet.Prioridade == 0) {
        insereFila(filaEmergencia, novoPet);
        printf("\n=> Pet '%s' inserido na fila de EMERGENCIA!\n", novoPet.Nome);
    } else {
        insereFila(filaNormal, novoPet);
        printf("\n=> Pet '%s' inserido na fila NORMAL!\n", novoPet.Nome);
    }
}

void mostrarProximo(Fila* filaEmergencia, Fila* filaNormal) {
     printf("\n--- Proximo a Ser Atendido ---\n");
    if (!vaziaFila(filaEmergencia)) {
        printf("Nome: %s\n", filaEmergencia->ini->info.Nome);
        printf("Especie: %s\n", filaEmergencia->ini->info.Especie);
        printf("Tipo de Atendimento: Emergencia\n");
    } else if (!vaziaFila(filaNormal)) {
        printf("Nome: %s\n", filaNormal->ini->info.Nome);
        printf("Especie: %s\n", filaNormal->ini->info.Especie);
        printf("Tipo de Atendimento: Normal\n");
    } else {
        printf("Nao ha pets nas filas para atender.\n");
    }
}

void atenderPet(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos) {
    if (!vaziaFila(filaEmergencia)) {
        Pet petAtendido = retiraFila(filaEmergencia);
        
        printf("\n--- Atendendo Pet Agora (EMERGENCIA) ---\n");
        printf("ID: %d | Nome: %s | Tipo: Emergencia\n",
               petAtendido.ID,
               petAtendido.Nome);

        insereFila(filaAtendidos, petAtendido);
        printf("=> Pet atendido e movido para a lista de historico.\n");

        mostrarProximo(filaEmergencia, filaNormal);

    }else if (!vaziaFila(filaNormal)) {
        Pet petAtendido = retiraFila(filaNormal);

        printf("\n--- Atendendo Pet Agora (NORMAL) ---\n");
        printf("ID: %d | Nome: %s | Tipo: Normal\n",
               petAtendido.ID,
               petAtendido.Nome);
        
        insereFila(filaAtendidos, petAtendido);
        printf("=> Pet atendido e movido para a lista de historico.\n");
        
        mostrarProximo(filaEmergencia, filaNormal);

    }else {
        printf("\nNao ha pets nas filas para atender.\n");
    }
}

void imprimirRelatorioFilas(Fila* emergencia, Fila* normal) {
    no* atual;
    printf("\n--- Relatorio de Pets nas Filas ---\n");

    printf("\n--- FILA DE EMERGENCIA ---\n");
    if (vaziaFila(emergencia)) {
        printf("Fila de emergencia vazia.\n");
    } else {
        for (atual = emergencia->ini; atual != NULL; atual = atual->prox) {
            printf("ID: %d | Nome: %s | Especie: %s\n", atual->info.ID, atual->info.Nome, atual->info.Especie);
        }
    }

    printf("\n--- FILA NORMAL ---\n");
    if (vaziaFila(normal)) {
        printf("Fila normal vazia.\n");
    } else {
         for (atual = normal->ini; atual != NULL; atual = atual->prox) {
            printf("ID: %d | Nome: %s | Especie: %s\n", atual->info.ID, atual->info.Nome, atual->info.Especie);
        }
    }
}

void imprimirAtendidos(Fila* atendidos) {
    no* atual;
    printf("\n--- Relatorio de Pets Atendidos ---\n");

    if (vaziaFila(atendidos)) {
        printf("Nenhum pet foi atendido ainda.\n");
    } else {
        for (atual = atendidos->ini; atual != NULL; atual = atual->prox) {
             printf("ID: %d | Nome: %s | Prioridade: %s\n",
                   atual->info.ID, atual->info.Nome, (atual->info.Prioridade == 0) ? "Emergencia" : "Normal");
        }
    }
}

int main() {
    srand(time(NULL));

    Fila* filaEmergencia = CriaFila();
    Fila* filaNormal = CriaFila();
    Fila* filaAtendidos = CriaFila();

    int opcao = 0;
    char buffer_leitura[51];

    do {
        printf("\n\n--- Clinica Veterinaria ---\n");
        printf("1. Inserir um pet na fila\n");
        printf("2. Atender o proximo pet\n");
        printf("3. Buscar um Pet pelo nome e/ou ID\n");
        printf("4. Mostrar proximo a ser atendido\n");
        printf("5. Imprimir relatorio das filas\n");
        printf("6. Imprimir relatorio de atendidos\n");
        printf("7. Finalizar o sistema\n");
        printf("---------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (fgets(buffer_leitura, sizeof(buffer_leitura), stdin) != NULL) {
            if (sscanf(buffer_leitura, "%d", &opcao) != 1) {
                opcao = 0;
            }
        } else {
            opcao = 6;
        }

        switch (opcao) {
            case 1:
                inserirPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 2:
                atenderPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 3:
                buscarPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 4:
                mostrarProximo(filaEmergencia, filaNormal);
                break;
            case 5:
                imprimirRelatorioFilas(filaEmergencia, filaNormal);
                break;
            case 6:
                imprimirAtendidos(filaAtendidos);
                break;
            case 7:
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