'''CODE BY: COPILOT'''

import networkx as nx
import matplotlib.pyplot as plt

# Criação do grafo
G = nx.Graph()

# Adiciona os nós (cidades)
cidades = [
    "Jacareí", "São José dos Campos", "Caçapava", "Taubaté",
    "Tremembé", "Pindamonhangaba", "Campos do Jordão",
    "Santo Antônio do Pinhal", "São Bento do Sapucaí"
]
G.add_nodes_from(cidades)

# Definição das arestas conforme a rota real aproximada:
# 1. Jacareí <-> São José dos Campos (cidades vizinhas)
# 2. São José dos Campos <-> Caçapava (rota pelo Eixo Dutra)
# 3. Caçapava <-> Taubaté (rota onde Caçapava está no caminho)
# 4. Taubaté <-> Tremembé (ligações locais)
# 5. Taubaté <-> Pindamonhangaba (rota principal para a montanha)
# 6. Pindamonhangaba <-> Campos do Jordão (rota para a região serrana)
# 7. Campos do Jordão <-> Santo Antônio do Pinhal (cidades interligadas na serra)
# 8. Santo Antônio do Pinhal <-> São Bento do Sapucaí (rota de acesso à região)
arestas = [
    ("Jacareí", "São José dos Campos"),
    ("São José dos Campos", "Caçapava"),
    ("Caçapava", "Taubaté"),
    ("Taubaté", "Tremembé"),
    ("Taubaté", "Pindamonhangaba"),
    ("Taubaté", "Campos do Jordão"),
    ("Tremembé", "Campos do Jordão"),
    ("Pindamonhangaba", "Campos do Jordão"),
    ("Pindamonhangaba", "Tremembé"),
    ("Campos do Jordão", "Santo Antônio do Pinhal"),
    ("Campos do Jordão", "São Bento do Sapucaí")
]
G.add_edges_from(arestas)

# Definindo posições geográficas aproximadas (longitude, latitude)
# Nota: Os valores abaixo são ilustrações para que a visualização respeite a ordenação geográfica.
'''positions = {
    "Jacareí":             (-45.95, -23.30),
    "São José dos Campos": (-45.90, -23.22),
    "Caçapava":            (-45.90, -23.00),
    "Taubaté":             (-45.56, -23.00),
    "Tremembé":            (-45.55, -23.05),
    "Pindamonhangaba":     (-45.75, -22.90),
    "Campos do Jordão":    (-45.65, -22.95),
    "Santo Antônio do Pinhal": (-45.62, -22.98),
    "São Bento do Sapucaí":    (-45.60, -23.00)
}'''

# Plotando o grafo com layout geográfico
plt.figure(figsize=(10, 8))
nx.draw(
    G,
    with_labels=True,
    node_size=600,
    node_color="lightblue",
    edge_color="gray",
    font_size=10,
    font_weight="bold"
)
plt.title("Grafo Simplificado das Conexões no Vale do Paraíba")
plt.xlabel("Longitude (aproximada)")
plt.ylabel("Latitude (aproximada)")
plt.show()
