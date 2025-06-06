from src.domain.model import User

def test_user_booking_list_begins_empty():
    user = User("test_user")
    assert len(user.bookings) == 0, "Booking list should start empty"