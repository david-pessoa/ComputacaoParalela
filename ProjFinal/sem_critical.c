#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <pthread.h>
#include <gmp.h>

//Executar no replit:
//1) Abra a shell
//2) Digite nix-shell -p gmp
//3) Digite gcc -o programa main.c -lgmp
//4) Execute ./programa

#define FRAC 48 //Número de frações a serem calculadas (66 é o limite)
sem_t semaphore; //Declara semáforo

mpf_t Euler;

struct ThreadArgs //struct contendo:
{
  int id; //id da thread
  int total_threads;
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
  for(int i = 1; i < FRAC; i++)
  {
    mpz_mul_ui(vetor[i], vetor[i - 1], i);//Os resultados ficam guardados dentro do vetor
  }
}

void* calcula_fracoes(void *args)
{
  struct ThreadArgs* t_args = (struct ThreadArgs*)args; //realiza o casting e extrai os valores passados para args
  int index = t_args->id; //id thread
  int num_threads = t_args->total_threads;
  mpz_t* denominadores = t_args->vetor; //vetor de denominadores
  mpf_t numerador, soma, frac;
  mpf_init(numerador); mpf_init(soma); mpf_init(frac);
  mpf_set_ui(soma, 0);
  mpf_set_ui(frac, 0);
  mpf_set_ui(numerador, 1);

  int inicio = (FRAC / num_threads) * index; //calcula indíces de início e fim da iteração no for
  int fim = (FRAC / num_threads) * (index + 1);

  for(int i = inicio; i < fim; i++)
  {
  mpf_div_ui(frac, numerador, mpz_get_ui(denominadores[i]));//calcula fração e adiciona valor a Euler
  mpf_add(soma, soma, frac);
  }
  sem_wait(&semaphore);
    mpf_add(Euler, Euler, soma);
  sem_post(&semaphore);

  pthread_exit(NULL); // encerra a thread
}

int main(int argc, char* argv[]) 
{
  char *endptr;
  int num_threads = (int)strtol(argv[1], &endptr, 10);
  mpf_set_default_prec(100000);
  mpf_init(Euler); //Número de Euler a ser calculado 
  mpf_set_d(Euler, 0);
  struct ThreadArgs args[num_threads]; //Vetor de argumentos da thread
  pthread_t threads[num_threads]; //Vetor de threads
  mpz_t *fat = malloc(FRAC * sizeof(mpz_t)); //Aloca espaço para vetor com os fatoriais de 0 a N - 1
  if (fat == NULL) 
  {
      perror("Falha ao alocar memória");
      exit(EXIT_FAILURE);
  }
  zera_vetor(fat, num_threads); //zera o vetor fat
  fatorial(fat); //Preenche o vetor com os fatoriais

  sem_init(&semaphore, 0, 1); //Inicia semáforo
  for(int i = 0; i < num_threads; i++) //Para cada loop:
  {
    args[i].id = i; //Atribui id à thread
    args[i].vetor = fat; //Coloca o vetor no argumento
    args[i].total_threads = num_threads;
    pthread_create(&threads[i], NULL, &calcula_fracoes, (void*)&args[i]);
  }

  //Aguarda todas as threads encerrarem usando pthread_join()
  for(int j = 0; j < num_threads; j++)
  {
    pthread_join(threads[j], NULL);
  }
  free(fat);
  sem_destroy(&semaphore); //Destrói semáforo
  gmp_printf("Euler: %.30113Ff\n", Euler); // 30.113 casas
  printf("Tempo: %lfms\n", exec_time);

  return 0;
}
