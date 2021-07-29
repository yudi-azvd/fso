# Fundamentos de Sistemas Operacionais - FGA0170

[Página de FSO](https://www.brunoribas.com.br/so/2021-1/)

[Livro Prof. Maziero](http://wiki.inf.ufpr.br/maziero/doku.php?id=socm:start)


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


