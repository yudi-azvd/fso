# Alguns aprendizados

[Solução do professor](https://www.youtube.com/watch?v=YzaDM4QHjN8)

- Não usar a mesma variável que pode ser influenciada por processos diferentes. 
Isso pode causar uma race condition. É o que acontecia em 
[matriz.c](matriz.c#L67):67. (Eu entendi como essa situação causava uma race 
condition, mas ainda não entendo como essa situação causa o TLE na correção do 
juiz)
- Em [matriz-v2.c](matriz-v2.c), o processo pai acompanha o "progresso" do 
processos filhos com uma variável para cada processo. Para $N$ processos, 
"bastaria" criar um vetor com $N$ posições para os sinais de cada processo filho
e outro vetor com $N$ posições para as funções do pai que tratam esses sinais.

O professor fez assim:

```c
signal(CHILD_1_SIGNAL, handle_child_1_sig);
signal(CHILD_2_SIGNAL, handle_child_2_sig);
// ...
void handle_child_1_sig(int sig) { child1sig++ };
void handle_child_2_sig(int sig) { child2sig++ };
```

Não seria melhor assim?
```c
int children_sigs[] = {CHILD_1_SIGNAL, CHILD_2_SIGNAL, ...};
// ...
signal(CHILD_1_SIGNAL, handle_child_sig);
signal(CHILD_2_SIGNAL, handle_child_sig);
// ...
void handle_child_sig(int sig) {
  child_sig = children_sigs[sig];
  child_sig++;
};
```
  
- [matriz-v3.c](matriz-v3.c): solucação iterativa para $N$ processos filhos.
Só tem que arrumar o `remainder` para divisões não exatas
