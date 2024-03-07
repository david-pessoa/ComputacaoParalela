# Multiplicação matriz-vetor
O programa matriz.c realiza a multiplicação entre as matrizes A[3][8] e B[8][1], gerando um vetor C[3].
Para realizar esta operação por meio de threads, utilizou-se uma thread para gerar cada elemento do vetor C  
pela fórmula: C[m] = ∑(A[m][i] * B[i][0]).

## Constantes:
m = 3 --> Número de linhas da matriz A e itens em C  
n = 8 --> Número de colunas de A e linhas de B

## Funções criadas:  
* void* multiplica(void *args):
  * Esta função é executada pelas threads para gerar um item de C

* void zera_vetor(int vetor[], int k):
  * Esta função torna todos os elementos do vetor iguais a zero
  
* void show_vetor(int vetor[], int k):
  * Esta função é usada para exibir todos os elementos de um vetor (no caso, o vetor resultante C)

## struct ThreadArgs
Esse struct foi criado para armazenar o vetor C e o índice do elemento de C que será calculado pela thread.  
O vetor args criado a partir desse struct, passa pelo casting (*void) e é então passado como argumento para  
a função pthread_create()

## pthread_join()
É importante que essa função seja usada para que o programa não encerre antes das threads terem terminado de executar
  
