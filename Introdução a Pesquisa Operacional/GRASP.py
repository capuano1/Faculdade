import random
import math

def read_ttp_instance(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    tsp_data = []
    kp_data = []
    tsp_section = False
    kp_section = False

    for line in lines:
        if line.startswith("NODE_COORD_SECTION"):
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

    return tsp_data, kp_data

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

    return distances

def grasp_ttp(tsp_data, kp_data, num_iterations, alpha, capacity):
    best_solution = None
    best_value = float('-inf')

    for _ in range(num_iterations):
        # Fase de Construção
        current_solution = construct_solution(tsp_data, kp_data, alpha, capacity)
        
        # Fase de Busca Local
        current_solution = local_search(current_solution, capacity)
        
        # Atualizar a melhor solução
        current_value = evaluate_solution(current_solution)
        if current_value > best_value:
            best_solution = current_solution
            best_value = current_value

    return best_solution

def construct_solution(tsp_data, kp_data, alpha, capacity):
    # Inicializar a solução com a rota do TSP
    num_cities = len(tsp_data)
    solution = {'route': list(range(1, num_cities + 1)), 'items': []}
    remaining_capacity = capacity

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
    ttp_input_file = input("Digite o caminho do arquivo com a instância do TTP: ")

    tsp_data, kp_data = read_ttp_instance(ttp_input_file)
    distances = calculate_distances(tsp_data)

    num_iterations = 100
    alpha = 0.5
    capacity = 4029

    best_solution = grasp_ttp(tsp_data, kp_data, num_iterations, alpha, capacity)
    print("Melhor solução encontrada:", best_solution)

if __name__ == "__main__":
    main()
