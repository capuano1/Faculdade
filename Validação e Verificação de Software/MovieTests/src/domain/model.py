from dataclasses import dataclass, field
from enum import Enum
from datetime import timedelta
from src.domain.errors import DuplicateRoomName, InvalidDurationError, InvalidTitleError, DuplicateMovieNameError

class SeatStatus(Enum):
    AVAILABLE = "available"
    RESERVED = "reserved"
    OCCUPIED = "occupied"

@dataclass
class Seat:
    row: str
    number: int
    status: SeatStatus = SeatStatus.AVAILABLE

    @property
    def is_available(self):
        return self.status == SeatStatus.AVAILABLE
    
    def reserve(self):
        if self.status == SeatStatus.AVAILABLE:
            self.status = SeatStatus.RESERVED
            return True
        return False
    
    def confirm(self):
        if self.status == SeatStatus.RESERVED:
            self.status = SeatStatus.OCCUPIED
            return True
        return False
    
    def release(self):
        self.status = SeatStatus.AVAILABLE

    
@dataclass
class Room:
    name: str
    rows: list[list[Seat]]

    def __init__(self, name, seats=None):
        self.name = name
        self.rows = []
        if seats is None:
            self.create_list_of_seats()
            return
        i = 65
        for row in seats:
            row_seats = []
            row_name = chr(i)
            for j in range(row):
                seat = Seat(row=row_name, number=j+1)
                row_seats.append(seat)
            self.rows.append(row_seats)
            i += 1

    def create_list_of_seats(self):
        for i in range(10):
            row = chr(i + 65)
            row_seats = []
            for j in range(10):
                seat = Seat(row=row, number=j+1)
                row_seats.append(seat)
            self.rows.append(row_seats)

    def capacity(self):
        seats = 0
        for row in self.rows:
            seats += len(row)
        return seats
    
    def available_seats(self):
        available_seats = 0
        for row in self.rows:
            for seat in row:
                if seat.is_available:
                    available_seats += 1
        return available_seats
    
@dataclass
class Movie:
    title: str
    duration: int
    description: str = ""

    def __post_init__(self):
        if self.duration <= 0:
            raise InvalidDurationError("Duration must be a positive integer.")
        if not self.title:
            raise InvalidTitleError("Title cannot be empty.")
        
    @property
    def formated_duration(self):
        hours = self.duration // 60
        minutes = self.duration % 60
        return f"{hours}h {minutes}m" if hours > 0 else f"{minutes}m"
    
    def get_duration_in_timedelta(self):
        return timedelta(minutes=self.duration)

@dataclass
class Theater:
    rooms: list[Room] = field(default_factory=list)
    movies: list[Movie] = field(default_factory=list)

    def add(self, room):
        if self.duplicate_room_name(room):
            raise DuplicateRoomName()
        self.rooms.append(room)

    def add_movie(self, movie):
        if self.duplicate_movie_title(movie):
            raise DuplicateMovieNameError()
        self.movies.append(movie)

    def remove(self, room):
        self.rooms.remove(room)

    def remove_movie(self, movie):
        self.movies.remove(movie)

    def duplicate_room_name(self, room):
        return [theater_room for theater_room in self.rooms if theater_room.name == room.name]
    
    def duplicate_movie_title(self, movie):
        return [theater_movie for theater_movie in self.movies if theater_movie.title == movie.title]