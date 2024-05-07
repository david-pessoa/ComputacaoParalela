#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <gmp.h>
#include <windows.h>

#define ELEMENTOS 128

mpf_t Euler;

void fatorial(mpf_t result, int n) 
{
    mpf_set_ui(result, 1);  // Set result to 1

    for (int i = 1; i <= n; i++) 
    {
        mpf_mul_ui(result, result, i);  // result *= i
    }
}

void Taylor();

int main(int argc, char* argv[])
{
    LARGE_INTEGER start, end, freq;

    QueryPerformanceFrequency(&freq);  // Get the frequency of the high-resolution performance counter

    QueryPerformanceCounter(&start);  // Get the current count

    mpf_set_default_prec(100000);
    mpf_init(Euler); //Numero de Euler a ser calculado
    mpf_set_d(Euler, 0); //Inicializa Euler com 0

    int thread_count = strtol(argv[1], NULL, 10);
    omp_set_num_threads(thread_count);

# pragma omp parallel num_threads(thread_count)
    Taylor();

    QueryPerformanceCounter(&end);  // Get the current count again
    double exec_time = ((double)end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;  // Calculate the elapsed time in milliseconds
    gmp_printf("Euler: %.30113Ff\n", Euler); // 30.113 casas
    printf("Tempo: %lfms\n", exec_time);
    mpf_clear(Euler);
    return 0;
}

void Taylor() 
{ 
    int thread_id = omp_get_thread_num();
    const int NUM_THREADS = omp_get_num_threads();
    const int ELEMENTOS_POR_THREAD = ELEMENTOS / NUM_THREADS;
    mpf_t soma_thread, temp, fact;
    mpf_init(soma_thread);
    mpf_init(temp);
    mpf_init(fact);

    for (int i = 0; i < ELEMENTOS_POR_THREAD; i++)
    {
        fatorial(fact, thread_id + (i * NUM_THREADS));
        mpf_ui_div(temp, 1, fact);  // temp = 1 / fact
        mpf_add(soma_thread, soma_thread, temp);
    }

    #pragma omp critical
    mpf_add(Euler, Euler, soma_thread);

    mpf_clear(soma_thread);
    mpf_clear(temp);
    mpf_clear(fact);
}

