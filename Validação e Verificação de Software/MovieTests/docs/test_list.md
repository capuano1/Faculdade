Here's a comprehensive item list of all the tests organized by domain entity:

## Seat Tests
X Create seat with row and number - defaults to available
X Reserve available seat
X Cannot reserve already reserved seat
X Confirm reserved seat
X Cannot confirm available seat
X Cannot confirm occupied seat
X Cannot reserve occupied seat
X Release seat

## Room Tests
X Create theater room - creates seats automatically
X Get capacity
X Get available seats

# Theater Tests
x Can add room to theater
X Can remove room from theater
X Each theater room has unique name

## Movie Tests
X Create movie
X Movie has unique name
X Get formatted duration (90 minutes movie -> 1h30min)
X Get duration as timedelta (converts movie length in minutes to a timedelta object for time calculations)

## Session Tests
X Create session
X Calculate end time
X Check if seat is available
X Check if seats are treated differently between sessions
X Detect session overlap same room
X No overlap different rooms
X No overlap sequential sessions

## User Tests
X User bookings start empty

## Booking Tests
X Create booking
X Booking has unique ID
X Booking records current time
X Calculate total price
X Booking added to user bookings
X Confirm booking
X Cancel booking

## Test associations
1. Create room, add session and book seats
2. Prevent double booking
3. Prevent overlapping sessions
4. Session capacity management

Using this test list as a roadmap, you'll implement each test and then write the minimal code required to make it pass. This TDD approach will naturally guide the development of your domain model while ensuring all functionality is properly tested.