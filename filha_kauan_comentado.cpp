#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa um processo
typedef struct Process {
    int id;                // Identificador do processo
    struct Process* prox;  // Ponteiro para o pr�ximo processo na fila ou na pilha
} Process;

// Estrutura para a fila
typedef struct Queue {
    Process* frente;       // Ponteiro para o primeiro processo da fila
    Process* atras;        // Ponteiro para o �ltimo processo da fila
} Queue;

// Estrutura para a pilha
typedef struct Stack {
    Process* top;          // Ponteiro para o topo da pilha
} Stack;

// Fun��o para criar uma nova fila
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));  // Aloca mem�ria para a fila
    q->frente = q->atras = NULL;               // Inicializa a fila vazia
    return q;                                  // Retorna o ponteiro para a fila
}

// Fun��o para enfileirar um novo processo
void enqueue(Queue* q, int id) {
    Process* newProcess = (Process*)malloc(sizeof(Process));  // Aloca mem�ria para um novo processo
    newProcess->id = id;                                      // Define o ID do processo
    newProcess->prox = NULL;                                  // Pr�ximo processo � NULL, pois ser� o �ltimo da fila

    if (q->atras == NULL) {                 // Se a fila estiver vazia
        q->frente = q->atras = newProcess;  // O novo processo � o primeiro e �ltimo
    } else {
        q->atras->prox = newProcess;        // Liga o �ltimo processo atual ao novo processo
        q->atras = newProcess;              // Atualiza o �ltimo processo para o novo
    }
    printf("Processo %d enfileirado com sucesso.\n", id);  // Mensagem de sucesso
}

// Fun��o para desenfileirar (remover) o primeiro processo da fila
Process* dequeue(Queue* q) {
    if (q->frente == NULL) {  // Se a fila estiver vazia
        printf("\nA fila est� vazia. N�o h� processos para desenfileirar.\n");
        return NULL;          // Retorna NULL indicando que n�o h� processos
    }

    Process* temp = q->frente;        // Guarda o primeiro processo da fila
    q->frente = q->frente->prox;      // Atualiza o ponteiro da frente para o pr�ximo processo

    if (q->frente == NULL) {          // Se a fila ficou vazia ap�s o deque
        q->atras = NULL;              // O ponteiro de tr�s tamb�m � NULL
    }

    printf("Processo %d desenfileirado e movido para a pilha.\n", temp->id);  // Mensagem de sucesso
    return temp;                        // Retorna o processo removido da fila
}

// Fun��o para criar uma nova pilha
Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));  // Aloca mem�ria para a pilha
    s->top = NULL;                             // Inicializa a pilha vazia
    return s;                                  // Retorna o ponteiro para a pilha
}

// Fun��o para empilhar (adicionar) um processo na pilha
void push(Process** topo, Process* processo) {
    processo->prox = *topo;  // O novo processo aponta para o topo atual da pilha
    *topo = processo;        // Atualiza o ponteiro 'topo' para apontar para o novo processo
    printf("Processo com Identificador de Processo (PID) %d empilhado com sucesso!\n", processo->id);
}

// Fun��o para desempilhar (remover) o processo no topo da pilha
Process* pop(Process** topo) {
    if (*topo == NULL) {     // Se a pilha estiver vazia
        printf("\nA pilha est� vazia. N�o h� processos para desempilhar.\n");
        return NULL;         // Retorna NULL indicando que n�o h� processos
    }

    Process* processoDesempilhado = *topo;  // Guarda o processo que ser� desempilhado
    *topo = (*topo)->prox;                  // Atualiza o ponteiro 'topo' para o pr�ximo processo na pilha
    printf("Processo desempilhado com Identificador de Processo (PID): %d\n", processoDesempilhado->id);
    return processoDesempilhado;            // Retorna o processo desempilhado
}

// Fun��o para imprimir o conte�do da fila de processos
void imprimirQueue(Process* frente) {
    if (frente == NULL) {     // Se a fila estiver vazia
        printf("A fila (Queue) de processos se encontra vazia!\n");
        return;               // Retorna sem fazer nada
    }
 
    printf("\nConteudo da fila (Queue) de processos: ");
    Process* atual = frente;  // Come�a do primeiro processo da fila
    
    while (atual != NULL) {   // Percorre cada processo na fila
        printf("%d ", atual->id);  // Imprime o ID do processo atual
        atual = atual->prox;       // Move para o pr�ximo processo
    }
    
    printf("\n");
}

// Fun��o para imprimir o hist�rico da pilha de processos
void historicoStack(Process* stack) {
    if (stack == NULL) {         // Se a pilha estiver vazia
        printf("A pilha (Stack) de processos se encontra vazia!\n");
        return;                  // Retorna sem fazer nada
    }

    printf("Conteudo da pilha (Stack) de processos: ");
    Process* atual = stack;      // Come�a do topo da pilha
    
    while (atual != NULL) {      // Percorre cada processo na pilha
        printf("%d ", atual->id); // Imprime o ID do processo atual
        atual = atual->prox;      // Move para o pr�ximo processo
    }
    
    printf("\n");
}

// Fun��o principal
int main() {
    Queue* queue = createQueue();  // Cria uma fila vazia
    Stack* stack = createStack();  // Cria uma pilha vazia

    // Enfileiramento de 3 processos
    for (int i = 1; i <= 3; i++) {
        enqueue(queue, i);         // Adiciona processos com IDs 1, 2 e 3 na fila
    }

    // Imprime o conte�do da fila
    imprimirQueue(queue->frente);

    // Processa cada elemento da fila e move para a pilha
    while (queue->frente != NULL) {
        Process* process = dequeue(queue);  // Remove o primeiro processo da fila
        if (process != NULL) {
            push(&stack->top, process);     // Adiciona o processo removido ao topo da pilha
        }
    }

    // Verifica se a fila est� vazia
    if (queue->frente == NULL) {
        printf("\nA fila agora esta vazia.\n");
    }

    // Imprime o conte�do da pilha (hist�rico de processos finalizados)
    printf("\nHistorico de Processos da Stack finalizados\n");
    historicoStack(stack->top);

    // Desempilha todos os processos da pilha, liberando cada um
    while (stack->top != NULL) {
        Process* temp = pop(&stack->top);  // Remove o processo do topo da pilha
        free(temp);                        // Libera a mem�ria do processo removido
    }

    printf("\n");
    historicoStack(stack->top);   // Verifica se a pilha est� vazia
    printf("\n");

    // Libera a mem�ria alocada para a fila e a pilha
    free(queue);
    free(stack);

    return 0;  // Fim do programa
}

