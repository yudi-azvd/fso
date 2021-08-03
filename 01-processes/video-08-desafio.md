# Desafio

LEMBRE que é possível reinstalar o mesmo sinal com outra função.

        100    | PAI
         |     |
        101    | FILHO
        / \    |
      102 103  | NETO1 e NETO2

- [x] PAI envia SIGUSR1 para FILHO
  - [x] FILHO envia SIGUSR1 para NETO1
    - [ ] NETO1 imprime seu próprio PID

- [x] PAI envia SIGUSR2 para FILHO, 
  - [x] FILHO envia SIGUSR2 para NETO2
    - [ ] NETO2 imprime o PID de seu pai

- [ ] PAI recebe SIGINT e envia SIGINT para FILHO
- [ ] FILHO recebe SIGINT e envia SIGINT para NETOS
- [ ] NETO1 e NETO2 recebem SIGINT
  - [ ] NETO1 envia SIGTERM para FILHO
  - [ ] NETO2 dorme por 4s e depois envia SIGTERM para FILHO
- [ ] FILHO recebe SIGTERM duas vezes, envia SIGTERM para PAI e morre
- [ ] PAI recebe SIGTERM, imprime "ADEUS" e morre.

Idealmente o pai apenas morre quando ele recebe o sinal SIGTERM do 
filho. Vou considerar apenas esse caso.

Eu, exercitando o sistema, vou enviar os sinais SIGUSR1 SIGUSR2 e SIGINT.
