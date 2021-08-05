# Fundamentos de Sistemas Operacionais - FGA0170
[Página de FSO](https://www.brunoribas.com.br/so/2021-1/)

[Progresso das aulas e exercícios](https://github.com/yudi-azvd/fso/issues/1)


## Livros e recursos
[Livro Prof. Maziero](http://wiki.inf.ufpr.br/maziero/doku.php?id=socm:start)

[Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/), Universidade de 
Winsconsin

[Notas de revisão](http://pages.cs.wisc.edu/~bart/537/lecturenotes/titlepage.html)

[Xv6, a simple Unix-like teaching operating system](https://pdos.csail.mit.edu/6.828/2012/xv6.html), [Livro](https://pdos.csail.mit.edu/6.S081/2020/xv6/book-riscv-rev1.pdf)

[Operating Systems and System Programming, Berkley](https://www.youtube.com/playlist?list=PLggtecHMfYHA7j2rF7nZFgnepu_uPuYws) - Vídeo aulas


## Aprendizados
[Aprendizados de processos e sinais](01-processes/_exercises/aula-04/moj-processos-sinais/README.md)


## Útil

    ./a.out & ps -x --forest \
      | grep './a.out' \
      | sed -E 's/.*[0-9]+\s+.\s+//g' \
      > tmp \
      ;code tmp 

Reproduz algo do tipo

    \_ ./a.out
    |   \_ ./a.out
    |   \_ ./a.out
    \_ grep --color=auto ./a.out


