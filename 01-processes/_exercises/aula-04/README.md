## Questão 1
Lista pública no CD-MOJ
Resolva os exercícios propostos na lista pública do CD-MOJ.
Para ganhar credenciais de acesso à lista, envie uma mensagem para @mojinhobot, 
no telegram AQUI, com o conteúdo:

    participar bcr-FSO-2021_1-processos-e-sinais
Os usuários são compartilhados com as listas de EDA2


## Questão 2
O que é um processo Zumbi? Escreva um programa que crie processos zumbis.

### Resposta
respondido em [../aula-03/README.md#questao-3](../aula-03/README.md#questao-3)


## Questão 3 
Resolva http://www.brunoribas.com.br/so/2019-1/pratica/multiplicacao-matriz.html


## Questão 4
Resolva http://wiki.inf.ufpr.br/maziero/doku.php?id=so:criacao_de_processos


## Questão 5
Resolva http://www.dei.isep.ipp.pt/~orlando/so2/processos.htm


## Questão 6
Familiarize-se com as chamadas: execve(2), clone(2)


## Questão pré 7

    ...
    int main() {
      pid1=fork();
      pid2=fork();
      printf("oi");
    }
1. Quantas vezes é apresentada a frase `oi`? Justifique.

### Resposta
[exp.c](exp.c) e [árvore de processos](./exp-process-tree.png)


## Questão 7
Considere a seguinte parte de um programa

    int main()
    {
      ...
      pid2=0;
      for(i=0;i<2;i++)
      {
        pid=fork();
        if(pid==0)
          pid2=fork();
        if(pid2==0)
          printf("Exame de SO\n");
      }
      ...
    }
1. Quantas vezes é apresentada a frase Exame de SO? Justifique
1. Veja a discussão deste problema nesse 
[vídeo](https://www.youtube.com/watch?v=C4dWwWAd5Wg&t=1281s) 


## Questão 8
Tendo um vetor de inteiros com mil posições, crie um processo e faça o seguinte:   
- Os dois processos (pai e filho) fazem o seguinte cálculo: 
`resultado[i]=dados[i]*4+20`
- Cada processo é responsável pelo cálculo de 500 posições do vetor dados, 
colocando o resultado no vetor resultado
- Os resultados devem ser apresentados seguindo a ordem do vetor (de [0,499] e 
depois [500,999])


## Questão 9
Faça um programa que crie 6 processos e:
- Cada processo escreve 200 números:
  - 1o processo [0,200];
  - 2o processo [201,400];
  - 3o processo [401,600];
  - 4o processo [601,800];
  - 5o processo [801,1000];
  - 6o processo [1001,1200];
- O processo pai tem de esperar que TODOS os processos filho terminem


## Questão 10
Tendo um vetor de 1000 posições, faça um programa que crie 5 processos e:
- Dado um número, procurar esse número no vetor;
- Cada processo filho, procura 200 posições;
- O processo que encontrar o número, deve imprimir a posição do vetor onde se 
encontra. Também deve "retornar" como valor de saída o número do processo 
(1,2,3,4,5);
- Os processos que não encontrarem o número devem "retornar" como valor de 
saída o valor 0;
- O processo pai tem de esperar que todos filhos terminem e imprimir o número do
 processo onde esse número foi encontrado (1,2,3,4,5)

NOTA: O vetor não possui números repetidos