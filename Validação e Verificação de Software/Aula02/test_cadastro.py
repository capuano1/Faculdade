from verificadorCadastro import verificadorCadastro
from Cadastro import Cadastro, Categoria
from errors import InvalidTermAcceptError, InvalidAgeError, InvalidCategoryError, InvalidDurationError
import pytest

def test_valid_child():
    participante = Cadastro(10, Categoria.infantil, 60, True)
    assert verificadorCadastro(participante) is True

def test_valid_teen():
    participante = Cadastro(15, Categoria.juvenil, 60, True)
    assert verificadorCadastro(participante) is True

def test_valid_adult():
    participante = Cadastro(30, Categoria.adulto, 60, True)
    assert verificadorCadastro(participante) is True

def test_invalid_age_young():
    participante = Cadastro(9, Categoria.infantil, 60, True)
    with pytest.raises(InvalidAgeError):
        verificadorCadastro(participante)

def test_invalid_age_old():
    participante = Cadastro(61, Categoria.adulto, 60, True)
    with pytest.raises(InvalidAgeError):
        verificadorCadastro(participante)

def test_invalid_age_category():
    participante = Cadastro(18, Categoria.infantil, 60, True)
    with pytest.raises(InvalidCategoryError):
        verificadorCadastro(participante)

def test_invalid_duration_short():
    participante = Cadastro(12, Categoria.infantil, 29, True)
    with pytest.raises(InvalidDurationError):
        verificadorCadastro(participante)

def test_invalid_duration_long():
    participante = Cadastro(12, Categoria.infantil, 240, True)
    with pytest.raises(InvalidDurationError):
        verificadorCadastro(participante)

def test_invalid_term_accepted():
    participante = Cadastro(12, Categoria.infantil, 60, False)
    with pytest.raises(InvalidTermAcceptError):
        verificadorCadastro(participante)