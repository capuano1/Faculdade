from src.domain.model import Room

def test_create_room():
    room = Room("1")
    assert len(room.rows) == 10
    assert len(room.rows[5]) == 10
    first_seat = room.rows[0][0]
    assert first_seat.row == "A"
    assert first_seat.number == 1

def test_create_room_with_custom_map():
    seats = [10, 10, 10, 20, 20, 10, 10]
    room = Room("1", seats)
    assert len(room.rows[3]) == 20

def test_capacity_for_default_map():
    room = Room("1")
    assert room.capacity() == 100

def test_get_available_seats():
    room = Room("1")
    assert room.available_seats() == 100