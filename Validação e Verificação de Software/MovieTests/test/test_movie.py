from src.domain.model import Movie, Theater
from test.builder.movie_builder import MovieBuilder
from datetime import timedelta
from src.domain.errors import InvalidDurationError, InvalidTitleError, DuplicateMovieNameError
import pytest

def test_create_movie():
    movie = MovieBuilder().aMovie().with_duration(148).build()
    assert movie.title == "Die Hard 2"
    assert movie.duration == 148

def test_cannot_create_movie_with_invalid_duration():
    with pytest.raises(InvalidDurationError):
        Movie("Inception", -1)

def test_cannot_create_movie_without_title():
    with pytest.raises(InvalidTitleError):
        Movie("", 120)

def test_movie_cannot_have_duplicate_title():
    movie1 = Movie("Inception", 148)
    movie2 = Movie("Inception", 120)
    theater = Theater()
    theater.add_movie(movie1)
    with pytest.raises(DuplicateMovieNameError):
        theater.add_movie(movie2)

def test_movie_formatted_duration():
    movie = Movie("Inception", 148)
    assert movie.formated_duration == "2h 28m"
    
    short_movie = Movie("Short Film", 45)
    assert short_movie.formated_duration == "45m"
    
    one_hour_movie = Movie("One Hour Film", 60)
    assert one_hour_movie.formated_duration == "1h"

def test_movie_get_duration_in_timedelta():
    movie = Movie("Inception", 148)
    inception_duration = timedelta(minutes=148)
    assert movie.get_duration_in_timedelta() == inception_duration