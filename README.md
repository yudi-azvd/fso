# Fundamentos de Sistemas Operacionais - FGA0170
[Página de FSO](https://www.brunoribas.com.br/so/2021-1/)

[Progresso das aulas e exercícios](https://github.com/yudi-azvd/fso/issues/1)


## Livros e recursos
[Livro Prof. Maziero](http://wiki.inf.ufpr.br/maziero/doku.php?id=socm:start)

[Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/), 
Universidade de Winsconsin

[Notas de revisão](http://pages.cs.wisc.edu/~bart/537/lecturenotes/titlepage.html)

[Xv6, a simple Unix-like teaching operating system](https://pdos.csail.mit.edu/6.828/2020/xv6.html), 
[Livro](https://pdos.csail.mit.edu/6.S081/2020/xv6/book-riscv-rev1.pdf)

[Operating Systems and System Programming, Berkley](https://www.youtube.com/playlist?list=PLggtecHMfYHA7j2rF7nZFgnepu_uPuYws) - Vídeo aulas


## Aprendizados
[Aprendizados de processos e sinais](01-processes/_exercises/aula-04/moj-processos-sinais/README.md)


## Útil
Executar com `watch -d -n 0.5 ./print-process-tree.sh`:
```sh
# print-process-tree.sh
ps -x --forest | grep "a.out\|main.out" | grep -v 'grep' |
  sed -E "s/^(\s+?[0-9]+)(.*\s+\|)(.*)/\1 ->\3/"
```

Reproduz algo do tipo

    Every 0.1s: ./print-process-tree.sh            Atlas: Sun Aug 22 12:31:29 2021

    25969 ->   \_ ./a.out
    25970 ->       \_ [a.out] <defunct>
    25971 ->       \_ [a.out] <defunct>
