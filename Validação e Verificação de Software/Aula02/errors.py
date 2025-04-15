class InvalidAgeError(Exception):
    def __init__(self, age: int):
        if age > 60:
            self.message = f"{age} is too old for this race"
        elif age < 10:
            self.message = f"{age} is too young for this race"
        super().__init__(self.message)

class InvalidCategoryError(Exception):
    def __init__(self):
        self.message = f"Invalid category"
        super().__init__(self.message)

class InvalidDurationError(Exception):
    def __init__(self, duration: int):
        if duration > 180:
            self.message = "Race is too long"
        elif duration < 30:
            self.message = "Race is too short"
        super().__init__(self.message)

class InvalidTermAcceptError(Exception):
    def __init__(self):
        self.message = "Must accept the terms of the race to participate!"
        super().__init__(self.message)