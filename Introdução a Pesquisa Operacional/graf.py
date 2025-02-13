import matplotlib.pyplot as plt
import numpy as np

# Dados fornecidos
instancias = [
    "eil51_n50_bounded-strongly-corr_01", "eil51_n50_uncorr_01", "eil51_n50_uncorr-similar-weights_01",
    "eil51_n150_bounded-strongly-corr_01", "eil51_n150_uncorr_01", "eil51_n150_uncorr-similar-weights_01",
    "eil51_n250_bounded-strongly-corr_01", "eil51_n250_uncorr_01", "eil51_n250_uncorr-similar-weights_01",
    "pr152_n151_bounded-strongly-corr_01", "pr152_n151_uncorr_01", "pr152_n151_uncorr-similar-weights_01",
    "pr152_n453_bounded-strongly-corr_01", "pr152_n453_uncorr_01", "pr152_n453_uncorr-similar-weights_01",
    "a280_n279_bounded-strongly-corr_01", "a280_n279_uncorr_01", "a280_n279_uncorr-similar-weights_01"
]
our_bks = [
    4273.36, 1703.85, 1097.23, 5501.45, -2134.34, 1458.29,
    8404.35, -5435.34, 438.85, 8527.4, -5256.32, 596.82,
    16898.08, -16087.98, -115.5, 4698.65, -14014.31, -2896.29
]
nikfarjam_bks = [
    4269.4, 2871.1, 1460, 7532, 7037, 4365,
    12804, 12478, 6359, 11117.4, 5615, 3791.9,
    25664.4, 20705.8, 13556.9, 19499, 20491, 9998
]

x = np.arange(len(instancias))  # o rótulo da localização no eixo x
largura = 0.35  # a largura das barras

fig, ax = plt.subplots(figsize=(14, 8))
rects1 = ax.bar(x - largura/2, our_bks, largura, label='Our BKS')
rects2 = ax.bar(x + largura/2, nikfarjam_bks, largura, label='Nikfarjam et al., 2024 BKS')

# Adiciona alguns textos para os rótulos, título e customiza o gráfico
ax.set_xlabel('Instância')
ax.set_ylabel('BKS')
ax.set_title('Comparação dos Resultados de cada Instância do TTP')
ax.set_xticks(x)
ax.set_xticklabels(instancias, rotation=90)
ax.legend()

fig.tight_layout()

# Salva o gráfico como uma imagem
plt.savefig('comparacao_ttp.png', dpi=300)

# Mostra o gráfico
plt.show()