#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#define m 24 //Número de linhas da matriz A
#define n 8 //Número de colunas de A e linhas de B

int A[m][n] = { //Matriz A
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

struct ThreadArgs //struct contendo:
{
    int* C; //Vetor C resultante
    int index; //Índice da thread
	int num_threads; //Número total de threads executando
	sem_t* semaphore; //Semáforo
};

//Função multiplica() faz com que cada thread realize o cálculo dos itens do vetor C
void* multiplica(void *args)
{
	struct ThreadArgs* t_args = (struct ThreadArgs*)args; //realiza o casting e extrai os valores passados para args
    int k = t_args->index;
    int* vetor = t_args->C;
	int threads = t_args->num_threads;
	sem_t* semaphore = t_args->semaphore;
	
    for(int j = 0; j < m/threads; j++) //Cada thread é responsável por calcular m/threads elementos de C
	{
		int valor = 0;
		for(int i = 0; i < n; i++) //Realiza o cálculo do item C[(m/threads) * k + j]
		{
			valor += A[(m/threads) * k + j][i] * B[i][0];
		}
		sem_wait(semaphore); //Espera outra thread terminar para acessar a área de risco 
		vetor[(m/threads) * k + j] = valor; //altera valor no vetor
		sem_post(semaphore); //Libera o semáforo
	}
	pthread_exit(NULL); // encerra a thread
	
}
void multiplica_serial(int vetor[]) //Função realiza a multiplicação de matrizes de maneira serial
{
	for(int j = 0; j < m; j++)
	{
		int valor = 0;
		for(int i = 0; i < n; i++) //Realiza o cálculo do item C[j]
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
	int C_serial[m]; //Vetor C resultante da execução serial
	int C_paralela[m]; //Vetor C resultante da execução em paralelo
	zera_vetor(C_serial, m);
	struct ThreadArgs args[m]; //args será passado como argumento para a thread

	clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
    double serial_time, parallel_time;
	sem_t semaphore; //Inicia semáforo
    sem_init(&semaphore, 0, 1);

	start = clock(); //Inicia contagem do tempo em serial
	multiplica_serial(C_serial); //Executa em serial
	end = clock(); //Encerra a contagem
	serial_time = ((double)(end - start)) / CLOCKS_PER_SEC; //Calcula o tempo
	printf("Tempo de execução serial: %lfms\n", serial_time * 1000); //Exibe o resultado obtido
	printf("Vetor serial: ");
	show_vetor(C_serial, m); //Exibe o vetor C resultante

	for(int i = 2; i <= n; i += 2) //Para cada número de núcleos de processador:
	{
		int num_threads = i;
		zera_vetor(C_paralela, m);
		start = clock(); //Inicia contagem do tempo em paralelo
		for(int j = 0; j < num_threads; j++) //Para cada thread a ser criada:
		{
			args[j].C = C_paralela; //Passa informações como vetor C, número de threads, índice da thread e o semáforo para a thread
			args[j].num_threads = num_threads;
			args[j].index = j;
			args[j].semaphore = &semaphore;
			//Cria uma thread que fará o cálculo de m/num_threads itens de C
			pthread_create(&threads[j], NULL, &multiplica, (void*)&args[j]);
		}
		//Aguarda todas as threads encerrarem usando pthread_join()
		for(int j = 0; j < num_threads; j++)
		{
			pthread_join(threads[j], NULL);
		}
		end = clock(); //Encerra a contagem do tempo em paralelo
        parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC; //Calcula o tempo
		printf("Tempo de execução em paralelo com %d processadores: %lfms\n", num_threads, parallel_time * 1000); //Exibe o resultado obtido
		printf("Vetor paralelo: ");
		show_vetor(C_paralela, m); //Exibe o vetor C resultante
	}
	sem_destroy(&semaphore); //Destrói o semáforo

return 0;
}
