#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 50
#define MAX_ACOES 50       
#define MAX_NOTIFICACOES 50 
#define TAM_DESCRICAO 100  
#define TAM_NOTIFICACAO 200 


/*

Tarefa: É a nossa unidade básica. Cada tarefa terá um número de identificação (id), uma descrição e um status (concluida).

Acao: Essencial para o Undo/Redo(refazer/desfazer). Ela guarda que tipo de ação foi feita e em qual Tarefa.

ListaDeTarefas: É um array estático que guarda nossas tarefas. O controle quantidade nos diz quantas tarefas temos.

PilhaDeAcoes: Nossa pilha para o histórico. O topo = -1 indicará que ela está vazia.

FilaDeNotificacoes: Nossa fila para as mensagens. Usaremos frente e final para controlar a entrada e saída, de forma similar ao exemplo de Fila Linear do seu PDF.

*/

// --- Estruturas de Dados ---

// Estrutura para uma única tarefa
typedef struct {
    int id;
    char descricao[TAM_DESCRICAO];
    int concluida; // teste booleano onde 0 para pendente e 1 para concluída
} Tarefa;

// Estrutura para uma Ação (para o refazer/desfazer)
typedef struct {
    char tipo_acao[20];
    Tarefa tarefa;      // tarefa que será modificada
} Acao;

// lista (uuso de array estático)
typedef struct {
    Tarefa tarefas[MAX_TAREFAS];
    int quantidade;
    int proximo_id; // geração id's únicos
} ListaDeTarefas;

// pilha (para refazer/desfazer)
typedef struct {
    Acao acoes[MAX_ACOES];
    int topo;  
} PilhaDeAcoes;

// fila (para notificações)
typedef struct {
    char notificacoes[MAX_NOTIFICACOES][TAM_NOTIFICACAO];
    int frente;
    int final;
} FilaDeNotificacoes;

// Métodos 

void inicializar_lista(ListaDeTarefas *lista) {
    lista->quantidade = 0; // zera a quantidade de tarefas
    lista->proximo_id = 1; // a primeira tarefa receberá id 1
    printf("Lista de tarefas inicializada com sucesso!\n");
}

// função para adicionar uma nova tarefa à lista
void adicionar_tarefa(ListaDeTarefas *lista, const char* descricao) {

    if (lista->quantidade >= MAX_TAREFAS) {
        printf("ERRO: A lista de tarefas esta cheia!\n");
        return;
    }

    // cria a nova tarefa
    Tarefa nova_tarefa;
    nova_tarefa.id = lista->proximo_id;
    strcpy(nova_tarefa.descricao, descricao); // copia a descrição para a tarefa
    nova_tarefa.concluida = 0; // nova tarefa começa como "pendente"

    // adiciona a nova tarefa ao array de tarefas
    lista->tarefas[lista->quantidade] = nova_tarefa;
    
    // atualizando
    lista->quantidade++;
    lista->proximo_id++;

    printf("Tarefa '%s' adicionada com sucesso!\n", descricao);
}

// função para listar todas as tarefas -- configuração de leitura
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

// função para alterar o status de uma tarefa (concluída ou pendente)
void marcar_status_tarefa(ListaDeTarefas *lista, int id_tarefa, int novo_status) {
    // Primeiro, vamos procurar a tarefa com o ID fornecido
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


// --- Função principal ---
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