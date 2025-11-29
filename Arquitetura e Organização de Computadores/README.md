# COMO USAR O TRABALHO FINAL
Neste documento, vou explicar como funciona o trabalho final e como usá-lo. Primeiramente, o código deve ser executado através do simulador MARS para funcionar.

Ao iniciar o programa, ele irá te pedir o horário atual, porém, sem separar horas e minutos com dois pontos ':'. Portanto, para entrar 15:00 no programa, devemos escrever 1500 e apertar enter.

Após inserir o horário atual, é possível interagir com diferentes funções do sistema através do menu simples baseado em texto do programa. É apenas necessário digitar o número da opção escolhida e apertar enter. Abaixo, estão listadas as funções do programa com seu número de opção.

Importante notar que o programa suporta um vetor de até 10 trens armazenados.

## 0 - Lista de comandos
Como o próprio nome já diz, este comando imprime a lista de comandos na tela

## 1 - Adicionar trem
Com este comando, podemos adicionar um trem. Para isso, devemos escrever um código de trem que siga o padrão de 1 letra maiúscula seguido por 3 números. Não se deve apertar enter após digitar. O segundo dado pedido é o código da cidade, em que qualquer código de 3 caracteres é aceito e, novamente, não se deve apertar enter após digitar. Por fim, devemos demarcar qual é o horário previsto para que o trem chegue na estação. Neste caso, devemos entrar o horário no mesmo formato do horário atual e, então, apertamos enter.

Importante notar que, caso o horário previsto seja menor do que o horário atual, então o trem é demarcado como "atrasado". Caso contrário, ele é demarcado como "a caminho".

Além disso, os trens são ordenados de maneira crescente de horário, de cima para baixo.

## 2 - Remover trem
Com este comando, podemos remover um trem da nossa lista. Para tal, precisamos apenas escrever qual é o código do trem em questão. Não se deve apertar enter. Com isso, o trem será removido e a lista será ordenada novamente sem a presença deste trem.

## 3 - Listar trens
Comando simples que lista todos os trens cadastrados

## 4 - Buscar trem
Com este comando, podemos buscar um trem específico na lista através de seu código. Para tal, precisamos apenas escrever qual é o código do trem em questão. Não se deve apertar enter. Caso o trem seja encontrado, seus dados serão printados na tela

## 5 - Marcar chegada do trem
Com este comando, é possível demarcar o estado do trem como "chegou". Para tal, precisamos apenas escrever qual é o código do trem em questão. Não se deve apertar enter.

## 9 - Encerrar programa
Com este comando, o programa é encerrado.