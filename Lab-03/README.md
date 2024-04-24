# Paralelismo com OpenMP

## Foram criadas dois programas para calcular a área da função senoide utilizando trapézios. O programa open_parallel.c utiliza semáforos da biblioteca <semaphore.h> para isolar a região crítica do código, enquanto o programa open_critical.c utiliza a diretiva #pragma omp critical da biblioteca <omp.h> para controlar a zona crítica. 

# Exercícios:
## 1) Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução

### Gráfico de tempo de execução:
![image](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/e452ea31-54af-4da4-8abd-f3b8653ebcdf)


## 2) Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.

No gráfico a seguir podemos ver os valores de speedup quanto mais adicionamos processadores.

###Gráfico de speedup:
![image](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/b0e44935-2ffc-4822-bf0f-63c694da9561)


## 3) Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Utilizando a diretiva critical, é mais fácil isolar e controlar a zona crítica do código quando comparado com usar a biblioteca de semáforos; apesar disso, as duas soluções são praticamente equivalentes. Resolvemos usar o semáforo nas questões 1 e 2 pois não é possível obter um resultado paralelo coerente neste problema sem usar algum tipo de controle. Isto porque adicionar a área de cada trapézio (thread) na área total é uma tarefa necessariamente serial.

### Gráficos de tempo de execução e speedup com diretiva critical:
![image](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/19a24ec2-617e-46f4-b940-98c038409e8e)

![image](https://github.com/david-pessoa/ComputacaoParalela/assets/112708096/98f813a7-ca78-4a09-8823-be8c7a077372)

## Especificações do processador utilizado na AWS:
[CPU Info.txt](https://github.com/david-pessoa/ComputacaoParalela/files/15085570/CPU.Info.txt)#
