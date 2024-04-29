#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define N 20 //Número de threads
//#define FRAC 100 //Número de frações a serem calculadas
//#define FRAC_THREAD FRAC/N //Número de frações por thread
sem_t semaphore; //Declara semáforo

long double Euler = 0; //Número de Euler a ser calculado

struct ThreadArgs //struct contendo:
{
  int id; //id da thread
  unsigned long long int* vetor; //vetor de denominadores
};

void zera_vetor(unsigned long long int* vetor, int k) //Função para zerar o vetor (evita erros)
{
  for(int i = 0; i < k; i++)
  {
    vetor[i] = 0; //Atribui zero a todos os elementos do vetor
  }
}

void show_vetor(unsigned long long int* vetor, int k) // Função para exibir todos os elementos do vetor
{
  printf("Vetor final: [");
  for(int i = 0; i < k; i++)
  {
    printf("%lld, ", vetor[i]);
  }
  printf("]\n");
}

void fatorial(unsigned long long int* vetor) //Função para calcular os fatoriais nos denominadores
{
  vetor[0] = 1;
  for(int i = 1; i < N; i++)
  {
    vetor[i] = vetor[i - 1] * i; //Os resultados ficam guardados dentro do vetor
  }
}

void* calcula_fracoes(void *args)
{
  struct ThreadArgs* t_args = (struct ThreadArgs*)args; //realiza o casting e extrai os valores passados para args
  int index = t_args->id; //id thread
  unsigned long long int* denominadores = t_args->vetor; //vetor de denominadores
  
     sem_wait(&semaphore);
     Euler += 1.0 / denominadores[index]; //calcula fração e adiciona valor a Euler
     sem_post(&semaphore);
  
  pthread_exit(NULL); // encerra a thread
}

int main(void) 
{
  struct ThreadArgs args[N]; //Vetor de argumentos da thread
  pthread_t threads[N]; //Vetor de threads
  clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
  start = clock(); //Inicia contagem de tempo
  unsigned long long int *fat = malloc(N * sizeof(unsigned long long int)); //Aloca espaço para vetor com os fatoriais de 0 a N - 1
  if (fat == NULL) 
  {
      perror("Falha ao alocar memória");
      exit(EXIT_FAILURE);
  }
  zera_vetor(fat, N); //zera o vetor fat
  fatorial(fat); //Preenche o vetor com os fatoriais
  
  sem_init(&semaphore, 0, 1); //Inicia semáforo
  for(int i = 0; i < N; i++) //Para cada loop:
  {
    args[i].id = i; //Atribui id à thread
    args[i].vetor = fat; //Coloca o vetor no argumento
    pthread_create(&threads[i], NULL, &calcula_fracoes, (void*)&args[i]);
  }

  //Aguarda todas as threads encerrarem usando pthread_join()
  for(int j = 0; j < N; j++)
  {
    pthread_join(threads[j], NULL);
  }

  sem_destroy(&semaphore); //Destrói semáforo
  end = clock(); //Encerra o tempo de execução
  double exec_time = ((double)(end - start)) / CLOCKS_PER_SEC; //Calcula o tempo de execução em ms
  exec_time *= 1000;
  
  printf("Euler: %.65Lf\n", Euler);
  printf("Tempo: %lf\n", exec_time);
  return 0;
}