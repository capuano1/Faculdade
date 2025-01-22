# Definição dos conjuntos e parâmetros
set N;  # Conjunto de nós (cidades)
param c{N,N};  # Matriz de custos (distâncias) entre as cidades
param n;  # Número de cidades

data tsp_data.dat;

set PAIRS := {i in N, j in N: i != j};

# Variáveis de decisão
var x{N,N} binary; # x[i,j] = 1 se a aresta (i,j) for usada, 0 caso contrário
var u{N} >= 0, <= n-1; # Variáveis auxiliares para evitar subrotas

# FO: Minimize “custo” da rota
# x como binário para a rota que foi feita, c para o “custo” dela
minimize total_cost:
    sum{i in N, j in N} c[i,j] * x[i,j];

# Visita tudo
subject to visit_once{i in N}:
    sum{j in N} x[i,j] = 1;

# Visita apenas uma vez
subject to leave_once{j in N}:
    sum{i in N} x[i,j] = 1;

# MTZ
subject to MTZ{(i,j) in PAIRS: i != j and i != 1 and j != 1}:
    u[i]-u[j]+(n)*x[i,j] <= n-1;

# Como inserir dados
end;