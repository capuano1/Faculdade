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
1. Create session
2. Session has unique ID
3. Calculate end time
4. Check if seat is available
5. Get all available seats
6. Detect session overlap same room
7. No overlap different rooms
8. No overlap sequential sessions

## User Tests
1. Create user
2. User has unique ID
3. User bookings start empty

## Booking Tests
1. Create booking
2. Booking has unique ID
3. Booking records current time
4. Calculate total price
5. Booking added to user bookings
6. Booking added to session bookings
7. Confirm booking
8. Confirm fails if any seat not reserved
9. Cancel booking

## Test associations
1. Create room, add session and book seats
2. Prevent double booking
3. Prevent overlapping sessions
4. Session capacity management

Using this test list as a roadmap, you'll implement each test and then write the minimal code required to make it pass. This TDD approach will naturally guide the development of your domain model while ensuring all functionality is properly tested.