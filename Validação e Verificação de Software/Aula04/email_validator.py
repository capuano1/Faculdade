import re

def validate(email):
    if not email or not isinstance(email, str):
        return False

    """if len(email) > 320: # If Statement to False
        return False # False to None""" # Essa validação acaba caindo quando testamos na linha 18 local_part e domain

    if email.count('@') != 1: # != to >  => Não faz sentido checar se não há ou se tem diferente de 1. Melhor checar apenas se é diferente de 1
        return False

    local_part, domain = email.split('@')

    """if not local_part or not domain: # 4 Or to And
        return False""" # Ambas checagens acabam caindo no regex, então aqui não é necessário

    if len(local_part) > 64 or len(domain) > 255:
        return False

    # Local part rules
    if '..' in local_part or local_part.endswith('.') or ' ' in local_part:
        return False

    # Domain part rules
    domain_labels = domain.split('.')
    if any(len(label) > 63 for label in domain_labels):
        return False # False to None

    # Use a safe regex to confirm valid characters and structure
    local_pattern = r'^[A-Za-z0-9!#$%&\'*+/=?^_`{|}~.-]+$'
    domain_pattern = r'^[A-Za-z0-9.-]+\.[A-Za-z]{2,}$'

    if not re.match(local_pattern, local_part):
        return False

    if not re.match(domain_pattern, domain):
        return False

    return True