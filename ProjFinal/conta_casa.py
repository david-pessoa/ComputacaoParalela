# Nome do arquivo que contém o número
arquivo1 = './ProjFinal/Euler_million.txt'
arquivo2 = './ProjFinal/Valores_Euler_Omp/omp_1.txt'

# Ler o conteúdo do arquivo
with open(arquivo1, 'r') as f:
    Euler_verdadeiro = f.read()

with open(arquivo2, 'r') as f:
    Euler_duvidoso = f.read()

casas_corretas = 0
i = 0
while True:
    if Euler_verdadeiro[i] != Euler_duvidoso[i]:
        break
    else:
        casas_corretas += 1
    i += 1

print(f"O número obtido contém {casas_corretas} casas corretas")




