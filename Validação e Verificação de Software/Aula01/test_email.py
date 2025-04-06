import pytest
from my_email import validaEmail
from invalid_email_error import InvalidEmailError

def test_emailTrue():
    assert validaEmail("thiago.capuano@unifesp.br") is True

def test_emailException():
    with pytest.raises(InvalidEmailError):
        """Seguindo dicas do StackOverflow, o RegEx que testa e-mail aceita muitas coisas,
        então usar 2 @ é uma das poucas coisas que geraria uma exceção neste caso"""
        validaEmail("fulano@fulano@ciclano.com")