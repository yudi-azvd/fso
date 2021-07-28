## Questão 1
Familiarize-se com a chamada: fork(2), wait(2), execl(3);
Descreva o funcionamento das funções listadas acima.

### Resposta
**`fork`**: cria um processo filho duplicando o processo pai, mas possui um PID
diferente e mais um monte de coisa (vide `man fork`). É uma chamada de sistema
**blocante**.

Retorna duas vezes: uma vez no processo pai, uma vez no processo filho.

**`wait`**: faz o processo pai esperar por uma mudança de estado de um processo 
filho. Mudança de estado pode ser:
- processo filho terminou
- processo filho foi parado por um sinal
- processo filho foi continuado por um sinal

Pode ser usada pra recuperar o valor de retorno de um processo filho.

**`execl`**: substitui a imagem atual de um processo pela imagem de um novo
processo.


## Questão 2
Na figura 1 são mostrados três estados de processos. 

![estados de um processo](grafo-estados.png)

Na teoria, com três estados poderia haver seis transições, duas para cada estado. Contudo, somente quatro transições são mostradas. Há alguma circunstância na qual uma delas ou ambas as transições não ilustradam possam ocorrer?

### Resposta
Segundo Tanenbaum, um processo em estado conceitualmente pronto pode ser 
parado por que a CPU precisa alocar recursos para outro processo por um tempo.


## Questão 3
O que é um processo Zumbi? Explique como que um processo passe para o estado de Zumbi.

### Resposta
É um processo que terminou de executar e só está esperando o processo pai pegar
os resultados do processo filho. Enquanto o processo filho espera ele é zumbi e
ele não morre.

Caso especial: se o pai de um zumbi morre, o processo `init` (processo de ID 1),
assume a paternidade do zumbi e recupera o valor de retorno do processo órfão, 
assim deixando de ser zumbi. Se o ex-zumbi rodar `getppid()` (get parent PID) a 
função deve retornar 1.

Notes in the manual pages (`man wait`)
> A child that terminates, but has not been waited for becomes a "zombie".

## Questão 4
Escreva um programa que gere um processo Zumbi.

### Resposta
[`questao-4-zombie-process.c`](questao-4-zombie-process.c).

Rodar `ps x` para verificar o zombie. O que deve aparecer é algo do tipo 

    PID ... ... ./a.out
    PID ... ... [./a.out] <defunct> // zumbi


## Questão 5
Considere a seguinte parte de um programa: 

    p=fork();
    a=fork();

    printf("Sistemas Operacionais\n");

Quantas vezes é apresentada "Sistemas Operacionais"? Justifique.

Quantos processos são criados pelo programa?


## Questão 6
Faça um programa que crie 2 processos e:
- Escreve `Eu sou o pai` no processo pai;
- Escreve `Eu sou o 1o filho` no primeiro filho;
- Escreve `Eu sou o 2o filho` no segundo filho.


## Questão 7
Considere o seguinte pedaço de código em C:  

    for(i=0;i<4;i++)
      pid=fork();
    printf("FSO\n");

Quantos processos são criados por este programa? Justifique.
Quantas vezes é apresentado "FSO"? Justifique.