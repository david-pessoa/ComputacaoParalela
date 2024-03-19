# Multiplicação matriz-vetor
O programa Multimatrizes.c realiza a multiplicação entre as matrizes A[3][8] e B[8][1], gerando um vetor C[3].
Para realizar esta operação por meio de threads, utilizou-se uma thread para gerar cada elemento do vetor C  
pela fórmula: C[m] = ∑(A[m][i] * B[i][0]).

## Constantes:
m = 3 --> Número de linhas da matriz A e itens em C  
n = 8 --> Número de colunas de A e linhas de B

## Funções criadas:  
* `void* multiplica(void *args)`
  * Esta função é executada pelas threads para gerar um valor do vetor C, conforme a fórmula descrita anteriormente
    
* `void multiplica_serial(int vetor[])`
  * Esta função executa a multiplicação entre as matrizes A e B de maneira serial (sem threads) e grava o resultado no vetor C passado
  
* `void zera_vetor(int vetor[], int k)`
  * Esta função torna todos os elementos do vetor iguais a zero
  
* `void show_vetor(int vetor[], int k)`
  * Esta função é usada para exibir todos os elementos de um vetor (no caso, o vetor resultante C)

## struct ThreadArgs
Esse struct foi criado para armazenar o vetor C e o índice do elemento de C que será calculado pela thread.  
O vetor args criado a partir desse struct, passa pelo casting (*void) e é então passado como argumento para  
a função pthread_create() para que possa ser usado como o parâmetro *args na função multiplica.

## pthread_join()
É importante que essa função seja usada para que o programa não encerre antes das threads terem terminado de executar,  
pois, caso contrário, poderíamos obter um resultado diferente do esperado.

# Execução do programa na AWS
![](https://github.com/david-pessoa/ComputacaoParalela/blob/David/Lab%2002/executa%20multimatrizes.png)

# Lab02b
## Execução do programa matriz.c
![](https://github.com/david-pessoa/ComputacaoParalela/blob/David/Lab%2002/executa%20matrizes.png)  
## Exercícios
1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
   
![](https://github.com/david-pessoa/ComputacaoParalela/blob/David/Lab%2002/Gra%CC%81fico%20dos%20tempos.jpeg) <!--Foto gráfico dos tempos-->

2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.
 ![](https://github.com/david-pessoa/ComputacaoParalela/blob/David/Lab%2002/Gra%CC%81fico%20dos%20speed%20up.jpeg) <!--Foto gráfico speed up-->

3. Como você acha que poderia melhorar o seu algoritmo para obter maior benefício com o paralelismo? Para provar seu ponto, refaça a solução com essa abordagem e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores. <!--Não sei como fazer aaaaa-->

## Especificações do processador
![](https://github.com/david-pessoa/ComputacaoParalela/blob/David/Lab%2002/htop.png)


  
