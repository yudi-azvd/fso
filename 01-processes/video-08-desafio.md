# Desafio

LEMBRE que é possível reinstalar o mesmo sinal com outra função.

     PAI
      |
    FILHO
   /     \
NETO1   NETO2

A família de processos pode ficar nesse estado por tempo indeterminado,
até que o PAI receba SIGINT.
- PAI envia SIGUSR1 para FILHO
  - FILHO envia SIGUSR1 para NETO1
    - NETO1 imprime seu próprio PID

- PAI envia SIGUSR2 para FILHO, 
  - FILHO envia SIGUSR2 para NETO2
    - NETO2 imprime o PID de seu pai

Daqui pra frente o PAI ignora SIGUSR1 e SIGUSR2.

- PAI recebe SIGINT e envia SIGINT para FILHO
- FILHO recebe SIGINT e envia SIGINT para NETOS
- NETO1 e NETO2 recebem SIGINT
  - NETO1 envia SIGTERM para FILHO
  - NETO2 dorme por 4s e depois envia SIGTERM para FILHO
- FILHO recebe SIGTERM duas vezes, envia SIGTERM para PAI e morre
- PAI recebe SIGTERM, imprime "ADEUS" e morre.

Idealmente o pai apenas morre quando ele recebe o sinal SIGTERM do 
filho. Vou considerar apenas esse caso.

Eu, exercitando o sistema, vou enviar os sinais SIGUSR1 SIGUSR2 e SIGINT.
