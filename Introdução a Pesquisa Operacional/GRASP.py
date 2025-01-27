import random
import math

def read_ttp_instance(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    tsp_data = []
    kp_data = []
    tsp_section = False
    kp_section = False
    kp_capacity: int = 0
    min_speed: float = 0
    max_speed: float = 0
    rent_ratio: float = 0

    for line in lines:
        if line.startswith("PROBLEM NAME"):
            part = line.split("PROBLEM NAME:")
            strpart = part[1].strip
            print("Instância localizada: " + strpart)
        elif line.startswith("KNAPSACK DATA TYPE"):
            part = line.split("KNAPSACK DATA TYPE:")
            strpart = part[1].strip
            print("Tipo de mochila: " + strpart)
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
            continue

        if tsp_section:
            tsp_data.append(line.strip())
        elif kp_section:
            kp_data.append(line.strip())

    return tsp_data, kp_data, kp_capacity, min_speed, max_speed, rent_ratio

def calculate_distances(tsp_data):
    num_cities = len(tsp_data)
    distances = [[0] * num_cities for _ in range(num_cities)]

    cities = []
    for line in tsp_data:
        index, x, y = map(int, line.split())
        cities.append((index, x, y))

    for i in range(num_cities):
        for j in range(num_cities):
            if i != j:
                dist = math.ceil(math.sqrt((cities[j][1] - cities[i][1]) ** 2 + (cities[j][2] - cities[i][2]) ** 2))
                distances[i][j] = dist
                distances[j][i] = dist
            else:
                distances[i][j] = 10000000.0

    return distances

def grasp_ttp(tsp_data, kp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio):
    best_solution = None
    best_value = float('-inf')

    for _ in range(num_iterations):
        # Fase de Construção
        current_solution = construct_solution(tsp_data, kp_data, alpha, kp_capacity)
        
        # Fase de Busca Local
        current_solution = local_search(current_solution, kp_capacity)
        
        # Atualizar a melhor solução
        current_value = evaluate_solution(current_solution)
        if current_value > best_value:
            best_solution = current_solution
            best_value = current_value

    return best_solution

def construct_solution(tsp_data, kp_data, alpha, kp_capacity, min_speed, max_speed, rent_ratio):
    # Inicializar a solução com a rota do TSP
    num_cities = len(tsp_data)
    solution = {'route': list(range(1, num_cities + 1)), 'items': []}
    remaining_capacity = kp_capacity

    # Adicionar itens à mochila de forma aleatória
    random.shuffle(kp_data)
    for line in kp_data:
        index, profit, weight, node = map(int, line.split())
        if weight <= remaining_capacity:
            solution['items'].append({'index': index, 'profit': profit, 'weight': weight, 'node': node})
            remaining_capacity -= weight

    return solution

def local_search(solution, capacity):
    # Implementar a busca local para melhorar a solução
    # Exemplo: troca de itens, remoção e inserção de novos itens
    return solution

def evaluate_solution(solution):
    # Avaliar a solução considerando a rota do TSP e os itens na mochila
    return random.random()  # Substituir por uma função de avaliação real

def main():
    ttp_input_file = ".\Inst\instancia.ttp"

    tsp_data, kp_data, kp_capacity, min_speed, max_speed, rent_ratio = read_ttp_instance(ttp_input_file)
    distances = calculate_distances(tsp_data)

    num_iterations = 100
    alpha = 3

    best_solution = grasp_ttp(tsp_data, kp_data, distances, num_iterations, alpha, kp_capacity, min_speed, max_speed, rent_ratio)
    print("Melhor solução encontrada:", best_solution)

if __name__ == "__main__":
    main()
