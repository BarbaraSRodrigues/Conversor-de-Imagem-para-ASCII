# Conversor-de-Imagem-para-ASCII
Trabalho feito para a disciplina de Processamento de Imagens. Esse conversor pega uma imagem e coloca caracteres da tabela ASCII dados pelo usuário, de acordo com a tonalidade do pixel da imagem.

## Descrição:

<li>Nesse trabalho há uma ferramenta que a partir de uma **imagem em tons de cinza (PGM)**, produz a imagem usando **caracteres ASCII** como tons de cinza.</li>
<li>O usuário desse programa deverá informar a imagem, o número de colunas e linhas da imagem ASCII que será gerada (amostragem) e o string de caracteres para codificar os tons de cinza (quantização)</li>
<li>O programa deverá ser chamado em linha de comando da seguinte forma: **./ascii nome=arquivo=imagem ncolunas nlinhas string [.pgm]**</li><br>
Exemplo de uso:<br>
<p>./ascii cao.pgm 100 30 ”@$#*%o!=+;:˜=,. ”</p>
