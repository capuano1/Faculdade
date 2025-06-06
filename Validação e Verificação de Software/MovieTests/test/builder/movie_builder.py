from src.domain.model import Movie

class MovieBuilder:
    movie: Movie

    def __init__(self):
        self.movie = Movie("Die Hard 2", 124, "Die Hard Description")

    def aMovie(self):
        self.movie = Movie("Die Hard 2", 124, "Die Hard Description")
        return self

    def build(self):
        return self.movie
    
    def with_title(self, title: str):
        self.movie.title = title
        return self
    
    def with_description(self, description: str):
        self.movie.description = description
        return self

    def with_duration(self, duration: int):
        self.movie.duration = duration
        return self