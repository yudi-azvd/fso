# Imprime a árvore de processos a partir de a.out
# com os PIDs decada processo.

# ps -x --forest | grep a.out | grep -v 'grep' | sed -E 's/^([\s]+?[0-9]+)(.*)/\1/'
# se estiver rodando em watch, é só salvar e comando é atualizado.

# executar com watch -d -n 0.5 ./video-08-desafio.c
ps -x --forest | grep a.out | grep -v 'grep'
