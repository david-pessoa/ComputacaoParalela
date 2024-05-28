# Evolução do projeto:
Nesta seção, será abordada a evolução do projeto. Para resolvermos o problema, desenvolvemos duas soluções, apresentadas a seguir. Portanto, esta seção será dividida em três: duas para discutir cada solução criada individualmente e, ao final, uma conclusão.

## `sem_critical.c`
Nesta solução, utilizamos a biblioteca `pthread.h` para paralelização do código e `semaphore.h`para isolamento da região crítica. Inicialmente, propôs-se criar um vetor do tipo o tipo `unsigned long long int` para armazenar os valores dos denominadores das frações da série de Taylor. Além disso, cada thread ficaria responsável por calcular uma fração que é adicionada à variável global Euler do tipo `long double`. Porém, tal técnica se mostrou ineficiente, pois só conseguimos obter `65 casas decimais` além de possuir um alto custo por conta do overhead de threads. Pensando nisso, chegamos numa nova versão, que utiliza a biblioteca `gmp.h` para obter mais casas decimais (logo, o tipo do vetor se tornou: `mpz_t`, usado para números muito grandes, e o tipo de Euler `mpf_t`) e mudamos o código de execução das threads para que elas calculem mais de uma fração. Com essas mudanças, o número de casas decimais saltou para `30.113 casas` (chamamos: `mpf_set_default_prec(100000)`) e o tempo de execução diminui significativamente, embora tenhamos conseguido apenas `18 casas decimais` calculadas corretamente nesta versão.

## `omp_critical.c`
Nesta solução, utilizamos a biblioteca `omp.h` para paralelização do código e a diretiva `# pragma critical` para isolamento da região crítica. Diferentemente do programa anterior, neste nós calculamos o fatorial dos denominadores individualmente por meio da função `fatorial()`. Além disso, cada thread é responsável por calcular o valor de mais de uma fração para que seja então adicionada à variável global Euler do tipo `mpf_t`. Desse modo, o número de Euler resultante também ficou com `30.113 casas decimais`, pois chamamos: `mpf_set_default_prec(100000)`. Outro ponto importante é que este código estava usando uma biblioteca do Windows para contar o tempo de execução, mas isso foi alterado para não ter nenhuma contagem de tempo no código. Ao invés disso, utilizamos o comando `time` na chamada do executável para contar o tempo. Diferentemente de `sem_critical.c`, a versão final de `omp_critical.c` calculou `250 casas decimais` corretamente.

## Conclusão
Observando os resultados finais, é possível concluir que o código utilizando a biblioteca OpenMP conseguiu mais performance quando comparado com o código utilizando a biblioteca Pthread, pois o código utilizando OpenMP ficou mais performático quanto mais threads foram adicionadas no seu processamento, enquanto o código de Pthread ficou com um tempo de execução quase constante. Provavelmente, isso se deve ao fato das diferentes estratégias empregadas para calcular os fatoriais dos números, então podemos concluir que calcular cada fatorial individualmente, é mais eficiente que armazenar números num vetor. Além disso, vale destacar que a diferença entre o número de casas decimais calculados se deve à diferença entre o número de frações a serem calculadas em cada programa, o que altera a precisão do número obtido.


# Funções utilizadas da biblioteca `gmp.h` e o que fazem
## Inteiros

  1) `mpz_init(MP_INT *integer)`: Inicializa uma variável do tipo mpz e coloca seu valor igual a 0.
  2) `mpz_set_ui(MP_INT *integer, unsigned long int initial_value)`: Inicializa uma variável do tipo mpz e coloca seu valor como sendo igual ao valor do tipo `unsigned int` passado por parâmetro.
  3) `mpz_mul_ui(MP_INT *product, MP_INT *multiplicator, unsigned long int multiplicand)`: Altera o valor de `product` para `multiplicator * multiplicand`.
  4) `mpz_get_ui(const mpz t op)`:  retorna o valor de op como `unsigned long`.

## Números Ponto flutuante
  1) `mpf_init(mpf_t x)`: Inicializa `x` com valor igual a 0.
  2) `mpf_set_ui(mpf_t rop, unsigned long int op)`: Inicializa uma variável do tipo mpf_t e coloca seu valor como sendo igual ao valor do tipo `unsigned int` passado por parâmetro.
  3) `mpf_div_ui(mpf t rop, const mpf t op1, unsigned long int op2)`: Altera o valor de `rop` para  `op1/op2`.
  4) `mpf_add(mpf t rop, const mpf t op1, const mpf t op2)`: Altera o valor de `rop` para  `op1 + op2`.
  5) `mpf_set_default_prec(mp_bitcnt_t prec)`: Configura a precisão padrão para ser ao menos igual ao valor de `prec`
  6) `mpf_set_d(mpf t rop, double op)`: Inicializa uma variável do tipo mpf_t e coloca seu valor como sendo igual ao valor do tipo `double` passado por parâmetro.

Usamos as funções do tipo inteiro, somente no `sem_critical.c` para calcular os valores dos fatoriais, sendo a `mpz_mul_ui()` para obter o valor de um novo fatorial a partir do anterior e `mpz_get_ui()` para calcular obter o último fatorial calculado. (ex: 7! = 7 * 6!, `mpz_get_ui()` obteria o valor 6! do vetor e `mpz_mul_ui()` multiplicaria por 7). 

Enquanto usamos as funções do tipo ponto flutuante para poder lidar com a variável Euler. Usamos `mpf_div_ui()` para calcular o valor de cada fração a partir da divisão 1/denominador. Além disso, usamos `mpf_add()` para calcular o valor da soma das frações que cada thread é responsável por calcular e depois a adição desta soma à variável global Euler.

# Exercícios
## 1) Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
* Tempo de execução para `sem_critical.c`:
  ![Tempos sem_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/62566949-b901-4137-a68b-0e44fac29967)
  
### Gráfico com os tempos de execução de `sem_critical.c`
<img width="399" alt="image" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/2e8d77da-bf35-471a-9d5f-82fda233bc73">

## 2) Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.
<img width="404" alt="image" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/7c8b1d63-fc97-423d-a07f-751aa47f9f81">


## 3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Usando a diretiva critical, estamos usando outra biblioteca para aplicar o paralelismo, podendo causar certa diferença nos tempos de execução e speedup.

* Tempo de execução para `omp_critical.c`:
  ![Tempos com_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/5c28ac5f-ca52-4af0-bccc-cc482dddf9d5)

### Gráfico com os tempos de execução de `omp_critical.c`
<img width="384" alt="image" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/420ef4f1-7f98-4e8a-8eea-9570af2b35fd">

### Gráfico com o speedup de `omp_critical.c`
<img width="425" alt="image" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/579acb1f-1ede-445c-8dab-3df617bf4fb1">


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

### [Especificações do processador usado nos exercícios no arquivo cpuinfo.txt](https://github.com/david-pessoa/ComputacaoParalela/blob/main/ProjFinal/cpuinfo.txt)

