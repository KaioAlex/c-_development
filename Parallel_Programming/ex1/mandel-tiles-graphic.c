// C implementation for mandelbrot set fractals using libgraph, a simple
// library similar to the old Turbo C graphics library.
/*****************************************************************
 * ATENCAO: a biblioteca libgraph nao funciona com pthreads, entao
 * a solucao do exercicio nao deve chamar as funcoes graficas 
 * NADA SERA EXIBIDO, INFELIZMENTE. :-(
 *****************************************************************/

//#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

#include "fila.h"

#define MAXX 640
#define MAXY 480
#define MAXITER 32768
#define NUM_THREADS_PADRAO 1

FILE* input; 					// descriptor for the list of tiles (cannot be stdin)
int color_pick = 5; 			// decide how to choose the color palette
int tam = 0;

// params for each call to the fractal function
typedef struct{
	int left; int low;  		// lower left corner in the screen
	int ires; int jres; 		// resolution in pixels of the area to compute
	double xmin; double ymin;   // lower left corner in domain (x,y)
	double xmax; double ymax;   // upper right corner in domain (x,y)
} fractal_param_t;

/****************************************************************
 * Nesta versao, o programa principal le diretamente da entrada
 * a descricao de cada quadrado que deve ser calculado; no EX1,
 * uma thread produtora deve ler essas descricoes sob demanda, 
 * para manter uma fila de trabalho abastecida para as threads
 * trabalhadoras.
 ****************************************************************/
int input_params(fractal_param_t* p){ 
	int n;
	n = fscanf(input, "%d %d %d %d",&(p->left),&(p->low),&(p->ires),&(p->jres));

	if(n == EOF) return n;

	if(n != 4){
		perror("fscanf(left,low,ires,jres)");
		exit(-1);
	}
	
	n = fscanf(input,"%lf %lf %lf %lf", &(p->xmin),&(p->ymin),&(p->xmax),&(p->ymax));
	if(n != 4){
		perror("scanf(xmin,ymin,xmax,ymax)");
		exit(-1);
	}

	// printf("%d %d %d %d\n",(p->left),(p->low),(p->ires),(p->jres));
	// printf("%lf %lf %lf %lf", (p->xmin),(p->ymin),(p->xmax),(p->ymax));
	// exit(-1);

	return 8;
}

/****************************************************************
 * A funcao a seguir faz a geracao dos blocos de imagem dentro
 * da area que vai ser trabalhada pelo programa. Para a versao
 * paralela, nao importa quais as dimensoes totais da area, basta
 * manter um controle de quais blocos estao sendo processados
 * a cada momento, para manter as restricoes desritas no enunciado.
 ****************************************************************/
// Function to draw mandelbrot set
void fractal(fractal_param_t* p){
	double dx, dy;
	int i, j, k, color;
	double x, y, u, v, u2, v2;

    /*************************************************************
     * a funcao // deve ser removida na versao com pthreads,
     * ja que as bibliotecas sao conflitantes.
     *************************************************************/
	//rectangle(p->left, p->low, p->left+p->ires-1, p->low+p->jres-1);

	dx = ( p->xmax - p->xmin ) / p->ires;
	dy = ( p->ymax - p->ymin ) / p->jres;
	
	// scanning every point in that rectangular area.
	// Each point represents a Complex number (x + yi).
	// Iterate that complex number
	for(j = 0; j < p->jres; j++){
		for(i = 0; i <= p->ires; i++){
			x = i * dx + p->xmin; // c_real
			u = u2 = 0; // z_real
			y = j * dy + p->ymin; // c_imaginary
			v = v2 = 0; // z_imaginary

			// Calculate whether c(c_real + c_imaginary) belongs
			// to the Mandelbrot set or not and draw a pixel
			// at coordinates (i, j) accordingly
			// If you reach the Maximum number of iterations
			// and If the distance from the origin is
			// greater than 2 exit the loop
			for(k=0; (k < MAXITER) && ((u2+v2) < 4); ++k){
				// Calculate Mandelbrot function
				// z = z*z + c where z is a complex number

				// imag = 2*z_real*z_imaginary + c_imaginary
				v = 2 * u * v + y;
				// real = z_real^2 - z_imaginary^2 + c_real
				u  = u2 - v2 + x;
				u2 = u * u;
				v2 = v * v;
			}

			if(k == MAXITER){
				// converging areas are black
				color = 0;
			} else{
				// graphics mode has only 16 colors;
				// choose a range and recycle!
				color = ( k >> color_pick ) %16;
			}
		}
	}

	//printf("%d %d %d\n", p->left+i, p->low+j, color);
}

