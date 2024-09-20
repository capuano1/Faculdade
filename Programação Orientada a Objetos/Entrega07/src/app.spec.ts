import sinon from "sinon"
import { App } from "./app"
import { Bike } from "./bike"
import { User } from "./user"
import { Location } from "./location"

describe('App', () => {
    it('should correctly register a user', async () => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        const id = await app.registerUser(user)
        expect(id).not.toBeUndefined
    })

    it('should throw exception when registering already existing email', async() => {
        await expect (async () => {
            const app = new App()
            const user1 = new User('Jose', 'jose@mail.com', '1234')
            const user2 = new User('Josias', 'jose@mail.com', '5678')
            await app.registerUser(user1)
            await app.registerUser(user2)
        }).rejects.toThrowError()
    })

    it('should correctly authenticate user', async() => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        await app.registerUser(user)
        const isValid = await app.authenticate('jose@mail.com', '1234')
        expect(isValid).toBe(true)
    })

    it('should correctly register bike', () => {
        const app = new App()
        const bike = new Bike('caloi mountainbike', 'mountain bike',
            1234, 1234, 100.0, 'My bike', 5, [])
        const id = app.registerBike(bike)
        expect(id).not.toBeUndefined()
    })

    it('should correctly remove user', async() => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        await app.registerUser(user)
        app.removeUser('jose@mail.com')
        expect(app.findUser('jose@mail.com')).toBeUndefined()
    })

    it('should correctly rent a bike', async () => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        await app.registerUser(user)
        const bike = new Bike('caloi mountainbike', 'mountain bike',
            1234, 1234, 100.0, 'My bike', 5, [])
        app.registerBike(bike)
        app.rentBike(bike.id, user.email)
        const rent = app.rents.find(rent =>
            rent.bike.id === bike.id &&
            rent.user.email === user.email &&
            !rent.end
        )
        expect(rent).not.toBeUndefined
    })

    it('should not rent an unavailable bike', async() => {
        expect(async() => {
            const app = new App()
            const user1 = new User('Jose', 'jose@mail.com', '1234')
            const user2 = new User('Maria', 'maria@mail.com', '5678')
            await app.registerUser(user1)
            await app.registerUser(user2)
            const bike = new Bike('caloi mountainbike', 'mountain bike',
                1234, 1234, 100.0, 'My bike', 5, [])
            app.registerBike(bike)
            app.rentBike(bike.id, user1.email)
            app.rentBike(bike.id, user2.email)
        }).rejects.toThrowError
    })

    it('should correctly turn a returned bike available', async() => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        await app.registerUser(user)
        const bike = new Bike('caloi mountainbike', 'mountain bike',
            1234, 1234, 100.0, 'My bike', 5, [])
        app.registerBike(bike)
        app.rentBike(bike.id, user.email)
        app.returnBike(bike.id, user.email)
        expect(bike.available).toBe(true)
    })

    it('should correctly calculate the rent amount', async () => {
        const app = new App()
        const user = new User('Jose', 'jose@mail.com', '1234')
        await app.registerUser(user)
        const bike = new Bike('caloi mountainbike', 'mountain bike',
            1234, 1234, 100.0, 'My bike', 5, [])
        app.registerBike(bike)
        const clock = sinon.useFakeTimers();
        app.rentBike(bike.id, user.email)
        const hour = 1000 * 60 * 60
        clock.tick(2 * hour)
        const rentAmount = app.returnBike(bike.id, user.email)
        expect(rentAmount).toEqual(200.0)
    })

    it('should be able to move a bike to a specific location', () => {
        const app = new App()
        const bike = new Bike('caloi mountainbike', 'mountain bike',
            1234, 1234, 100.0, 'My bike', 5, [])
        app.registerBike(bike)
        const newYork = new Location(40.753056, -73.983056)
        app.moveBikeTo(bike.id, newYork)
        expect(bike.location.latitude).toEqual(newYork.latitude)
        expect(bike.location.longitude).toEqual(newYork.longitude)
    })

    it('should throw an exception when trying to move an unregistered bike', () => {
        expect(() => {
            const app = new App()
            const newYork = new Location(40.753056, -73.983056)
            app.moveBikeTo('UYTRYREUREUREUE', newYork)
        }).toThrowError()
    })
})