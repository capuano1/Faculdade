from src.domain.model import Room, Theater
from src.domain.errors import DuplicateRoomName
import pytest

def test_can_add_room_to_theater():
    theater = Theater()
    room1 = Room("1")
    theater.add(room1)
    assert room1 in theater.rooms

def test_can_remove_room_from_theater():
    theater = Theater()
    room1 = Room("1")
    theater.add(room1)
    theater.remove(room1)
    assert room1 not in theater.rooms

def test_theater_room_has_unique_name():
    theater = Theater()
    room1 = Room("1")
    room2 = Room("1")
    theater.add(room1)
    with pytest.raises(DuplicateRoomName):
        theater.add(room2)