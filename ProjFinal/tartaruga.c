#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define N 5 //Número de threads
#define FRAC 100 //Número de frações a serem calculadas
#define FRAC_THREAD FRAC/N //Número de frações por thread
sem_t semaphore; //Declara semáforo

long double Euler = 0;

struct ThreadArgs //struct contendo:
{
  int inicio;
  int fim;
};

void fatorial(int* vetor)
{
  for(int i = 0; i < N; i++)
  {
    
  }
}

void* fatorial(void *args)
{
  struct ThreadArgs* t_args = (struct ThreadArgs*)args; //realiza o casting e extrai os valores passados para args
  int inicio = t_args->inicio;
  int fim = t_args->fim;
  //int denominador = *(int *)fat;

  
  for (int i = inicio; i < fim; i++) 
  {
    printf("%d\n", i);
     sem_wait(&semaphore);
     Euler += 1.0 / i;
     sem_post(&semaphore);
  }
  
  pthread_exit(NULL); // encerra a thread
}

int main(void) 
{
  struct ThreadArgs args[N];
  pthread_t threads[N]; //Vetor de threads
  clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
  start = clock(); //Inicia contagem de tempo
  sem_init(&semaphore, 0, 1); //Inicia semáforo
  
  for(int i = 0; i < N; i++) //Para cada linha da matriz A...
  {
    
    args[i].inicio = i * FRAC_THREAD + 1;
    args[i].fim = (i + 1) * FRAC_THREAD + 1;
    pthread_create(&threads[i], NULL, &fatorial, (void*)&args);
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
  
  printf("Euler: %Lf\n", Euler);
  printf("Tempo: %lf\n", exec_time);
  return 0;
}