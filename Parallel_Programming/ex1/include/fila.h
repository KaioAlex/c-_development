// .h - prototipos das funcoes da estrutura fila
#ifndef FILA_H
#define FILA_H

#include <pthread.h>

typedef struct queue queue_t;

struct queue_node{
	void* job;

	struct queue_node* next;
};

struct queue{
	int size;

	struct queue_node* head;

	pthread_mutex_t m;

	char locked;
};

void queue_node_delete(struct queue_node* node);

// utilizar "queue_lock" antes de invocar o push
int queue_t_push(queue_t* q, void* job);

// utilizar "queue_lock" antes de invocar o pop
void* queue_t_pop(queue_t* q);

// liberando memória de uma fila
void queue_t_delete(queue_t* q);

// aloca memória a um novo nó
struct queue_node* new_queue_node();

// aloca memória a uma nova fila
queue_t* new_queue();

// Trava a fila para as ações pop/push. Impede acesso de outras threads antes de rodar "queue_unlock"
void queue_lock(queue_t* q);

// Libera a fila para outras threads usarem
void queue_unlock(queue_t* q);

#endif
