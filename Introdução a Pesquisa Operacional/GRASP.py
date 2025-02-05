import random
import math
import numpy as np
import random
from dataclasses import dataclass

@dataclass
class Item:
    index: int
    profit: float
    weight: float
    benefit: float
    assignedIndex: int

@dataclass
class City:
    ind: int
    posX: float
    posY: float
    items: list[Item]

def read_ttp_instance(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    probType = ""
    knapType = ""
    ttp_data: list[City] = []
    tsp_section = False
    kp_section = False
    dimension: int = 0
    numItems: int = 0
    kp_capacity: int = 0
    min_speed: float = 0
    max_speed: float = 0
    rent_ratio: float = 0
    med_benef: float = 0

    for line in lines:
        if line.startswith("PROBLEM NAME"):
            part = line.split("PROBLEM NAME:")
            strippart = part[1].strip()
            print("Instância localizada: " + str(strippart))
            probType = str(strippart)
        elif line.startswith("KNAPSACK DATA TYPE"):
            part = line.split("KNAPSACK DATA TYPE:")
            strippart = part[1].strip()
            print("Tipo de mochila: " + str(strippart))
            knapType = str(strippart)
        elif line.startswith("DIMENSION:"):
            part = line.split("DIMENSION:")
            strippart = part[1].strip()
            dimension = int(strippart)
        elif line.startswith("NUMBER OF ITEMS:"):
            part = line.split("NUMBER OF ITEMS:")
            strippart = part[1].strip()
            numItems = int(strippart)
        elif line.startswith("CAPACITY OF KNAPSACK:"):
            part = line.split("CAPACITY OF KNAPSACK:")
            strippart = part[1].strip()
            kp_capacity = int(strippart)
        elif line.startswith("MIN SPEED:"):
            part = line.split("MIN SPEED:")
            strippart = part[1].strip()
            min_speed = float(strippart)
        elif line.startswith("MAX SPEED:"):
            part = line.split("MAX SPEED:")
            strippart = part[1].strip()
            max_speed = float(strippart)
        elif line.startswith("RENTING RATIO"):
            part = line.split("RENTING RATIO:")
            strippart = part[1].strip()
            rent_ratio = float(strippart)
        elif line.startswith("NODE_COORD_SECTION"):
            tsp_section = True
            kp_section = False
            continue
        elif line.startswith("ITEMS SECTION"):
            tsp_section = False
            kp_section = True
            continue

        if tsp_section:
            lin = line.split()
            ind = int(lin[0])
            x = float(lin[1])
            y = float(lin[2])
            ttp_data.append(City(ind, x, y, []))
        elif kp_section:
            lin = line.split()
            ind = int(lin[0])
            p = float(lin[1])
            w = float(lin[2])
            assInd = int(lin[3])
            benef: float = (p/w)
            med_benef += benef
            ttp_data[assInd-1].items.append(Item(ind, p, w, benef, assInd))
    med_benef /= numItems
    return ttp_data, kp_capacity, min_speed, max_speed, rent_ratio, med_benef, probType, knapType, numItems, dimension

def gurobiReader(probType, knapType, numItems, dimension):
    items = 0
    tsp = str(probType.split('-')[0])
    ttp = tsp + "-n" + str(numItems)
    tspSection = False
    kpSection = False
    solutionRoute: list[int] = []
    type1 = []
    type2 = []
    type3 = []
    
    with open(".\\gurobi.txt", 'r') as file:
        lines = file.readlines()

    for line in lines:
        if line.split()[0] == tsp:
            tspSection = True
            continue
        elif line.split()[0] == ttp:
            kpSection = True
            continue

        if tspSection:
            solutionRoute = [int(x) for x in line.split()]
            tspSection = False
            continue
        if kpSection:
            if items == 0:
                type1 = [int(x) for x in line.split()]
                items += 1
                continue
            elif items == 1:
                type2 = [int(x) for x in line.split()]
                items += 1
                continue
            elif items == 2:
                type3 = [int(x) for x in line.split()]
                items += 1
                kpSection = False
                continue

    if knapType == "bounded strongly corr":
        kpDesejado = type1
    elif knapType == "uncorrelated":
        kpDesejado = type2
    elif knapType == "uncorrelated, similar weights":
        kpDesejado = type3

    # print(solutionRoute)
    # print(kpDesejado)
    # print(kpDesejado)
    return solutionRoute, kpDesejado

def calculate_distances(ttp_data):
    num_cities = len(ttp_data)
    distances = [[0] * num_cities for _ in range(num_cities)]

    cities = []
    for city in ttp_data:
        #if city.ind == 0: continue
        index: int = city.ind
        x: float = city.posX
        y: float = city.posY
        cities.append((index, x, y))

    for i in range(num_cities):
        for j in range(num_cities):
            if i != j:
                dist = math.ceil(math.sqrt((cities[j][1] - cities[i][1]) ** 2 + (cities[j][2] - cities[i][2]) ** 2))
                distances[i][j] = dist
                #distances[j][i] = dist => Duplicado
            else:
                distances[i][j] = 10000000.0

    return distances

def grasp_ttp(ttp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio, med_benef):
    best_solution_route = None
    best_solution_knapsack = None
    best_profit = float('-inf')
    best_dist = None

    for _ in range(num_iterations):
        
        # Fase de Construção
        for i in range(10):
            solutionRoute, solutionKnapsack = construct_solution(ttp_data, alpha, kp_capacity, distances)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

            if totalLucro > best_profit or best_profit == float('-inf'):
                best_solution_route = solutionRoute.copy()
                best_solution_knapsack = solutionKnapsack.copy()
                best_profit = totalLucro
                best_dist = totalDist
            with open("results.txt", 'w') as file:
                file.write(str(best_solution_route) + '\n')
                file.write('\n' + str(best_solution_knapsack) + '\n')
                file.write('\n' + str(best_dist) + '\n')
                file.write('\n' + str(best_profit) + '\n')

        #print(solutionRoute)
        #print(solutionKnapsack)

        # Fase de Busca Local
        best_solution_route, best_solution_knapsack, best_profit, best_dist = local_search(best_solution_route, best_solution_knapsack, best_profit, best_dist,
                                                                                            distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

    return best_solution_route, best_solution_knapsack, best_profit, best_dist

def construct_solution(ttp_data_original, alpha, kp_capacity_original, distances):
    ttp_data = ttp_data_original.copy()
    kp_capacity = kp_capacity_original
    num_cities = len(ttp_data)-1
    solutionKnapsack = []
    solutionRoute: list[int] = []
    # Cidade que começamos
    cidadeAtual = 0
    # Lista para guardar os índices das cidades que já passamos. Vamos remover estes índices após ordenar as distâncias mais próximas
    # Já começamos com o 1 pois ele não deverá ser calculado aqui, sendo a primeira e última cidade
    # Ao fazer a equação para determinar o preço, eu devo manualmente adicionar o custo de saída e volta dela, tendo entre ambas um for com toda a equação restante
    unavailable = [0]
    # Zerar a solutionKnapsack e deixar ela preparada para alterar o que for
    for city in ttp_data:
        #if city.ind == 1: continue
        solutionKnapsack.append([0] * len(city.items))
    # Looping para gerar a solução por cidade. Devemos percorrer ao contrário (última até a primeira) e ir decidindo os items
    # Ao rodar da última até a primeira, este algoritmo acaba sendo guloso para o KP, já que damos prioridade aos últimos itens
    cid = num_cities
    biggest: float = 0
    totalDist = 0
    for i in range(num_cities-1):
        # "TSP" primeiro, "KP" depois
        # Pegamos as alpha cidades mais próximas
        aux: list[int] = np.argsort(distances[cidadeAtual])
        prox = [cid for cid in aux if cid not in unavailable]
        if len(prox) > alpha: prox = prox[:alpha]
        proxCidade: int = random.choice(prox)
        totalDist += distances[cidadeAtual][proxCidade]
        unavailable.append(proxCidade)
        solutionRoute.insert(0, int(proxCidade))
        j = 0
        for item in ttp_data[proxCidade].items:
            item.benefit += cid
            if item.benefit - cid >= 10 and kp_capacity - item.weight >= 0:
                solutionKnapsack[proxCidade][j] = 1
                kp_capacity -= item.weight
            if (item.benefit > biggest): biggest = item.benefit
            j += 1
        cid -= 1
        cidadeAtual = proxCidade

    for i in reversed(solutionRoute):
        # "KP"
        if i == 0: break
        for item in ttp_data[i].items:
            j = 0
            chance = round((item.benefit / biggest) * 100)
            if kp_capacity - ttp_data[i].items[j].weight >= 0 and solutionKnapsack[i][j] == 0:
                if chance >= random.randint(0, 99):
                    solutionKnapsack[i-1][j] = 1
                    kp_capacity -= ttp_data[i].items[j].weight
            j += 1
        
    # Inserir a primeira cidade no começo para facilitar o meu for no futuro que irá calcular o lucro final
    solutionRoute.insert(0, 0)

    # Ambos devem ser arrays. solutionRoute com a rota de solução e solutionKnapsack com a solução dos itens que devem estar na mochila.
    # solutionRoute deverá ser um array na ordem em que as cidades são visitadas.
    # solutionKnapsack deverá ser um array binário, levando em conta o índice do item
    # Pegar tamanho dos problemas + 1 e fazer lista binária ((0, 0, 0), (0, 1, 0)...) indicando quais itens colocar na mochila.
    # Assim ele organiza por cidade o índice e a parte de dentro pode só fazer um for mesmo (ou checar o ind deles)
    return solutionRoute, solutionKnapsack

def local_search(solutionRoute, solutionKnapsack, profit, dist, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    # RVND => Temos 3 heurísticas diferentes: 2-OPT (TSP), Swap Cidades(TSP) e Trocar Bit (KP)
    # Se fosse orientado a objetos, eu poderia fazer um visitor aqui pra deixar a coisa mais fácil
    # Python também não tem switch case, afinal python é python
    totalDist = 0
    totalLucro = 0
    best_route = solutionRoute.copy()
    best_knapsack = solutionKnapsack.copy()
    best_profit = profit
    best_dist = dist
    originalArray = [1, 2, 3]
    iterationArray = originalArray.copy()
    while iterationArray:
        heuristics = random.choice(iterationArray)
        # Uma função para cada heurística é melhor, ao invés de deixar uma função gigantesca aqui
        # Também facilita a manutenção do código e adição de outras heurísticas, assim como substituição de uma por outra
        if heuristics == 1:
            solutionRoute = opt2heuristic(best_route)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        elif heuristics == 2:
            solutionRoute = swapCidades(best_route)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        elif heuristics == 3:
            solutionKnapsack = trocaBit(best_knapsack, len(solutionRoute))
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

        # Analiso o resultado: se for melhor, salvo e tento o looping novamente, se for pior, removo essa opção da lista de heurísticas e tento novamente
        if totalLucro > best_profit:
            best_route = solutionRoute
            best_knapsack = solutionKnapsack
            best_profit = totalLucro
            best_dist = totalDist
            iterationArray = originalArray.copy()
            continue
        else:
            iterationArray.remove(heuristics)
            continue

    return best_route, best_knapsack, best_profit, best_dist

def opt2heuristic(solutionRoute):
    newSolutionRoute = []
    size = len(solutionRoute) - 1
    small = random.randint(1, size)
    aux: int = None
    big: int = None
    while small == aux or aux == None:
        aux = random.randint(1, size)
    if small < aux:
        big = aux
    else:
        big = small
        small = aux
    newSolutionRoute = solutionRoute[:small] + solutionRoute[big:] + solutionRoute[small:big]
    return newSolutionRoute

def swapCidades(solutionRoute):
    size = len(solutionRoute) - 1
    cid1 = random.randint(1, size)
    cid2 = None
    while cid1 == cid2 or cid2 == None:
        cid2 = random.randint(1, size)
    aux = solutionRoute[cid1]
    solutionRoute[cid1] = solutionRoute[cid2]
    solutionRoute[cid2] = aux
    return solutionRoute

def trocaBit(solutionKnapsack, size):
    cid = random.randint(1, size-1)
    qte = len(solutionKnapsack[cid])
    indItem = random.randint(0, qte-1)
    if solutionKnapsack[cid][indItem] == 0: solutionKnapsack[cid][indItem] = 1
    else: solutionKnapsack[cid][indItem] = 0
    return solutionKnapsack

def evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    # Simplesmente a equação
    totalDist = 0
    totalPeso = 0
    totalLucro = 0
    velAtual: float = max_speed
    for i in range(1, len(solutionRoute)):
        totalDist += distances[solutionRoute[i-1]][solutionRoute[i]] / velAtual
        j = 0
        for item in ttp_data[solutionRoute[i]].items:
            totalPeso += solutionKnapsack[solutionRoute[i]][j] * item.weight
            totalLucro += solutionKnapsack[solutionRoute[i]][j] * item.profit
            if totalPeso > kp_capacity:
                totalDist = float('inf')
                totalLucro = float('-inf')
                return totalDist, totalLucro
            j += 1
        velAtual = max_speed * (1 - (float(totalPeso/kp_capacity)))
        if velAtual < min_speed: velAtual = min_speed
    totalDist += distances[solutionRoute[-1]][0] / velAtual
    totalLucro -= rent_ratio*totalDist
    return totalDist, totalLucro

def evaluate_solution_exata(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    # Simplesmente a equação
    numCid = len(solutionRoute)
    totalDist = 0
    totalPeso = 0
    totalLucro = 0
    velAtual: float = max_speed
    for i in range(1, len(solutionRoute)):
        totalDist += distances[solutionRoute[i-1]][solutionRoute[i]] / velAtual
        j = 0
        for item in ttp_data[solutionRoute[i]].items:
            totalPeso += solutionKnapsack[(solutionRoute[i] + j*(numCid-1)) - 1] * item.weight
            totalLucro += solutionKnapsack[(solutionRoute[i] + j*(numCid-1)) - 1] * item.profit
            if totalPeso > kp_capacity:
                totalDist = float('inf')
                totalLucro = float('-inf')
                return totalDist, totalLucro
            j += 1
        velAtual = max_speed * (1 - (float(totalPeso/kp_capacity)))
        if velAtual < min_speed: velAtual = min_speed
    totalDist += distances[solutionRoute[-1]][0] / velAtual
    totalLucro -= rent_ratio*totalDist
    return totalDist, totalLucro

def main():
    ttp_input_file = ".\\Inst\\instancia.ttp"

    ttp_data, kp_capacity, min_speed, max_speed, rent_ratio, med_benef, probType, knapType, numItems, dimension = read_ttp_instance(ttp_input_file)
    distances = calculate_distances(ttp_data)

    exatoRoute, exatoKnapsack = gurobiReader(probType, knapType, numItems, dimension)
    exatoDist, exatoLucro = evaluate_solution_exata(exatoRoute, exatoKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
    print("Solução exata a bater:")
    print("Lucro: " + str(exatoLucro))
    print("Tempo: " + str(exatoDist))

    num_iterations = 100
    alpha = 3

    solutionRoute, solutionKnapsack, profit, dist = grasp_ttp(ttp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio, med_benef)
    print("Melhor solução encontrada:")
    print("Rota: " + str(solutionRoute))
    print("Mochila: " + str(solutionKnapsack))
    print("Lucro: " + str(profit))
    print("Tempo: " + str(dist))

if __name__ == "__main__":
    main()