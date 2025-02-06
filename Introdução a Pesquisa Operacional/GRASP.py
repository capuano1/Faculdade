import random
import math
import numpy as np
import random
import time
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
    best_time: float = 0
    execMinutes = 10
    maxTime = execMinutes * 60

    local_profit: float = 0

    start = time.time()
    current = time.time()
    while current - start < maxTime:
        iteration_route = None
        iteration_knapsack = None
        iteration_profit = float('-inf')
        iteration_dist = 0
        alpha = random.randint(3, 5)
        # Fase de Construção
        for i in range(10):
            solutionRoute, solutionKnapsack = construct_solution(ttp_data, alpha, kp_capacity, distances)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

            if totalLucro > iteration_profit or iteration_profit == float('-inf'):
                iteration_route = solutionRoute.copy()
                iteration_knapsack = solutionKnapsack.copy()
                iteration_profit = totalLucro
                iteration_dist = totalDist
            """ with open("results.txt", 'w') as file:
                file.write(str(best_solution_route) + '\n')
                file.write('\n' + str(best_solution_knapsack) + '\n')
                file.write('\n' + str(best_dist) + '\n')
                file.write('\n' + str(best_profit) + '\n') """

        #print(solutionRoute)
        #print(solutionKnapsack)

        # Fase de Busca Local
        iteration_route, iteration_knapsack, local_profit, iteration_dist = local_search(iteration_route, iteration_knapsack, iteration_profit, iteration_dist,
                                                                                            distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        
        print("Best: " + str(round(best_profit, 2)))
        print("Local: " + str(round(local_profit, 2)))

        if local_profit > best_profit or best_profit == float('-inf'):
                current = time.time()
                best_solution_route = iteration_route.copy()
                best_solution_knapsack = iteration_knapsack.copy()
                best_profit = local_profit
                best_dist = iteration_dist
                best_time = current - start

        current = time.time()

    return best_solution_route, best_solution_knapsack, best_profit, best_dist, best_time

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
            solutionRoute = COPTIno(best_route, best_profit, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        elif heuristics == 2:
            solutionRoute = swapCidades(best_route, best_profit, best_knapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        elif heuristics == 3:
            solutionKnapsack = trocaBit(best_knapsack, len(solutionRoute), best_profit, best_route, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

        # Analiso o resultado: se for melhor, salvo e tento o looping novamente, se for pior, removo essa opção da lista de heurísticas e tento novamente
        if totalLucro > best_profit:
            best_route = solutionRoute.copy()
            best_knapsack = solutionKnapsack.copy()
            best_profit = totalLucro
            best_dist = totalDist
            iterationArray = originalArray.copy()
            continue
        else:
            iterationArray.remove(heuristics)
            continue

    return best_route, best_knapsack, best_profit, best_dist

def COPTIno(solutionRoute, best_profit, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    size = len(solutionRoute)
    for i in range(1, size):
        for j in range(i+2, size):
            for k in range(j+2, size):
                firstSubarray = solutionRoute[i:j]
                secondSubarray = solutionRoute[j:k]
                thirdSubarray = solutionRoute[k:]
                firstReverse = firstSubarray.copy()
                secondReverse = secondSubarray.copy()
                thirdReverse = thirdSubarray.copy()
                # reverse não retorna valor, ele diretamente altera a lista
                firstReverse.reverse()
                secondReverse.reverse()
                thirdReverse.reverse()
                # permutações
                first = solutionRoute[:i] + firstSubarray + secondSubarray + thirdReverse
                dist, lucro = evaluate_solution(first, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(first, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                second = solutionRoute[:i] + firstSubarray + secondReverse + thirdSubarray
                dist, lucro = evaluate_solution(second, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(second, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                third = solutionRoute[:i] + firstSubarray + secondReverse + thirdReverse
                dist, lucro = evaluate_solution(third, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(third, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                fourth = solutionRoute[:i] + firstReverse + secondSubarray + thirdSubarray
                dist, lucro = evaluate_solution(fourth, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(fourth, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                fifth = solutionRoute[:i] + firstReverse + secondSubarray + thirdReverse
                dist, lucro = evaluate_solution(fifth, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(fifth, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                sixth = solutionRoute[:i] + firstReverse + secondReverse + thirdSubarray
                dist, lucro = evaluate_solution(sixth, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(sixth, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

                seventh = solutionRoute[:i] + firstReverse + secondReverse + thirdReverse
                dist, lucro = evaluate_solution(seventh, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
                if lucro > best_profit: return COPTIno(seventh, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)

            if (j >= size-2):
                return solutionRoute

def swapCidades(solutionRoute, best_profit, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    size = len(solutionRoute) - 1
    original = solutionRoute.copy()
    lucro: float
    for i in range(1, size):
        for j in range(i+1, size):
            aux = solutionRoute[i]
            solutionRoute[i] = solutionRoute[j]
            solutionRoute[j] = aux
            dist, lucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            if lucro > best_profit:
                return swapCidades(solutionRoute, lucro, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            else: solutionRoute = original.copy()
    return original

def trocaBit(solutionKnapsack, size, best_profit, solutionRoute, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    original = solutionKnapsack.copy()
    for i in range(1, size-1):
        for j in range(0, len(solutionKnapsack[i])):
            if solutionKnapsack[i][j] == 0: solutionKnapsack[i][j] = 1
            else: solutionKnapsack[i][j] = 0
            dist, lucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            if lucro > best_profit:
                return trocaBit(solutionKnapsack, size, lucro, solutionRoute, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
            else: solutionKnapsack = original.copy()
    return original

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
    print("Lucro: " + str(round(exatoLucro, 2)))
    print("Tempo: " + str(round(exatoDist, 2)))

    num_iterations = 1000
    alpha = 3

    solutionRoute, solutionKnapsack, profit, dist, best_time = grasp_ttp(ttp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio, med_benef)
    print("Melhor solução encontrada:")
    print("Rota: " + str(solutionRoute))
    print("Mochila: " + str(solutionKnapsack))
    print("Lucro: " + str(round(profit, 2)))
    print("Tempo: " + str(round(dist, 2)))
    print("Melhor solução encontrada em " + str(round(best_time, 2)) + " segundos")

if __name__ == "__main__":
    main()