#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>

#ifdef _OPENMP
# include <omp.h>
#endif 

#define PI 3.1415
#define COMPRIMENTO 24 * PI
#define TRAPZ_NUM 8
#define ALT_TRAPZ TRAPZ_NUM / COMPRIMENTO
// Calcular a área para comprimento 24π
// Função f(x) = sen(x) + 2

double Area = 0;
sem_t semaphore;
sem_init(&semaphore, 0, 1);

double func(double x)
{
    return sin(x) + 2;
}
void AreaThread();
//Inicia com x = 0
// comprimento p/ cada thread = 24π / num_threads
int main(int argc, char* argv[])
{
    int num_threads = strtol(argv[1], NULL, 10);

# pragma omp parallel num_threads(thread_count)
AreaThread();
    
    printf("A área total aproximada é: %lf", Area);
    return 0;
}

void AreaThread()
{
#ifdef _OPENMP
  int thread_id = omp_get_thread_num();
  const int  TRAPZ_POR_THREAD = TRAPZ_NUM / omp_get_num_threads();  

#else
thread_id = 0;
const int TRAPZ_POR_THREAD = TRAPZ_NUM;
#endif
 for(int i = 0; i < TRAPZ_POR_THREAD; i++)
 {
  double coluna_anterior = thread_id * ALT_TRAPZ;
  double coluna_atual = coluna_anterior + COMP_THREAD;
  
  double altura_anterior = func(coluna_anterior);
  double altura_altual = func(coluna_atual);
  sem_wait(&semaphore);
  Area += COMP_THREAD * (altura_atual + altura_anterior) / 2;
  sem_post(&semaphore);
 }
}
sem_destroy(&semaphore);

