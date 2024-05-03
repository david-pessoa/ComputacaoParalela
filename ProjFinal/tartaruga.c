#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <gmp.h>

//Executar no replit:
//1) Abra a shell
//2) Digite nix-shell -p gmp
//3) Digite gcc -o programa main.c -lgmp
//4) Execute ./programa

#define N 40 //Número de threads
//#define FRAC 100 //Número de frações a serem calculadas
//#define FRAC_THREAD FRAC/N //Número de frações por thread
sem_t semaphore; //Declara semáforo

mpf_t Euler;

struct ThreadArgs //struct contendo:
{
  int id; //id da thread
  mpz_t* vetor; //vetor de denominadores
};

void zera_vetor(mpz_t* vetor, int k) //Função para zerar o vetor (evita erros)
{
  for(int i = 0; i < k; i++)
  {
    mpz_init(vetor[i]);
    mpz_set_ui(vetor[i], 0); //Atribui zero a todos os elementos do vetor
  }
}

void show_vetor(mpz_t* vetor, int k) // Função para exibir todos os elementos do vetor
{
  printf("Vetor final: [");
  for(int i = 0; i < k; i++)
  {
    gmp_printf("%Zd, ", vetor[i]);
  }
  printf("]\n");
}

void fatorial(mpz_t* vetor) //Função para calcular os fatoriais nos denominadores
{
  mpz_set_ui(vetor[0], 1);
  for(int i = 1; i < N; i++)
  {
    mpz_mul_ui(vetor[i], vetor[i - 1], i);//Os resultados ficam guardados dentro do vetor
  }
}

void* calcula_fracoes(void *args)
{
  struct ThreadArgs* t_args = (struct ThreadArgs*)args; //realiza o casting e extrai os valores passados para args
  int index = t_args->id; //id thread
  mpz_t* denominadores = t_args->vetor; //vetor de denominadores
  mpf_t numerador, soma;
  mpf_init(numerador); mpf_init(soma);
  mpf_set_ui(numerador, 1);
  mpf_div_ui(soma, numerador, mpz_get_ui(denominadores[index]));//calcula fração e adiciona valor a Euler
  //gmp_printf("%.60Ff\n", soma);
     sem_wait(&semaphore);
    mpf_add(Euler, Euler, soma);
     sem_post(&semaphore);

  pthread_exit(NULL); // encerra a thread
}

int main(void) 
{
  mpf_init(Euler); //Número de Euler a ser calculado 
  mpf_set_d(Euler, 0);
  struct ThreadArgs args[N]; //Vetor de argumentos da thread
  pthread_t threads[N]; //Vetor de threads
  clock_t start, end; //Variáveis para contar o tempo de início o fim da execução
  start = clock(); //Inicia contagem de tempo
  mpz_t *fat = malloc(N * sizeof(mpz_t)); //Aloca espaço para vetor com os fatoriais de 0 a N - 1
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

  gmp_printf("Euler: %.65Ff\n", Euler);
  printf("Tempo: %lf\n", exec_time);
  //show_vetor(fat,N);
  return 0;
}