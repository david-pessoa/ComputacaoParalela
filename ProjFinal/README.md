## 1) Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
* Tempo de execução para 1 processador: <img width="128" alt="sem1" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/1c09493f-299c-475b-80b0-a712f94e13cd">
  Valor calculado do número de Euler para 1 processador em: `sem_1.txt`.
* Tempo de execução para 2 processadores: <img width="128" alt="sem2" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/098b13b4-c1d7-4349-aaab-c736af6b45fd">
  Valor calculado do número de Euler para 2 processadores em: `sem_2.txt`.
* Tempo de execução para 4 processadores: <img width="128" alt="sem4" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/fafe20b9-fae2-4eac-a63d-5cee55ed6c3f">
  Valor calculado do número de Euler para 4 processadores em: `sem_4.txt`.
* Tempo de execução para 6 processadores: <img width="130" alt="sem6" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/e5189c3d-e396-4bce-a5ee-1e978b4c2ede">
  Valor calculado do número de Euler para 6 processadores em: `sem_6.txt`.
* Tempo de execução para 8 processadores: <img width="129" alt="sem8" src="https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/051d3184-9f11-4a73-b854-5ef1b5b3c09d">
  Valor calculado do número de Euler para 8 processadores em: `sem_8.txt`.

### Gráfico com os tempos de execução
![tempos_sem_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/7c49e366-d20d-46fe-abff-e778928c1570)

## 2) Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.
![speedup_sem_critical](https://github.com/david-pessoa/ComputacaoParalela/assets/104323068/2b648e3e-e230-4588-af03-3f0697611030)

## 3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Usando a diretiva critical, estamos usando outra biblioteca para aplicar o paralelismo, podendo causar certa diferença nos tempos de execução e speedup.

* Tempo de execução para 1 processador: <img width="128" alt="omp1" src="https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/4080479e-f9f7-4b60-8f47-bd6da520813d">
  Valor calculado do número de Euler para 1 processador em: `omp_1.txt`.
* Tempo de execução para 2 processadores: <img width="128" alt="omp2" src="https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/8636924f-2e62-43c2-9d42-12dd496ebb70">
  Valor calculado do número de Euler para 2 processadores em: `omp_2.txt`.
* Tempo de execução para 4 processadores: <img width="128" alt="omp4" src="https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/2cad8730-b398-49f4-b521-2190c5e987ee">
  Valor calculado do número de Euler para 4 processadores em: `omp_4.txt`.
* Tempo de execução para 6 processadores: <img width="128" alt="omp6" src="https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/908d32f6-53ef-409b-801f-874a6672c92d">
  Valor calculado do número de Euler para 6 processadores em: `omp_6.txt`.
* Tempo de execução para 8 processadores: <img width="128" alt="omp8" src="https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/759e3522-9476-47b8-bb2f-8a090fe273ab">
  Valor calculado do número de Euler para 8 processadores em: `omp_8.txt`.

### Gráfico com os tempos de execução
![tempos com critical](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/5bc7b178-3dd6-4e1a-a66d-0c899a40d39e)

![speedup com critical](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/8b76d479-f179-46db-9807-82b5cc7eec69)


## Como compilar o programa na plataforma disponibilizada e executa-lo:
  * Passo a passo para executar `sem_critical.c`:
    1) Digite gcc -o programa sem_critical.c -lgmp
    2) Execute o programa informando o número de threads (ex: 2 threads, `./programa 2`)
   
  * Passo a passo para executar `omp_critical.c`:
    1) Digite gcc -o programa omp_critical.c -fopenmp -lm -lgmp
    2) Execute o programa informando o número de threads (ex: 2 threads, `./programa 2`)

    
## Como comprovar que os resultados propostos foram alcançados.

### [Especificações do processador usado nos exercícios no arquivo cpuinfo.txt](https://github.com/david-pessoa/ComputacaoParalela/blob/main/ProjFinal/cpuinfo.txt)
