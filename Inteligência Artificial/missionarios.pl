/*
Vou usar -1 para representar o lado esquerdo e +1 para representar o lado direito
Isso traz a facilidade de poder multiplicar o número de canibais e missionários pelo valor da
direção, para então combinar 1 vez só este valor com a função movimento, sem precisar fazer
duas funções diferentes dependendo do lado que vamos.
*/

exibe([]) :- nl.
exibe([X|Y]) :- write(X), exibe(Y).

movimentos([(1, 0),
            (1, 1),
            (2, 0),
            (2, 1)]).

% Preciso checar lado esquerdo e lado direito
% Notação (M, C, D) mostra os restantes do lado esquerdo
% Testar primeiro o lado esquerdo, depois o lado direito
/*
Não sei o motivo, mas o prolog me dá problema de number outofsync se eu tento usar 0 diretamente
em algum lugar, como fazer X == 0, X = 0, X is 0...
Então criei essa variável para que o erro suma.
*/

seguro((M, C, _)) :-
    MD is 3 - M, CD is 3 - C, Zero is 1 - 1,
    ((MD == Zero) ; (MD >= CD)),
    (M >= C ; M == Zero).
    
% Inverter Lado
lado(-1, 1).
lado(1, -1).

% Realizar o movimento, caso válido
% Aqui eu faço a lógica de multiplicar por -1 ou por 1 para simplificar a solução
% Essa função já testa para garantir que o estado sendo retornado (M2, C2, NovDir) é seguro

movimento((M1, C1, Dir), (M, C)) :-
    AdjustedM is M * Dir, AdjustedC is C * Dir,
    M2 is M1 + AdjustedM, C2 is C1 + AdjustedC,
    seguro((M2, C2, _)).

adjuststate((M1, C1, Dir), (M, C), (M2, C2, NovDir)) :-
    AdjustedM is M * Dir, AdjustedC is C * Dir,
    M2 is M1 + AdjustedM, C2 is C1 + AdjustedC,
    lado(Dir, NovDir).

% Busca da solução
solucao((0, 0, 1), []) :- !.
solucao(EstadoAtual, [Caminho | EstadoAtual]) :-
    movimentos(Movs), member((Md, Cd), Movs),
    movimento(EstadoAtual, (Md, Cd)),
    adjuststate(EstadoAtual, (Md, Cd), EstadoProximo),
    \+ member(EstadoProximo, Caminho),
    print(EstadoProximo),
    solucao(EstadoProximo, Caminho).

% Retorna a solução final
resolver(Solucao) :-
    solucao((3, 3, -1), Solucao).