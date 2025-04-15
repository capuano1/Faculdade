import networkx as nx
import matplotlib.pyplot as plt

# Cria o grafo
G = nx.Graph()

# Define os vértices da rota principal e da alternativa
main_nodes = ["Km0", "Km10", "Km20", "Km30", "Km40", "Km50"]
alt_nodes = ["Km12_alt", "Km25_alt", "Km35_alt"]

G.add_nodes_from(main_nodes)
G.add_nodes_from(alt_nodes)

# Define as arestas com pesos (exemplo: índice de uso/tráfego)
# Rota principal: valores mais altos indicam maior fluxo
main_edges = [
    ("Km0", "Km10", {"weight": 20}),   # trecho com fluxo moderado
    ("Km10", "Km20", {"weight": 30}),   # trecho crítico com alto uso
    ("Km20", "Km30", {"weight": 25}),
    ("Km30", "Km40", {"weight": 15}),
    ("Km40", "Km50", {"weight": 10})
]

# Rota alternativa: pesos menores, pois é um desvio com fluxo reduzido
alt_edges = [
    ("Km10", "Km12_alt", {"weight": 5}),
    ("Km12_alt", "Km25_alt", {"weight": 10}),
    ("Km25_alt", "Km35_alt", {"weight": 8}),
    ("Km35_alt", "Km40", {"weight": 6})
]

G.add_edges_from(main_edges)
G.add_edges_from(alt_edges)

# Define posições para os nós, simulando uma localização genérica:
# - A rota principal segue horizontalmente (ao longo do eixo x)
# - A rota alternativa é deslocada verticalmente para melhor visualização
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

# Configura a figura e desenha o grafo
plt.figure(figsize=(12, 8))

# Calcula a largura das arestas proporcional ao seu peso (escala simples)
edge_weights = nx.get_edge_attributes(G, 'weight')
edge_widths = [edge_weights[edge] / 2 for edge in G.edges()]

nx.draw(
    G,
    pos=positions,
    with_labels=True,
    node_color="lightblue",
    node_size=600,
    edge_color="gray",
    width=edge_widths,
    font_size=10,
    font_weight="bold"
)

# Adiciona rótulos de peso nas arestas (em vermelho)
nx.draw_networkx_edge_labels(G, pos=positions, edge_labels=edge_weights, font_color='red')

plt.title("Exemplo Ilustrativo: Grafo com Vértices (km) e Arestas com Peso\n(indicador de uso/risco de acidentes e necessidade de manutenção)")
plt.xlabel("Quilômetros")
plt.ylabel("Deslocamento (rota alternativa)")
plt.axis('equal')
plt.show()
