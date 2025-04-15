from enum import Enum

class Categoria(Enum):
    infantil = 1
    juvenil = 2
    adulto = 3

class Cadastro():
    def __init__(self, idade: int, categoria: Categoria, tempoEstimado: int, assinaturaTermo: bool):
        self.idade = idade
        self.categoria = categoria
        self.tempoEstimado = tempoEstimado
        self.assinaturaTermo = assinaturaTermo