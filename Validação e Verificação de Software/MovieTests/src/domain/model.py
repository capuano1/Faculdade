from dataclasses import dataclass, field
from enum import Enum
import uuid, copy
from datetime import timedelta, datetime
from src.domain.errors import DuplicateRoomName, InvalidDurationError, InvalidTitleError, DuplicateMovieNameError, OverlappingSessionError

class SeatStatus(Enum):
    AVAILABLE = "available"
    RESERVED = "reserved"
    OCCUPIED = "occupied"

class BookingType(Enum):
    FULL_PRICE = "full_price"
    DISCOUNTED = "discounted"

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
        return f"{hours}h" if minutes == 0 else f"{hours}h {minutes}m" if hours > 0 else f"{minutes}m"
    
    def get_duration_in_timedelta(self):
        return timedelta(minutes=self.duration)

@dataclass
class Session:
    room: Room
    movie: Movie
    startTime: datetime
    id: uuid = field(init=False)

    def __init__(self, room: Room, movie: Movie, startTime: datetime):
        self.room = copy.deepcopy(room)
        self.movie = movie
        self.startTime = startTime
        self.id = uuid.uuid4()

    @property
    def get_end_time(self):
        return self.startTime + self.movie.get_duration_in_timedelta()
    
    @property
    def available_seats(self):
        return [seat for row in self.room.rows for seat in row if seat.is_available]
    
    def reserve_seat(self, row: str, number: int):
        for selRow in self.room.rows:
            for seat in selRow:
                if seat.row != row:
                    break
                elif seat.number == number and seat.is_available:
                    seat.reserve()
                    return True
            return False
    
    def confirm_seat(self, row: str, number: int):
        for selRow in self.room.rows:
            for seat in selRow:
                if seat.row != row:
                    break
                elif seat.number == number and seat.status == SeatStatus.RESERVED:
                    seat.confirm()
                    return True
            return False
    
    def release_seat(self, row: str, number: int):
        for selRow in self.room.rows:
            for seat in selRow:
                if seat.row != row:
                    break
                elif seat.number == number and not seat.is_available:
                    seat.release()
                    return True
            return False
    
    def get_seat_status(self, row: str, number: int):
        for selRow in self.room.rows:
            for seat in selRow:
                if seat.row != row:
                    break
                elif seat.number == number:
                    return seat.status
        return None
        
@dataclass
class Theater:
    rooms: list[Room] = field(default_factory=list)
    movies: list[Movie] = field(default_factory=list)
    sessions: list[Session] = field(default_factory=list)

    def add(self, room):
        if self.duplicate_room_name(room):
            raise DuplicateRoomName()
        self.rooms.append(room)

    def add_movie(self, movie):
        if self.duplicate_movie_title(movie):
            raise DuplicateMovieNameError()
        self.movies.append(movie)

    def add_session(self, session: Session):
        if self.overlapping_sessions(session):
            raise OverlappingSessionError("Session overlaps with an existing session.")
        self.sessions.append(session)

    def remove(self, room):
        self.rooms.remove(room)

    def remove_movie(self, movie):
        self.movies.remove(movie)

    def duplicate_room_name(self, room):
        return [theater_room for theater_room in self.rooms if theater_room.name == room.name]
    
    def duplicate_movie_title(self, movie):
        return [theater_movie for theater_movie in self.movies if theater_movie.title == movie.title]
    
    def overlapping_sessions(self, session: Session):
        for existing_session in self.sessions:
            if (existing_session.room.name == session.room.name and
                not (session.get_end_time <= existing_session.startTime or
                     session.startTime >= existing_session.get_end_time)):
                return True
        return False
    
    def get_session_by_id(self, session_id: uuid):
        for session in self.sessions:
            if session.id == session_id:
                return session
        return None
    
@dataclass
class Booking:
    session: Session
    seat: Seat
    ticketType: BookingType
    timeCreated: datetime = field(default_factory=datetime.now)
    id: uuid = field(init=False, default_factory=uuid.uuid4)

@dataclass
class User:
    username: str
    bookings: list[Booking] = field(default_factory=list)
    id: uuid = field(init=False, default_factory=uuid.uuid4)

@dataclass
class ShoppingCart:
    user: User
    bookings: list[Booking] = field(default_factory=list)

    def add_booking(self, booking: Booking):
        booking.session.reserve_seat(booking.seat.row, booking.seat.number)
        self.bookings.append(booking)

    def remove_booking(self, booking: Booking):
        booking.session.release_seat(booking.seat.row, booking.seat.number)
        self.bookings.remove(booking)

    def clear(self):
        for booking in self.bookings:
            booking.session.release_seat(booking.seat.row, booking.seat.number)
        self.bookings.clear()

    @property
    def final_price(self):
        total = 0
        for booking in self.bookings:
            if booking.ticketType == BookingType.FULL_PRICE:
                total += 30
            elif booking.ticketType == BookingType.DISCOUNTED:
                total += 20
        return total
    
    def confirm_purchase(self):
        for booking in self.bookings:
            booking.session.confirm_seat(booking.seat.row, booking.seat.number)
            self.user.bookings.append(booking)
        self.clear()