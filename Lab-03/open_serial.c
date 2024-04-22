#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>
#include <math.h>

#define PI 3.1415
#define COMPRIMENTO 24 * PI

// Calcular a área para comprimento 24π
// Função f(x) = sen(x) + 2

double func(double x)
{
    return sin(x) + 2;
}

//Inicia com x = 0
// comprimento p/ cada thread = 24π / num_threads
int main()
{
    int num_threads = 8;
    double ColAnterior;
    double ColAtual = 0;

    double AltAnterior;
    double AltAtual = func(ColAtual);
    const double COMP_THREAD = COMPRIMENTO / num_threads;
    double Area = 0;

    while(ColAnterior < COMPRIMENTO)
    {
        ColAnterior = ColAtual;
        AltAnterior =  AltAtual;

        ColAtual += COMP_THREAD;
        AltAtual = func(ColAtual);

        //COMP_THREAD * (AltAnterior + AltAtual) / 2
        Area += COMP_THREAD * (AltAtual + AltAnterior) / 2;
    }
    printf("A área total aproximada é: %lf", Area);
    return 0;
}

