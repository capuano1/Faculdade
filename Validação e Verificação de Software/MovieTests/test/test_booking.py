from src.domain.model import Booking, User, Session, Room, BookingType, Movie, ShoppingCart, Seat, SeatStatus
from test.builder.movie_builder import MovieBuilder
from datetime import datetime

def test_can_calculate_final_price():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(120).build()
    movie_time = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movie_time)
    user = User("test_user")
    shopping_cart = ShoppingCart(user)
    
    seat = Seat("A", 5)
    
    # Create a booking and insert it into the shopping cart
    booking = Booking(session, seat, BookingType.FULL_PRICE)
    shopping_cart.add_booking(booking)
    
    # Assert that the final price is equal to the initial price
    assert shopping_cart.final_price == 30

def test_can_reserve_seat_on_booking():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(120).build()
    movie_time = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movie_time)
    user = User("test_user")
    shopping_cart = ShoppingCart(user)
    
    seat = Seat("A", 5)
    
    # Create a booking and insert it into the shopping cart
    booking = Booking(session, seat, BookingType.FULL_PRICE)
    shopping_cart.add_booking(booking)
    
    # Assert that the seat is reserved
    assert session.get_seat_status("A", 5) == SeatStatus.RESERVED

def test_can_remove_booking_and_release_seat():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(120).build()
    movie_time = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movie_time)
    user = User("test_user")
    shopping_cart = ShoppingCart(user)
    
    seat = Seat("A", 5)
    
    # Create a booking and insert it into the shopping cart
    booking = Booking(session, seat, BookingType.FULL_PRICE)
    shopping_cart.add_booking(booking)
    
    # Remove the booking from the shopping cart
    shopping_cart.remove_booking(booking)
    
    # Assert that the seat is released
    assert session.get_seat_status("A", 5) == SeatStatus.AVAILABLE

def test_can_clear_shopping_cart_and_release_all_seats():
    room = Room("1")
    movie = MovieBuilder().aMovie().with_duration(120).build()
    movie_time = datetime(2022, 10, 22, 14, 30)
    session = Session(room, movie, movie_time)
    user = User("test_user")
    shopping_cart = ShoppingCart(user)
    
    seat1 = Seat("A", 5)
    seat2 = Seat("B", 9)
    
    # Create bookings and insert them into the shopping cart
    booking1 = Booking(session, seat1, BookingType.FULL_PRICE)
    booking2 = Booking(session, seat2, BookingType.FULL_PRICE)
    shopping_cart.add_booking(booking1)
    shopping_cart.add_booking(booking2)
    
    # Clear the shopping cart
    shopping_cart.clear()
    
    # Assert that all seats are released
    assert session.get_seat_status("A", 5) == SeatStatus.AVAILABLE
    assert session.get_seat_status("B", 9) == SeatStatus.AVAILABLE