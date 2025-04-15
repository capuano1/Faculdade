'''CODE BY: COPILOT'''

import networkx as nx
import matplotlib.pyplot as plt

# Criação do grafo
G = nx.Graph()

# Define nós da rota principal (representados pelos km)
main_nodes = ["Km0", "Km10", "Km20", "Km30", "Km40", "Km50"]

# Define nós da rota alternativa (saída e retomada da rota)
alt_nodes = ["Km12_alt", "Km25_alt", "Km35_alt"]

# Adiciona todos os nós ao grafo
G.add_nodes_from(main_nodes)
G.add_nodes_from(alt_nodes)

# Define as arestas da rota principal (conexão contínua)
main_edges = [
    ("Km0", "Km10"),
    ("Km10", "Km20"),
    ("Km20", "Km30"),
    ("Km30", "Km40"),
    ("Km40", "Km50")
]
G.add_edges_from(main_edges)

# Define as arestas do ramo alternativo:
# Este ramo parte de "Km10", segue por nós adicionais e reconecta em "Km40"
alt_edges = [
    ("Km10", "Km12_alt"),
    ("Km12_alt", "Km25_alt"),
    ("Km25_alt", "Km35_alt"),
    ("Km35_alt", "Km40")
]
G.add_edges_from(alt_edges)

# Opcional: Adiciona atributos de distância (em km) como peso para cada aresta
edge_weights = {
    ("Km0", "Km10"): 10,
    ("Km10", "Km20"): 10,
    ("Km20", "Km30"): 10,
    ("Km30", "Km40"): 10,
    ("Km40", "Km50"): 10,
    ("Km10", "Km12_alt"): 2,    # Saída: pequeno desvio a partir do Km10
    ("Km12_alt", "Km25_alt"): 13, # Percurso alternativo
    ("Km25_alt", "Km35_alt"): 10,
    ("Km35_alt", "Km40"): 5     # Reentrada próxima ao Km40
}
nx.set_edge_attributes(G, edge_weights, "weight")

# Define posições para simular uma localização genérica:
# - A rota principal é colocada ao longo do eixo x (y = 0)
# - A rota alternativa é deslocada para cima (por exemplo, y = 5)
positions = {
    "Km0": (0, 0),
    "Km10": (10, 0),
    "Km20": (20, 0),
    "Km30": (30, 0),
    "Km40": (40, 0),
    "Km50": (50, 0),
    "Km12_alt": (12, 5),
    "Km25_alt": (25, 5),
    "Km35_alt": (35, 5)
}

# Plotando o grafo
plt.figure(figsize=(12, 8))
nx.draw(
    G,
    pos=positions,
    with_labels=True,
    node_color="lightblue",
    node_size=800,
    edge_color="gray",
    font_size=10,
    font_weight="bold"
)

# Exibe os pesos (distâncias) nas arestas com rótulos em vermelho
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos=positions, edge_labels=edge_labels, font_color='red')

plt.title("Grafo Ilustrativo: Vértices Representando Quilômetros e Arestas como Conexões Físicas")
plt.xlabel("Localização (km)")
plt.ylabel("Offset (rota alternativa)")
plt.axis('equal')
plt.show()
