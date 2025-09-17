def soma_sia(intervalx: tuple, intervaly: tuple) -> tuple:
    resultado: tuple = (intervalx[0] + intervaly[0], intervalx[1] + intervaly[1])
    return resultado

def subtrai_sia(intervalx: tuple, intervaly: tuple) -> tuple:
    resultado: tuple = (intervalx[0] - intervaly[1], intervalx[1] - intervaly[0])
    return resultado

def multiplica_sia(intervalx: tuple, intervaly: tuple) -> tuple:
    p1: float = intervalx[0] * intervaly[0]
    p2: float = intervalx[0] * intervaly[1]
    p3: float = intervalx[1] * intervaly[0]
    p4: float = intervalx[1] * intervaly[1]
    resultado: tuple = (min(p1, p2, p3, p4), max(p1, p2, p3, p4))
    return resultado

def divide_sia(intervalx: tuple, intervaly: tuple) -> tuple:
    if intervaly[0] <= 0 <= intervaly[1]:
        raise ValueError("Divisão por intervalo que inclui zero não é permitida.")
    q1: float = intervalx[0] / intervaly[0]
    q2: float = intervalx[0] / intervaly[1]
    q3: float = intervalx[1] / intervaly[0]
    q4: float = intervalx[1] / intervaly[1]
    resultado: tuple = (min(q1, q2, q3, q4), max(q1, q2, q3, q4))
    return resultado

def soma_cia(intervalx: tuple, intervaly: tuple) -> tuple:
    lowest_x: float = intervalx[0]
    lowest_y: float = intervaly[0]
    wx: float = intervalx[1] - intervalx[0]
    wy: float = intervaly[1] - intervaly[0]

    lowest_sum: float = lowest_x + lowest_y
    min_sum: float = min(lowest_sum, lowest_sum + wx, lowest_sum + wy, lowest_sum + wx + wy)
    max_sum: float = max(lowest_sum, lowest_sum + wx, lowest_sum + wy, lowest_sum + wx + wy)

    resultado: tuple = (min_sum, max_sum)
    return resultado

def subtrai_cia(intervalx: tuple, intervaly: tuple) -> tuple:
    lowest_x: float = intervalx[0]
    lowest_y: float = intervaly[0]
    wx: float = intervalx[1] - intervalx[0]
    wy: float = intervaly[1] - intervaly[0]

    lowest_diff: float = lowest_x - lowest_y
    min_diff: float = min(lowest_diff, lowest_diff + wx, lowest_diff - wy, lowest_diff + wx - wy)
    max_diff: float = max(lowest_diff, lowest_diff + wx, lowest_diff - wy, lowest_diff + wx - wy)

    resultado: tuple = (min_diff, max_diff)
    return resultado

def multiplica_cia(intervalx: tuple, intervaly: tuple) -> tuple: