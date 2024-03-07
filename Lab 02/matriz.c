#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#define m 3 //Número de linhas da matriz A
#define n 8 //Número de colunas de A e linhas de B

int A[m][n] = {{1, 2, 3, 4, 5, 6, 7, 8},
	 {4, 5, 6, 1, 9, 0, 2, 7},
	 {6, 2, 3, 9, 1, 4, 0, 5}};
	 
int B[][1] = {{6},
	 {5},
	 {2},
	 {1},
	 {0},
	 {8},
	 {4},
	 {9}};

struct ThreadArgs {
    int* C;
    int index;
};

void* multiplica(void *args)
{
	struct ThreadArgs* t_args = (struct ThreadArgs*)args;
    int k = t_args->index;
    int* vetor = t_args->C;
    
    int valor = 0;
	for(int i = 0; i < n; i++)
	{
		valor += A[k][i] * B[k][0];
	}
	vetor[k] = valor;
	pthread_exit(NULL);
}

void zera_vetor(int vetor[], int k)
{
	for(int i = 0; i < k; i++)
	{
		vetor[i] = 0;
	}
}

void show_vetor(int vetor[], int k)
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
	pthread_t threads[m];
	int C[m];
	zera_vetor(C, m);
	struct ThreadArgs args[m];

	for(int i = 0; i < m; i++)
	{
		pthread_create(&threads[i], NULL, &multiplica, (void*)&args[i]);
	}

	for(int j = 0; j < m; j++)
	{
		pthread_join(threads[j], NULL);
	}
	show_vetor(C, m);
		


return 0;
}
