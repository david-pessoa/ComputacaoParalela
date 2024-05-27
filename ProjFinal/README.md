# Evolução do projeto:
Nesta seção, será abordada a evolução do projeto. Para resolvermos o problema, desenvolvemos duas soluções, apresentadas a seguir. Portanto, esta seção será dividida em três: duas para discutir cada solução criada individualmente e, ao final, uma conclusão.

## `sem_critical.c`
Nesta solução, utilizamos a biblioteca `pthreads.h` para paralelização do código e `semaphore.h`para isolamento da região crítica. Inicialmente, propôs-se criar um vetor do tipo o tipo `unsigned long long int` para armazenar os valores dos denominadores das frações da série de Taylor. Além disso, cada thread ficaria responsável por calcular uma fração que é adicionada à variável global Euler do tipo `long double`. Porém, tal técnica se mostrou ineficiente, pois só conseguimos obter `65 casas decimais` além de possuir um alto custo por conta do overhead de threads. Pensando nisso, chegamos numa nova versão, que utiliza a biblioteca `gmp.h` para obter mais casas decimais (logo, o tipo do vetor se tornou: `mpz_t`, usado para números muito grandes, e o tipo de Euler `mpf_t`) e mudamos o código de execução das threads para que elas calculem mais de uma fração. Com essas mudanças, o número de casas decimais saltou para `30.113 casas` (chamamos: `mpf_set_default_prec(100000)`) e o tempo de execução diminui significativamente, embora tenhamos conseguido apenas `18 casas decimais` calculadas corretamente nesta versão.

## `omp_critical.c`
Nesta solução, utilizamos a biblioteca `omp.h` para paralelização do código e a diretiva `# pragma critical` para isolamento da região crítica. Também foram inicialmente utilizados vetores de tipo `unsigned long long int`  para armazenar os valores dos denominadores das frações, que também foi alterado para o tipo `mpz_t` utilizando a biblioteca `gmp.h`. Desse modo, o número de Euler resultante também saltou para `30.113 casas decimais`, pois chamamos: `mpf_set_default_prec(100000)`. Outro ponto importante é que este código estava usando uma biblioteca do Windows para contar o tempo de execução, mas isso foi alterado para não ter nenhuma contagem de tempo no código. Ao invés disso, utilizamos o comando `time` na chamada do executável para contar o tempo. Diferentemente de `sem_critical.c`, a versão final de `omp_critical.c` calculou `250 casas decimais` corretamente.

## Conclusão

# Funções utilizadas da biblioteca `gmp.h` e algoritmo por trás:
## Inteiros

  1) `mpz_init()`
  2) `mpz_set_ui()`
  3) `mpz_mul_ui()`

## Números Ponto flutuante
  1) `mpf_init()`
  2) `mpf_set_ui()`
  3) `mpf_div_ui()`
  4) `mpf_get_ui()`
  5) `mpf_add()`
  6) `mpf_set_default_prec()`
  7) `mpf_set_d()`





# Exercícios
## 1) Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
* Tempo de execução para `sem_critical.c`:
  ![Tempos sem_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/62566949-b901-4137-a68b-0e44fac29967)
  
### Gráfico com os tempos de execução de `sem_critical.c`


## 2) Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.


## 3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Usando a diretiva critical, estamos usando outra biblioteca para aplicar o paralelismo, podendo causar certa diferença nos tempos de execução e speedup.

* Tempo de execução para `omp_critical.c`:
  ![Tempos com_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/5c28ac5f-ca52-4af0-bccc-cc482dddf9d5)

### Gráfico com os tempos de execução de `omp_critical.c`


### [Especificações do processador usado nos exercícios no arquivo cpuinfo.txt](https://github.com/david-pessoa/ComputacaoParalela/blob/main/ProjFinal/cpuinfo.txt)

## Como compilar o programa na plataforma disponibilizada e executá-lo:
  * Passo a passo para executar `sem_critical.c`:
    1) Digite gcc -o programa sem_critical.c -lgmp
    2) Execute o programa informando o número de threads (ex: 2 threads, `./programa 2`)
   
  * Passo a passo para executar `omp_critical.c`:
    1) Digite gcc -o programa omp_critical.c -fopenmp -lm -lgmp
    2) Execute o programa informando o número de threads (ex: 2 threads, `./programa 2`)
    3) Se quiser saber o tempo de execução do programa, coloque o comando `time` antes da chamada do executável (ex: `time ./programa 2`)

    
## Como comprovar que os resultados propostos foram alcançados.
Como instalar a biblioteca gmp.h: `sudo apt-get install libgmp3-dev`

Como instalar a biblioteca omp.h:  `sudo apt-get install libomp-dev`



