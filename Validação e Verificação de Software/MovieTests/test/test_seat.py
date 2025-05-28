from src.domain.model import Seat, SeatStatus

def test_create_seat_with_row_and_number():
    seat = Seat(row='A', number=1)
    assert seat.row == 'A'
    assert seat.number == 1
    assert seat.is_available is True

def test_reserve_seat():
    seat = Seat(row='A', number=1)
    assert seat.reserve() is True
    assert seat.is_available is False

def test_cannot_reserve_reserved_seat():
    seat = Seat(row='A', number=1)
    seat.reserve()
    assert seat.reserve() is False

def test_confirm_reserved_seat():
    seat = Seat(row='A', number=1)
    seat.reserve()
    assert seat.confirm() is True
    assert seat.is_available is False
    assert seat.status == SeatStatus.OCCUPIED

def test_cannot_confirm_available_seat():
    seat = Seat(row='A', number=1)
    assert seat.confirm() is False
    assert seat.is_available

def test_cannot_confirm_occupied_seat():
    seat = Seat(row='A', number=1)
    seat.reserve()
    seat.confirm()
    assert seat.confirm() is False

def test_cannot_reserve_occupied_seat():
    seat = Seat(row='A', number=1)
    seat.reserve()
    seat.confirm()
    assert seat.reserve() is False

def test_release_seat():    
    seat = Seat(row='A', number=1)
    seat.reserve()
    seat.release()
    assert seat.is_available