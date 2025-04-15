class InvalidEmailError(Exception):
    def __init__(self, email):
        self.email = email
        self.message = f"{email} is not a valid e-mail"
        super().__init__(self.message)

"""Eu decidi criar uma exceção prória, assim como em aula.
Decidi colocar uma mensagem personalizada, que acredito que seria comum de ver em produtos"""