#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#define m 3 //Número de linhas da matriz A
#define n 8 //Número de colunas de A e linhas de B

int A[m][n] = {{1, 2, 3, 4, 5, 6, 7, 8}, //Matriz A
	 {4, 5, 6, 1, 9, 0, 2, 7},
	 {6, 2, 3, 9, 1, 4, 0, 5}};
	 
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
};

//Função multiplica() faz com que cada thread realize o cálculo do valor do item C[k]
void* multiplica(void *args)
{
	struct ThreadArgs* t_args = (struct ThreadArgs*)args; //extrai o vetor C e o índice k do parâmetro args passado
    int k = t_args->index;
    int* vetor = t_args->C;
    
    int valor = 0;
	for(int i = 0; i < n; i++) //Realiza o cálculo do item C[k]
	{
		valor += A[k][i] * B[i][0];
	}
	vetor[k] = valor; //altera valor no vetor
	pthread_exit(NULL); // encerra a thread
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
	int C[m]; //Matriz C resultante
	zera_vetor(C, m);
	struct ThreadArgs args[m]; //args será passado como argumento para a thread

	for(int i = 0; i < m; i++) //Para cada linha da matriz A...
	{
		args[i].C = C; //Guarda-se o vetor C e o número da linha i de A em args
        args[i].index = i;
		//Cria uma thread que executará o cálculo: C[m] = ∑(A[m][i] * B[i][0])
		pthread_create(&threads[i], NULL, &multiplica, (void*)&args[i]);
	}
	//Aguarda todas as threads encerrarem usando pthread_join()
	for(int j = 0; j < m; j++)
	{
		pthread_join(threads[j], NULL);
	}
	show_vetor(C, m); //Exibe o vetor C resultante
		


return 0;
}
