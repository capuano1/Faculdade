import re
from invalid_email_error import InvalidEmailError

def validaEmail(email):
    if re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return True
    else:
        raise InvalidEmailError(email)