typedef struct{
	int id;
	int* jobs_por_trabalhador;	// vetor para guardar numero de tarefas de cada thread
} dados_thread_t;

queue_t* fila, *resultados;
sem_t sem_1, sem_2;

struct relatorio_job{
	int trabalhador;
	float tempo;
};

int cont_fila_vazia = 0;

void* thread_trabalhadora(void* args){
	// casting a struct passada como parametro do tipo void*, para dados_thread_t*
	dados_thread_t* dados = (dados_thread_t *)args;

	struct relatorio_job* relatorio;

	// inicia temporizador
	clock_t start_t, end_t; 
	start_t = clock();

	while(true){
		relatorio = malloc(sizeof(struct relatorio_job));

		queue_lock(fila);
		if(fila->size <= tam) sem_post(&sem_2);       // posso continuar

		// se fila vazia, aumenta numero de vezes do contador
		if(fila->size == 0){
			cont_fila_vazia++;

			queue_unlock(fila);
			sem_wait(&sem_1);
			queue_lock(fila);
		}

		// pegando primeiro job da fila
		fractal_param_t* job = queue_t_pop(fila);
		// se chegar ao fim dos jobs, sai
		if(!job) break;

		dados->jobs_por_trabalhador[dados->id]++;
		queue_unlock(fila);
		fractal(job);

		free(job);
		
		// finaliza temporizador
		end_t = clock();

		relatorio->trabalhador = dados->id;
		
		relatorio->tempo = ((double)(end_t - start_t)) / (CLOCKS_PER_SEC / 1000);

		// adicionando estatisticas na fila de resultados
		queue_lock(resultados);
		queue_t_push(resultados, relatorio);
		queue_unlock(resultados);
	}

	queue_unlock(fila);

	free(relatorio);
	free(dados);

}

