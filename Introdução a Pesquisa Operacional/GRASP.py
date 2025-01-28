import random
import math
import numpy as np
import random
from dataclasses import dataclass

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
            strpart = part[1].strip
            print("Instância localizada: " + strpart)
        elif line.startswith("KNAPSACK DATA TYPE"):
            part = line.split("KNAPSACK DATA TYPE:")
            strpart = part[1].strip
            print("Tipo de mochila: " + strpart)
        elif line.startswith("DIMENSION:"):
            part = line.split("DIMENSION:")
            strpart = part[1].strip
            dimension = int(strpart)
        elif line.startswith("NUMBER OF ITEMS:"):
            part = line.split("NUMBER OF ITEMS:")
            strpart = part[1].strip
            numItems = int(strpart)
        elif line.startswith("CAPACITY OF KNAPSACK:"):
            part = line.split("CAPACITY OF KNAPSACK:")
            strpart = part[1].strip
            kp_capacity = int(strpart)
        elif line.startswith("MIN SPEED:"):
            part = line.split("MIN SPEED:")
            strpart = part[1].strip
            min_speed = float(strpart)
        elif line.startswith("MAX SPEED:"):
            part = line.split("MAX SPEED:")
            strpart = part[1].strip
            max_speed = float(strpart)
        elif line.startswith("RENTING RATIO"):
            part = line.split("RENTING RATIO:")
            strpart = part[1].strip
            rent_ratio = float(strpart)
        elif line.startswith("NODE_COORD_SECTION"):
            tsp_section = True
            kp_section = False
            continue
        elif line.startswith("ITEMS SECTION"):
            tsp_section = False
            kp_section = True
            ttp_data.append(City(0, -1, -1, []))
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
            benef: float = (p/w) + (assInd-1)
            med_benef += benef
            ttp_data[assInd].items.append(Item(ind, p, w, benef, assInd))
    med_benef /= numItems
    return ttp_data, kp_capacity, min_speed, max_speed, rent_ratio, med_benef

def calculate_distances(ttp_data):
    num_cities = len(ttp_data)
    distances = [[0] * num_cities for _ in range(num_cities)]

    cities = []
    for city in ttp_data:
        if city.ind == 0: continue
        index = city.ind
        x = city.posX
        y = city.posY
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
        current_solution = construct_solution(ttp_data, alpha, kp_capacity, distances, min_speed, max_speed, rent_ratio, med_benef)
        
        # Fase de Busca Local
        current_solution = local_search(current_solution, kp_capacity)
        
        # Atualizar a melhor solução
        current_value = evaluate_solution(current_solution)
        if current_value > best_value:
            best_solution = current_solution
            best_value = current_value

    return best_solution

def construct_solution(ttp_data, alpha, kp_capacity, distances, min_speed, max_speed, rent_ratio, med_benef):
    num_cities = len(ttp_data)
    solutionKnapsack = []
    solutionRoute = []
    # Cidade que começamos
    cidadeAtual = 1
    # Lista para guardar os índices das cidades que já passamos. Vamos remover estes índices após ordenar as distâncias mais próximas
    # Já começamos com o 1 pois ele não deverá ser calculado aqui, sendo a primeira e última cidade
    # Ao fazer a equação para determinar o preço, eu devo manualmente adicionar o custo de saída e volta dela, tendo entre ambas um for com toda a equação restante
    unavailable = [1]
    # Zerar a solutionKnapsack e deixar ela preparada para alterar o que for
    for city in ttp_data:
        if city.ind == 0: continue
        solutionKnapsack.append([0] * len(city.items))
    # Looping para gerar a solução por cidade. Devemos percorrer ao contrário (última até a primeira) e ir decidindo os items
    # Ao rodar da última até a primeira, este algoritmo acaba sendo guloso para o KP, já que damos prioridade aos últimos itens
    for i in range(num_cities-1):
        # "TSP" primeiro, "KP" depois
        # Pegamos as alpha cidades mais próximas
        prox = np.argsort(distances[cidadeAtual-1]) - unavailable
        if len(prox) > alpha: prox = prox[:alpha]
        proxCidade = random.choice(prox)
        unavailable.append(proxCidade)
        solutionRoute.insert(0, proxCidade)

        # "KP"
        options = []
        for item in ttp_data[proxCidade].items:
            options.append(item.benefit)
        best = np.argsort(options)[0]
        if options[best] >= med_benef and kp_capacity - ttp_data[proxCidade].items[best].weight >= 0:
            solutionKnapsack[proxCidade][best] = 1
            kp_capacity -= ttp_data[proxCidade].items[best].weight
    
    # Inserir a primeira cidade no começo para facilitar o meu for no futuro que irá calcular o lucro final
    solutionRoute.insert(0, 1)

    # Ambos devem ser arrays. solutionRoute com a rota de solução e solutionKnapsack com a solução dos itens que devem estar na mochila.
    # solutionRoute deverá ser um array na ordem em que as cidades são visitadas.
    # solutionKnapsack deverá ser um array binário, levando em conta o índice do item
    # Pegar tamanho dos problemas + 1 e fazer lista binária ((0, 0, 0), (0, 1, 0)...) indicando quais itens colocar na mochila.
    # Assim ele organiza por cidade o índice e a parte de dentro pode só fazer um for mesmo (ou checar o ind deles)
    return solutionRoute, solutionKnapsack

def local_search(solution, capacity):
    # Implementar a busca local para melhorar a solução
    # Exemplo: troca de itens, remoção e inserção de novos itens
    return solution

def evaluate_solution(solution):
    # Avaliar a solução considerando a rota do TSP e os itens na mochila
    return random.random()  # Substituir por uma função de avaliação real

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
    items: list[Item] = []

