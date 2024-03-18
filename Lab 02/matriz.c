#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#define m 24 //Número de linhas da matriz A
#define n 8 //Número de colunas de A e linhas de B

int A[m][n] = {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 9, 10, 11, 12, 13, 14, 15, 16 },
        { 17, 18, 19, 20, 21, 22, 23, 24 },
        { 25, 26, 27, 28, 29, 30, 31, 32 },
        { 33, 34, 35, 36, 37, 38, 39, 40 },
        { 41, 42, 43, 44, 45, 46, 47, 48 },
        { 49, 50, 51, 52, 53, 54, 55, 56 },
        { 57, 58, 59, 60, 61, 62, 63, 64 },
        { 65, 66, 67, 68, 69, 70, 71, 72 },
        { 73, 74, 75, 76, 77, 78, 79, 80 },
        { 81, 82, 83, 84, 85, 86, 87, 88 },
        { 89, 90, 91, 92, 93, 94, 95, 96 },
        { 97, 98, 99, 100, 101, 102, 103, 104 },
        { 105, 106, 107, 108, 109, 110, 111, 112 },
        { 113, 114, 115, 116, 117, 118, 119, 120 },
        { 121, 122, 123, 124, 125, 126, 127, 128 },
        { 129, 130, 131, 132, 133, 134, 135, 136 },
        { 137, 138, 139, 140, 141, 142, 143, 144 },
        { 145, 146, 147, 148, 149, 150, 151, 152 },
        { 153, 154, 155, 156, 157, 158, 159, 160 },
        { 161, 162, 163, 164, 165, 166, 167, 168 },
        { 169, 170, 171, 172, 173, 174, 175, 176 },
        { 177, 178, 179, 180, 181, 182, 183, 184 },
        { 185, 186, 187, 188, 189, 190, 191, 192 }
    };
	 
int B[][1] = {{6}, //Matriz B
	 {5},
	 {2},
	 {1},
	 {0},
	 {8},
	 {4},
	 {9}};

struct ThreadArgs //struct contendo o vetor C resultante e o indíce de um dos elementos do vetor
{
    int* C;
    int index;
	int num_threads;
	sem_t* semaphore;
};

//Função multiplica() faz com que cada thread realize o cálculo do valor do item C[k]
void* multiplica(void *args)
{
	struct ThreadArgs* t_args = (struct ThreadArgs*)args; //extrai o vetor C e o índice k do parâmetro args passado
    int k = t_args->index;
    int* vetor = t_args->C;
	int threads = t_args->num_threads;
	sem_t* semaphore = t_args->semaphore;
	printf("Threads: %d\n", threads);
    for(int j = 0; j < m/threads; j++)
	{
		int valor = 0;
		for(int i = 0; i < n; i++) //Realiza o cálculo do item C[k]
		{
			valor += A[(m/threads) * k + j][i] * B[i][0];
		}
		sem_wait(semaphore);
		vetor[(m/threads) * k + j] = valor; //altera valor no vetor
		sem_post(semaphore); 
		printf("%d index: %d k: %d j: %d\n", valor, (m/threads) * k + j, k, j);
	}
	pthread_exit(NULL); // encerra a thread
	
}
void multiplica_serial(int vetor[])
{
	for(int j = 0; j < m; j++)
	{
		int valor = 0;
		for(int i = 0; i < n; i++) //Realiza o cálculo do item C[k]
		{
			valor += A[j][i] * B[i][0];
		}
		vetor[j] = valor; //altera valor no vetor
	}
}

void zera_vetor(int vetor[], int k) //Função para zerar o vetor (evita erros)
{
	for(int i = 0; i < k; i++)
	{
		vetor[i] = 0; //Atribui zero a todos os elementos do vetor
	}
}

void show_vetor(int vetor[], int k) // Função para exibir todos os elementos do vetor
{
	printf("Vetor final: [");
	for(int i = 0; i < k; i++)
	{
		printf("%d, ", vetor[i]);
	}
	printf("]\n");
}

int main()
{
	pthread_t threads[m]; //Vetor de threads
	int C_serial[m]; //Matriz C resultante
	int C_paralela[m];
	zera_vetor(C_serial, m);
	struct ThreadArgs args[m]; //args será passado como argumento para a thread

	clock_t start, end;
    double serial_time, parallel_time;
	sem_t semaphore;
    sem_init(&semaphore, 0, 1);

	start = clock();
	multiplica_serial(C_serial);
	end = clock();
	serial_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Tempo de execução serial: %lfs\n", serial_time);
	printf("Matriz serial: ");
	show_vetor(C_serial, m); //Exibe o vetor C resultante

	for(int i = 2; i <= n; i += 2)
	{
		int num_threads = i;
		zera_vetor(C_paralela, m);
		start = clock();
		for(int j = 0; j < num_threads; j++) //Para cada linha da matriz A...
		{
			args[j].C = C_paralela;
			args[j].num_threads = num_threads;
			args[j].index = j;
			args[j].semaphore = &semaphore;
			//Cria uma thread que executará o cálculo: C[m] = ∑(A[m][i] * B[i][0])
			pthread_create(&threads[j], NULL, &multiplica, (void*)&args[j]);
		}
		//Aguarda todas as threads encerrarem usando pthread_join()
		for(int j = 0; j < num_threads; j++)
		{
			pthread_join(threads[j], NULL);
		}
		end = clock();
        parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Tempo de execução em paralelo com %d processadores: %lfs\n", num_threads, parallel_time);
		printf("Matriz paralela: ");
		show_vetor(C_paralela, m); //Exibe o vetor C resultante
	}
	sem_destroy(&semaphore);

return 0;
}
