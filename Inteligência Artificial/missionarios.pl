/*
Vou usar -1 para representar o lado esquerdo e +1 para representar o lado direito
Isso traz a facilidade de poder multiplicar o número de canibais e missionários pelo valor da
direção, para então combinar 1 vez só este valor com a função movimento, sem precisar fazer
duas funções diferentes dependendo do lado que vamos.
*/

movimentos([(1, 0),
            (1, 1),
            (2, 0),
            (2, 1)]).

% Preciso checar lado esquerdo e lado direito
% Notação (M, C, D) mostra os restantes do lado esquerdo
% Testar primeiro o lado esquerdo, depois o lado direito
seguro((M, C, _)) :-
    (M >= C ; M = 0),
    ((3 - M) >= (3 - C) ; 3 - M = 0).

% Inverter Lado
lado(-1, 1).
lado(1, -1).

% Realizar o movimento, caso válido
% Aqui eu faço a lógica de multiplicar por -1 ou por 1 para simplificar a solução
movimento((M1, C1, Dir), (M2, C2, NovDir), (M, C)) :-
    movimentos(Mov), member((M, C), Mov),
    AdjustedM is M * Dir, AdjustedC is C * Dir,
    M2 is M1 + AdjustedM, C2 is C1 + AdjustedC,
    seguro((M2, C2, _)),
    lado(Dir, NovDir).

% Busca da solução
solucao((0, 0, 1), [(0, 0, 1)]).
solucao(EstadoAtual, [EstadoAtual | Caminho]) :-
    %movimentos(Movs), member((Md, Cd), Movs),
    movimento(EstadoAtual, EstadoProximo, _),
    \+ member(EstadoProximo, [EstadoAtual | Caminho]),
    solucao(EstadoProximo, Caminho).

% Retorna a solução final
resolver(Solucao) :-
    solucao((3, 3, -1), Solucao).
