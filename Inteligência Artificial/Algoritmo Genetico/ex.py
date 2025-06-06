# Thiago Corso Capuano  163996
# Melhor resultado encontrado usando 100 indivíduos e 2000 gerações (código executado 10 vezes):
# [-302.52493658 -420.97033592 420.96478584]
# Valor mínimo: -1138.510324904757

import numpy as np

num_individuals = 100
num_generations = 2000
mutation_rate = 0.1
num_variables = 3
interval = (-500, 500)

# Gera população
population = np.random.uniform(interval[0], interval[1], (num_individuals, num_variables))

# FO
def objective_function(X):
    return sum(-x * np.sin(np.sqrt(abs(x))) for x in X)

# n gerações
for generation in range(num_generations):
    fitness = np.array([objective_function(ind) for ind in population])
    # // => floor em python
    parents = population[np.argsort(fitness)[:num_individuals//2]]

    offspring = []
    # filhos
    for _ in range(num_individuals//2):
        parent1, parent2 = parents[np.random.choice(len(parents), 2, replace=False)]
        child = (parent1 + parent2) / 2
        offspring.append(child)
    
    offspring = np.array(offspring)
    
    # mutar
    mutations = np.random.uniform(-50, 50, offspring.shape) * (np.random.rand(*offspring.shape) < mutation_rate)
    offspring += mutations
    
    population = np.vstack((parents, offspring))

# solução e valor mínimo
best_solution = population[np.argmin([objective_function(ind) for ind in population])]
best_value = objective_function(best_solution)

print("Melhor solução encontrada:", best_solution)
print("Valor mínimo da função:", best_value)