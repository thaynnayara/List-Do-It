#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 50
#define MAX_ACOES 50       
#define MAX_NOTIFICACOES 50 
#define TAM_DESCRICAO 100  
#define TAM_NOTIFICACAO 200 

// Estruturas de Dados
typedef struct {
    int id;
    char descricao[TAM_DESCRICAO];
    int concluida; 
} Tarefa;
typedef struct {
    char tipo_acao[20];
    Tarefa tarefa;   
} Acao;

typedef struct {
    Tarefa tarefas[MAX_TAREFAS];
    int quantidade;
    int proximo_id; 
} ListaDeTarefas;

typedef struct {
    Acao acoes[MAX_ACOES];
    int topo;  
} PilhaDeAcoes;

typedef struct {
    char notificacoes[MAX_NOTIFICACOES][TAM_NOTIFICACAO];
    int frente;
    int final;
} FilaDeNotificacoes;

// Métodos 

void inicializar_lista(ListaDeTarefas *lista) {
    lista->quantidade = 0; 
    lista->proximo_id = 1; 
    printf("Lista de tarefas inicializada com sucesso!\n");
}


void adicionar_tarefa(ListaDeTarefas *lista, const char* descricao) {

    if (lista->quantidade >= MAX_TAREFAS) {
        printf("ERRO: A lista de tarefas esta cheia!\n");
        return;
    }

    // cria a nova tarefa
    Tarefa nova_tarefa;
    nova_tarefa.id = lista->proximo_id;
    strcpy(nova_tarefa.descricao, descricao); 
    nova_tarefa.concluida = 0; 

    lista->tarefas[lista->quantidade] = nova_tarefa;
    
    lista->quantidade++;
    lista->proximo_id++;

    printf("Tarefa '%s' adicionada com sucesso!\n", descricao);
}

void listar_tarefas(const ListaDeTarefas *lista) {

    printf("\n------------- Lista de Tarefas -------------\n");
    
    if (lista->quantidade == 0) {
        printf("Sua lista de tarefas esta vazia.\n");
    } else {
        for (int i = 0; i < lista->quantidade; i++) {

            printf("%d. [%s] - %s\n", 
                   lista->tarefas[i].id,
                   lista->tarefas[i].concluida ? "Concluida" : "Pendente",
                   lista->tarefas[i].descricao);
        }
    }
    
    printf("---------------------------\n");
}

void marcar_status_tarefa(ListaDeTarefas *lista, int id_tarefa, int novo_status) {

    for (int i = 0; i < lista->quantidade; i++) {
        
        if (lista->tarefas[i].id == id_tarefa) {
            
            lista->tarefas[i].concluida = novo_status;
            
            printf("Status da tarefa %d alterado com sucesso para '%s'.\n", 
                   id_tarefa, 
                   novo_status ? "Concluida" : "Pendente");
            return;
        }
    }

    printf("ERRO: Tarefa com ID %d nao encontrada.\n", id_tarefa);
}



int main() {
    ListaDeTarefas minha_lista;
    int opcao;

    inicializar_lista(&minha_lista);

    while (1) {
        printf("\n------------- task dia a dia -------------\n");
        printf("1. Adicionar Nova Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Atualizar Status da Tarefa\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1: {
                char descricao[TAM_DESCRICAO];
                printf("Digite a descricao da nova tarefa: ");
                fgets(descricao, TAM_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                adicionar_tarefa(&minha_lista, descricao);
                break;
            }
            case 2:
                listar_tarefas(&minha_lista);
                break;
            
            case 3: {
                int id_para_atualizar;
                int novo_status;
                
                listar_tarefas(&minha_lista);
                printf("Digite o ID da tarefa que deseja atualizar: ");
                scanf("%d", &id_para_atualizar);

                printf("Digite o novo status (1 para Concluida, 0 para Pendente): ");
                scanf("%d", &novo_status);

                if (novo_status == 0 || novo_status == 1) {
                    marcar_status_tarefa(&minha_lista, id_para_atualizar, novo_status);
                } else {
                    printf("Status invalido! Use 1 ou 0.\n");
                }
                break;
            }

            case 0:
                printf("Saindo do task dia a dia!\n");
                return 0;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0; 
}