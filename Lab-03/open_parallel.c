//*************************************** PARA COMPILAR, ESCREVA: gcc -g -Wall -fopenmp -o open open_parallel.c -lm ******************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>

#ifdef _OPENMP
# include <omp.h>
#endif 

#define PI 3.1415
#define COMPRIMENTO 24 * PI
#define TRAPZ_NUM 24
// Calcular a área para comprimento 24π
// Função f(x) = sen(x) + 2

double Area = 0;
sem_t semaphore;

double func(double x)
{
    return sin(x) + 2;
}
void AreaThread();
//Inicia com x = 0
// comprimento p/ cada thread = 24π / num_threads
int main(int argc, char* argv[])
{
    clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
    start = clock();
    sem_init(&semaphore, 0, 1);
    int thread_count = strtol(argv[1], NULL, 10);

# pragma omp parallel num_threads(thread_count)
    AreaThread();

    sem_destroy(&semaphore);
    end = clock();
    double exec_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    exec_time *= 1000;
    printf("O tempo de execução é: %lf\n", exec_time);
    return 0;
}

void AreaThread()
{
  const double ALT_TRAPZ = COMPRIMENTO / TRAPZ_NUM;
#ifdef _OPENMP
  int thread_id = omp_get_thread_num();
  const int  TRAPZ_POR_THREAD = TRAPZ_NUM / omp_get_num_threads();  

#else
    int thread_id = 0;
    const int TRAPZ_POR_THREAD = TRAPZ_NUM;
#endif
 for(int i = 0; i < TRAPZ_POR_THREAD; i++)
 {
  double coluna_anterior = (thread_id + i) * ALT_TRAPZ;
  double coluna_atual = coluna_anterior + ALT_TRAPZ;
  double altura_anterior = func(coluna_anterior);
  double altura_altual = func(coluna_atual);

  sem_wait(&semaphore);
  Area += ALT_TRAPZ * (altura_altual + altura_anterior) / 2;
  sem_post(&semaphore);
 }
}
