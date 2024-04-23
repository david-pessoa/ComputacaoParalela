//*************************************** PARA COMPILAR, ESCREVA: gcc -g -Wall -fopenmp -o open open_critical.c -lm ******************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef _OPENMP
# include <omp.h>
#endif 

#define PI 3.1415
#define COMPRIMENTO 24 * PI //Define comprimento que será calculado do eixo X
#define TRAPZ_NUM 24 * 4 // Define número de trapézios a serem utilizados no total pelas threads
// Calcular a área para comprimento 24π
// Função f(x) = sen(x) + 2

double Area = 0; //Area a ser calculada

double func(double x) //Função f(x) = sen(x) + 2
{
    return sin(x) + 2;
}
void AreaThread();

int main(int argc, char* argv[])
{
    clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
    start = clock(); //Inicia contagem de tempo
    int thread_count = strtol(argv[1], NULL, 10); // Armazena número de threads passado como argumento

# pragma omp parallel num_threads(thread_count)
    AreaThread(); //Chama o pragma para que a função AreaThread() seja executada pelo número de threads definido em thread_count

    end = clock(); //Encerra o tempo de execução
    double exec_time = ((double)(end - start)) / CLOCKS_PER_SEC; //Calcula o tempo de execução em ms
    exec_time *= 1000;
    printf("O tempo de execução é: %lfms\n", exec_time);
    return 0;
}

void AreaThread()
{
  const double ALT_TRAPZ = COMPRIMENTO / TRAPZ_NUM; //Calcula a altura de cada trapézio
#ifdef _OPENMP //Se a máquina possui a biblioteca openMP:
  int thread_id = omp_get_thread_num(); //Obtém número da thread
  const int  TRAPZ_POR_THREAD = TRAPZ_NUM / omp_get_num_threads(); // Obtém o número de trapézios que cada thread calculará

#else //Se não tem a biblioteca:
    int thread_id = 0; //Assume que só há somente uma thread, que calculará a área de todos os trapézios (execução serial)
    const int TRAPZ_POR_THREAD = TRAPZ_NUM;
#endif
 for(int i = 0; i < TRAPZ_POR_THREAD; i++) //Para cada trapézio a ser calculado...
 {
  double coluna_anterior = (thread_id + i) * ALT_TRAPZ; //Define a posição no eixo x das colunas anterior e atual (as bases do trapézio)
  double coluna_atual = coluna_anterior + ALT_TRAPZ;
  double altura_anterior = func(coluna_anterior); // Adquire as posições correspondentes no eixo Y (tamanho das bases)
  double altura_altual = func(coluna_atual);

  # pragma omp critical //Define área crítica
   Area += ALT_TRAPZ * (altura_altual + altura_anterior) / 2; // Calcula a área do trapézio e soma à área total
  
 }
}
