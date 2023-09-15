# Minesweeper

## Execução

Dentro da pasta src:

```shell
make all
```

## Tema

Este trabalho prático tem como objetivo conciliar os conhecimentos adquiridos na cadeira de Programação 1 para desenvolver o jogo Minesweeper na linguagem de programação C.\
Este jogo é constituido por um tabuleiro no qual se encontram escondidas minas. O objetivo é o jogador ir selecionando coordenadas sem acertar nas minas e, através da função flag, assinalar os locais onde acha que se encontram as mesmas. Uma vez destapadas todas as casas que não são minas o jogo termina e o jogador vence, caso o jogador acerte numa mina, perde.\
Para auxilio do utilizador o jogo informa-o de quantas minas existem no tabuleiro e quantas bandeiras lhe falta colocar.
Pode-se assim verificar que o jogador apenas tem de se preocupar com 3 regras:
- Não destapar nenhuma mina;
- Assinalar com uma bandeira todas e apenas as coordenadas das minas;
- Destapar todos os espaços que não sejam minas.
Software utilizado:
Apple Xcode (compilador);