set ITEMS; # Conjunto de itens
param profit{ITEMS}; # Lucro de cada item
param weight{ITEMS}; # Peso de cada item
param capacity; # Capacidade máxima

# Var decisão
var x{ITEMS} binary; # x[i] = 1 se o item i for incluído na mochila, 0 caso contrário

# FO: maximize lucro
maximize total_profit:
    sum{i in ITEMS} profit[i] * x[i];

subject to:
    # Não pode passar da cap máxima
    weight_constraint:
        sum{i in ITEMS} weight[i] * x[i] <= capacity;

# Como inserir dados
data kp_data.dat;
end;