void* thread_entrada(void* args){
	int* jobs_por_trabalhador = (int *)args;
	int NUM_THREADS = tam;

	// for(unsigned i = 0; i < tam; i++)
	// 	printf("value: %d\n", jobs_por_trabalhador[i]);

	fractal_param_t* p = malloc(sizeof(fractal_param_t));
	pthread_t tids[NUM_THREADS];
	dados_thread_t* dados;

	for(unsigned i = 0; i < NUM_THREADS; i++){
		dados = malloc(sizeof(dados_thread_t));
		dados->id = i;
		dados->jobs_por_trabalhador = jobs_por_trabalhador;

		pthread_create(tids+i, NULL, thread_trabalhadora, dados);
	}

	while(input_params(p) != EOF){
		sem_wait(&sem_2);

		// realizando o lock na fila e adicionando job nela
		queue_lock(fila);
		queue_t_push(fila, p);
		
		sem_post(&sem_1);
		queue_unlock(fila);

		p = malloc(sizeof(fractal_param_t));
	}
	free(p);

	// descritores de trabalho como NULL para EOW
	queue_lock(fila);
	for(unsigned i = 0; i < NUM_THREADS; i++){
		queue_t_push(fila, NULL);
		sem_post(&sem_1);
	}
	queue_unlock(fila);

	// aguardar todos os trabalhadores para prosseguir
	for(unsigned i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

}

/****************************************************************
 * Essa versao do programa, sequencial le a descricao de um bloco
 * de imagem do conjunto de mandelbrot por vez e faz a geracao
 * e exibicao do mesmo na janela grafica. Na versao paralela com 
 * pthreads, como indicado no enunciado, devem ser criados tres
 * tipos de threads: uma thread de entrada que le a descricao dos
 * blocos e alimenta uma fila para os trabalhadores, diversas
 * threads trabalhadoras que retiram um descritor de bloco da fila
 * e fazem o calculo da imagem e depositam um registro com os
 * dados sobre o processamento do bloco, como descrito no enunciado,
 * e uma thread final que recebe os registros sobre o processamento
 * e computa as estatisticas do sistema (que serao a unica saida
 * visivel do seu programa na versao que segue o enunciado).
 ****************************************************************/
int main(int argc, char* argv[]){
	// int i, j, k;
	// fractal_param_t p;
	int num_threads = NUM_THREADS_PADRAO;

	if((argc != 2) && (argc != 3)){
		fprintf(stderr,"usage %s filename [num_threads]\n", argv[0] );
		exit(-1);
	} 

	// Caso o número de threads seja passado pelo usuario
	if(argc == 3){
		//color_pick = atoi(argv[2]);
		num_threads = atoi(argv[2]);
	}

	// abrindo arquivo no descritor input
	if((input = fopen(argv[1],"r")) == NULL){
		perror("fdopen");
		exit(-1);
	}

	// inicializando os semaforos
    if(sem_init(&sem_1, 0, 0) < 0){         	// inicialmente como locked
        perror("Semaphore initialization failed");
        exit(-1);
    }
    if(sem_init(&sem_2, 0, num_threads)){   	// "counted semaphore" - inicialmente unlocked
        perror("Semaphore initialization failed");
        exit(0);
    }

	// inicializando as filas
	fila = new_queue();
	resultados = new_queue();

	tam = num_threads;
	int* jobs_por_trabalhador = (int *)malloc(num_threads*sizeof(int));

	pthread_t tid;
	// acionando a thread de entrada
	pthread_create(&tid, NULL, thread_entrada, jobs_por_trabalhador);

	// aguardando o retorno da thread de entrada
	pthread_join(tid, NULL);

	// printf("main: ");
	// for(unsigned i = 0; i < num_threads; i++)
	//	printf("%d ", jobs_por_trabalhador[i]);
	// printf("\n");

	// tempo_total, t_medio e t_desvio
	double tempo_total = 0;
	int total_tarefas = resultados->size;

	struct queue_node* cur = resultados->head->next;
	while(cur->next != NULL){
		// realizando a soma do tempo gasto pelos trabalhadores
		tempo_total += ((struct relatorio_job *)(cur->job))->tempo;
		cur = cur->next;	// avancando na fila
	}
	printf("Tempo total: %f\n", tempo_total);

	double t_desvio = 0, t_medio = (tempo_total / total_tarefas);
	while(resultados->size > 0){
		struct relatorio_job* r = queue_t_pop(resultados);

		double diferenca = r->tempo - t_medio;
		t_desvio += diferenca * diferenca;

		free(r);
	}
	t_desvio = sqrt(t_desvio / total_tarefas);

	// desvio_tarefas_pt, media_tarefas_pt
	double desvio_tarefas_pt = 0, media_tarefas_pt = (double)(total_tarefas) / num_threads;
	for(unsigned i=0; i < num_threads; i++){
		double diferenca = jobs_por_trabalhador[i] - media_tarefas_pt;

		desvio_tarefas_pt += diferenca * diferenca;
	}

	desvio_tarefas_pt = sqrt(desvio_tarefas_pt / num_threads);

	// Printando saida
	printf("Tarefas: total = %d;  média por trabalhador = %f(%f)\n", total_tarefas, media_tarefas_pt, desvio_tarefas_pt);
	printf("Tempo médio por tarefa: %.6f (%.6f) ms\n", t_medio, t_desvio);
	printf("Fila estava vazia: %d vezes\n", cont_fila_vazia);

	// liberando memoria dos recursos de semaforos e das filas
	sem_destroy(&sem_2);
	sem_destroy(&sem_1);

	queue_t_delete(fila);
	queue_t_delete(resultados);

	fclose(input);

	return 0;
}
