from Cadastro import Cadastro, Categoria
from errors import InvalidAgeError, InvalidCategoryError, InvalidDurationError, InvalidTermAcceptError

def verificadorCadastro(participante: Cadastro):
    if participante.idade > 60 or participante.idade < 10:
        raise InvalidAgeError(participante.idade)
    
    age_category_switch = {
        Categoria.infantil : participante.idade >= 10 and participante.idade <= 14,
        Categoria.juvenil : participante.idade >= 15 and participante.idade <= 17,
        Categoria.adulto : participante.idade >= 18 and participante.idade <= 60
    }

    if participante.categoria not in Categoria or not age_category_switch[participante.categoria]:
        raise InvalidCategoryError()
    
    if participante.tempoEstimado < 30 or participante.tempoEstimado > 180:
        raise InvalidDurationError(participante.tempoEstimado)
    
    if not participante.assinaturaTermo:
        raise InvalidTermAcceptError()
    
    return True