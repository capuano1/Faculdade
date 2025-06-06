import pytest
from datetime import datetime, timedelta
from test.builder.movie_builder import MovieBuilder
from src.domain.model import Room, Theater, Movie, Session, SeatStatus
from src.domain.errors import OverlappingSessionError

def test_can_create_session():
    room = Room("1")
    movie = Movie("Inception", 148, "Inception Description")
    movieTime = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movieTime)
    assert session.room == room
    assert session.movie == movie
    assert session.startTime == movieTime

def test_can_get_end_time():
    room = Room("1")
    movie = Movie("Inception", 148, "Inception Description")
    movieTime = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movieTime)
    assert session.get_end_time == movieTime + movie.get_duration_in_timedelta()

def test_can_check_how_many_seats_available():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(148).build()
    movieTime = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movieTime)
    
    # Initially all seats should be available
    assert len(session.available_seats) == 100
    
    # Mark a seat as taken
    session.reserve_seat('A', 5)
    assert len(session.available_seats) == 99

def test_seats_treated_differently_between_sessions():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(148).build()
    movieTime = datetime(2022, 10, 22, 14, 30)
    session1 = Session(room, movie, movieTime)
    
    # Reserve a seat in session1
    session1.reserve_seat('A', 5)
    
    # Create a new session
    session2 = Session(room, movie, movieTime)
    
    # In session2, the seat should still be available
    assert len(session2.available_seats) == 100
    assert any(seat.row == 'A' and seat.number == 5 and seat.is_available for seat in session2.available_seats)

def test_can_check_if_seat_is_available():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(148).build()
    movieTime = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movieTime)
    
    # Initially all seats should be available
    assert session.get_seat_status("A", 5) == SeatStatus.AVAILABLE
    
    # Reserve the seat
    session.reserve_seat("A", 5)
    
    # Assert that it is now reserved
    assert session.get_seat_status("A", 5) == SeatStatus.RESERVED

def test_cannot_register_overlapping_sessions():
    room = Room("1")
    theater = Theater()
    movie = MovieBuilder().aMovie().with_duration(148).build()
    movieTime = datetime(2022, 10, 22, 14, 30)
    session1 = Session(room, movie, movieTime)
    theater.add_session(session1)
    
    # Create a second session that overlaps with the first
    overlapping_time = datetime(2022, 10, 22, 15, 0)
    session2 = Session(room, movie, overlapping_time)
    
    with pytest.raises(OverlappingSessionError):
        theater.add_session(session2)

def test_should_not_detect_overlapping_sessions_on_different_rooms():
    room1 = Room("1")
    room2 = Room("2")
    theater = Theater()
    movie = MovieBuilder().aMovie().with_duration(148).build()
    movieTime = datetime(2022, 10, 22, 14, 30)
    
    session1 = Session(room1, movie, movieTime)
    theater.add_session(session1)
    
    # Create a second session in a different room
    session2 = Session(room2, movie, movieTime)
    
    # This should not raise an error
    theater.add_session(session2)

    assert theater.get_session_by_id(session1.id) == session1
    assert theater.get_session_by_id(session2.id) == session2

def test_should_not_detect_overlapping_on_sequential_sessions():
    room = Room("1")
    theater = Theater()
    movie = MovieBuilder().aMovie().with_duration(148).build()
    
    # First session starts at 14:30
    session1 = Session(room, movie, datetime(2022, 10, 22, 14, 30))
    theater.add_session(session1)
    
    # Second session starts 10 minutes after the first ends
    second_session_start = session1.get_end_time + timedelta(minutes=10)
    session2 = Session(room, movie, second_session_start)
    
    # This should not raise an error
    theater.add_session(session2)

    assert theater.get_session_by_id(session1.id) == session1
    assert theater.get_session_by_id(session2.id) == session2