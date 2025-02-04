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
        elif line.startswith("KNAPSACK DATA TYPE"):
            part = line.split("KNAPSACK DATA TYPE:")
            strippart = part[1].strip()
            print("Tipo de mochila: " + str(strippart))
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
    return ttp_data, kp_capacity, min_speed, max_speed, rent_ratio, med_benef

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
    best_solution = None
    best_value = float('-inf')

    for _ in range(num_iterations):
        
        # Fase de Construção
        solutionRoute, solutionKnapsack = construct_solution(ttp_data, alpha, kp_capacity, distances)
        totalDist, totalLucro = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio)
        with open("results.txt", 'w') as file:
            file.write(str(solutionRoute) + '\n')
            file.write('\n' + str(solutionKnapsack) + '\n')
            file.write('\n' + str(totalDist) + '\n')
            file.write('\n' + str(totalLucro) + '\n')

        #print(solutionRoute)
        #print(solutionKnapsack)

        # Fase de Busca Local
        current_solution = local_search(current_solution, kp_capacity)
        
        # Atualizar a melhor solução
        current_value = evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed)
        if current_value > best_value:
            best_solution = current_solution
            best_value = current_value

    return solutionRoute

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
    print(totalDist)
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
    print(kp_capacity)

    # Ambos devem ser arrays. solutionRoute com a rota de solução e solutionKnapsack com a solução dos itens que devem estar na mochila.
    # solutionRoute deverá ser um array na ordem em que as cidades são visitadas.
    # solutionKnapsack deverá ser um array binário, levando em conta o índice do item
    # Pegar tamanho dos problemas + 1 e fazer lista binária ((0, 0, 0), (0, 1, 0)...) indicando quais itens colocar na mochila.
    # Assim ele organiza por cidade o índice e a parte de dentro pode só fazer um for mesmo (ou checar o ind deles)
    return solutionRoute, solutionKnapsack

def local_search(solutionRoute, solutionKnapsack, kp_capacity, ttp_data):
    # Implementar a busca local para melhorar a solução
    # Exemplo: troca de itens, remoção e inserção de novos itens
    return solutionRoute, solutionKnapsack

def evaluate_solution(solutionRoute, solutionKnapsack, distances, ttp_data, kp_capacity, min_speed, max_speed, rent_ratio):
    totalDist = 0
    totalPeso = 0
    totalLucro = 0
    velAtual: float = max_speed
    for i in range(1, len(solutionRoute)):
        totalDist += distances[solutionRoute[i-1]][solutionRoute[i]] / velAtual
        j = 0
        for item in ttp_data[solutionRoute[i]].items:
            totalPeso += solutionKnapsack[i][j] * item.weight
            totalLucro += solutionKnapsack[i][j] * item.profit
            j += 1
        velAtual = max_speed * (1 - (float(totalPeso/kp_capacity)))
        if velAtual < min_speed: velAtual = min_speed
    totalLucro -= rent_ratio*totalDist
    return totalDist, totalLucro

def main():
    ttp_input_file = ".\Inst\instancia.ttp"

    ttp_data, kp_capacity, min_speed, max_speed, rent_ratio, med_benef = read_ttp_instance(ttp_input_file)
    distances = calculate_distances(ttp_data)

    num_iterations = 100
    alpha = 3

    best_solution = grasp_ttp(ttp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio, med_benef)
    print("Melhor solução encontrada:", best_solution)

if __name__ == "__main__":
    main()