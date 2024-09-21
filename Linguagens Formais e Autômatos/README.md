# Linguagens Formais e Autômatos

Observação 1: Arquivos .jff são arquivos do software JFLAP, usado para experimentar tópicos de Linguagens Formais e de Teoria de Autômatos.
Observação 2: Coloquei apenas os projetos que continham como resposta arquivos .jff. Projetos que não precisavam disso, não estão aqui.

- Projeto01: Realizar as implementações dos DFA's que reconhecem as linguagens definidas:
  - ExA: L1 = {w | w é da forma x01y e x e y são quaisquer strings de 0’s e 1’s}
  - ExB: L2 = {w | w possui um número par de 0's}
  - ExC: L3 = {w | w possui ao mesmo tempo um número par de 0’s e um número ímpar de 1's}
  - ExD: L4 = {w | w termina em 00}
  - ExE: L5 = {w | w contém três 0's consecutivos}
  - ExF: L6 = {w | w contém a substring 011}
  - ExG: L7 = {w | w possui número de 0’s divisível por 5 e número de 1’s divisível por 3}
- Projeto02: Realizar as implementações dos DFA's que reconhecem as linguagens definidas e descreva um exemplo de cálculo da função de transição estendida para cada linguagem projetada:
  - ExA: L1 = {w | w = 0^n 1^m e n e m são pares}
  - ExB: L2 = {w | w possui o mesmo número de 01 e 10}
  - ExC: L3 = {w | w contém exatamente quatro 0's}
  - ExD: L4 = {w | w termina em 1101}
  - ExE: L5 = {w | w contém exatamente quatro 0's e ao menos dois 1's}
  - ExF: L6 = {w | w possui valor binário divisível por 5}
  - ExG: L7 = {w | w contém a substring 0101}
  - ExH: L8 = {w | w começa com 0 e tem comprimento ímpar ou começa com 1 e tem comprimento par}
  - ExI: L9 = {w | w não contém a substring 110}
  - ExJ: L10 = {w | |w| 5}^1
  - ExK: L11 = {w | w possui 1 em todas posições ímpares}
- Projeto02-Extra: Implementação de um programa que calcule a Função de Transição Estendida. A entrada do programa é um DFA e uma string w. A saída deverá ser se a string pertence ou não pertence à linguagem definida pelo DFA.
- Projeto03: Desenvolva os NFAs para a linguagens regulares considerando o alfabeto binário.
  - ExA: L1 = {w | w contém exatamente 4 0’s ou um número par de 1’s} (8 estados)
  - ExB: L2 = {w | w possui o terceiro símbolo a partir da direita igual a 0} (4 estados)
  - ExC: L3 = {w | w possui dois 0’s separados por um string de comprimento 4i para algum i ≥ 0} (6 estados)
  - ExD: L4 = {w | w contém a substring 0101} (5 estados)
  - ExE: L5 = {w | w contém um número par de 0’s ou exatamente dois 1’s} (6 estados)
  - ExF: L6 = {w | w = 0*1*0*0} (3 estados)
- Projeto04: Realizar as implementações e conversões dos NFA's que reconhecem as linguagens definidas:
  - ExA: Prove que L1 é regular considerando alfabeto binário: L1 = {w | w possui o mesmo número de 01 e 10}
  - ExB, ExC e ExD: Converta os NFA's providenciados (representação em tabela) em DFA's
  - ExE e ExF: Para cada e-NFA providenciado (representação em tabela), calcule seu e-fechamento e converta-os para DFA.
- Projeto05: Realizar as implementações de e-NFA's que reconhecem as linguagens definidas:
  - Ex1: Prove que L1 é regular considerando o alfabeto binário: L1 = {w | w contém a cada bloco de cinco símbolos consecutivos pelo ao menos dois 0’s}
  - Ex2: Considere o autômato M = ({q0, q1}, {0,1}, , q0, {q0, q1}), com sua a função de transição especificada em tabela. Qual a linguagem reconhecida pelo autômato? Construa o autômato complementar.
  - Ex3: Projetar um e-NFA para as seguintes linguagens (considere alfabeto = {a, b, c})
    - Ex3a: L1 = {w | w contém no mínimo três ocorrências de abc}
    - Ex3b: L2 = {w | w contém no mínimo três ocorrências de a ou no mínimo três ocorrências de b ou no mínimo três ocorrências de c}
    - Ex3c: L3 = {w | w começa com abc e termina com bca}
    - Ex3d: L4 = {w | |w| > 1 e os a's (se houver) precedem os b’s e b's (se houver) precedem os c’s}
- Projeto06: Criar as expressões regulares que reconhecem as linguagens definidas:
  1. Criar expressões regulares (RE) para as linguagens formada por 0’s e 1’s.
    - A: {w | w contém um único 1}
    - B: {w | w contém pelo menos um 1}
    - C: {w | w contém a string 001 como substring}
    - D: {w | |w| é par}
    - E: {w | |w| é múltiplo de 3}
    - F: {w | 6° símbolo da direita para a esquerda é igual a 1}
  2. Dado alfabeto {a, b, c} apresente a RE que represente todas as strings com ao menos 1 a e ao menos 1b.
  3. Dado alfabeto binário, apresente a RE que represente todas as strings onde todo par de zeros adjacentes aparecem antes de qualquer par de 1’s adjacentes.
  4. Dado alfabeto binário, apresente a RE que represente o conjunto de strings que não contém 101.
  5. Dado alfabeto binário, apresente a RE que represente as strings com no máximo um par de 0’s consecutivos ou um par de 1’s consecutivos.
- Projeto06 - Extra:
  1. Forneça expressões regulares que denotem as seguintes linguagens:
    - A: {w ∈ {a,b}* | |w| >= 3}
    - B: {w ∈ {a,b}* | w começa com a e tem tamanho par}
    - C: {w ∈ {a,b}* | w tem um número par de a's}
    - D: {w ∈ {a,b}* | w contém bb}
  2. Obtenha expressões regulares que denotem as linguagens sobre {0, 1} abaixo, a partir de DFAs que reconheçam as mesmas.
    - A: O conjunto das strings em que 0s só podem ocorrer nas posições pares.
    - B: O conjunto das strings com pelo menos um símbolo em que os 0's, se houver algum 0, precedem os 1's, se houver algum 1.
    - C: O conjunto das strings que não contém a substring 000.
  3. Construa um autômato equivalente a cada uma das seguintes expressões regulares:
    - A: 0*1*
    - B: 00*11*
    - C: (00)*(11)*
    - D: ((00)*(11)*)*
- Projeto07: Criar as expressões regulares e os autômatos equivalentes que reconhecem as linguagens definidas
  1. Projetar um autômato equivalente às expressões regulares abaixo:
    - A: ((00)*.(11)*)*
    - B: 1*0(0)*
    - C: (0+1)(0+1)*00
    - D: (00+11+(01+10)(00+11)*(01+10))*
  2. Determine a RE da linguagem aceita pelo autômato apresentado.
- Projeto08: Realizar as reduções de DFA's em autômatos mínimos definidas
  1. Encontrar o DFA mínimo equivalente ao DFA passado.
  2. Crie o DFA de estado mínimo que aceite todas e apenas as sequências de 0 e 1 que terminam em 010.
  3. Encontrar o DFA mínimo equivalente ao DFA passado.
  4. Crie um DFA mínimo que aceite todas e apenas as strings de 0 e 1 que tenham 110 como substring.
- Projeto09 - Extra (ex12): Descreva um PDA determinístico que reconheça as seguintes linguagens:
  - ex12a: L1 = {a^n b^2n | n ≥ 1}.
  - ex12c: L3 = {a^n b^m a^m b^n | n, m ≥ 1}
  - ex12d: L4 = L3*
- Projeto10:
  1. Construir um PDA para as linguagens abaixo e apresentar um exemplo de ID para cada uma delas:
    - A: Strings com um número igual de 0’s e 1’s.
    - B: {0^n 1 2^n |n >= 0}
    - C: Palíndromos de comprimento ímpar, onde alfabeto = {0, 1}
    - D: {a^n b^n c^m d^m | m, n >= 0}
    - E: {a^i b^j c^k | k = 2(i + j)}
    - F: {0^m 1^n 0^m | m, n >= 0}
    - G: {a^i b^j c^k | i = j ou j = k}
    - H: {0^n 1^k | n k 2n}
  2. Construir um PDA determinístico que aceite a linguagem:
    - A: Strings binários com duas vezes mais 1’s que 0’s.
    - B: Strings binários que começam e terminam com o mesmo símbolo e tem o mesmo número de 0’s e 1’s.
- Projeto11: Projetar as Máquinas de Turing para as linguagens/problemas definidos:
  1. Projetar Máquinas de Turing para as seguintes linguagens:
    - A: Conjunto de strings com um número igual de 0’s e 1’s.
    - B: {a^n b^n c^n | n >= 1}.
    - C: {ww^r | w é qualquer string de 0’s e 1’s}
  2. Construir uma TM com alfabeto {a, b} para aceitar as seguintes linguagens:
    - A: {a^i b^j | i>=0 e j>=i }
    - B: {a^i b^j a^i b^j | i, j > 0}
    - C: {uu | u ∈ {a, b}* }
  3. Construir uma TM com alfabeto {0,1} para realizar as seguintes operações:
    - A: Mover a entrada um espaço para a direita.
    - B: Concatenar o reverso da entrada com a entrada.
    - C: Remover os 1’s da entrada.