import { Bike } from "../../../src/bike"
import prisma from "../../../src/external/database/db"
import { PrismaBikeRepo } from "../../../src/external/database/prisma-bike-repo"

describe('PrismaBikeRepo', () => {
    beforeEach(async () => {
        await prisma.bike.deleteMany({})
    })

    afterAll(async () => {
        await prisma.bike.deleteMany({})
    })

    it('adds a bike in the database', async () => {
        const addBike = new Bike(
            'Caloi',
            'Mountain',
            22,
            120,
            5,
            'Mountain Bike',
            5,
            ['']
        )
        const repo = new PrismaBikeRepo()
        const bikeId = await repo.add(addBike)
        expect(bikeId).toBeDefined()
        const addedBike = await repo.find(addBike.id)
        expect(addedBike.id).toEqual(
            addBike.id
        )
    })

    it('removes a user from the database', async () => {
        const addBike = new Bike(
            'Caloi',
            'Mountain',
            22,
            120,
            5,
            'Mountain Bike',
            5,
            ['']
        )
        const repo = new PrismaBikeRepo()
        await repo.add(addBike)
        await repo.remove(addBike.id)
        const removedBike = await repo.find(addBike.id)
        expect(removedBike).toBeNull()
    })

    it('lists users in the database', async () => {
        const bike1 = new Bike(
            'Caloi',
            'Mountain',
            22,
            120,
            5,
            'Mountain Bike',
            5,
            ['']
        )
        const bike2 = new Bike(
            'Caloi',
            'Speed',
            24,
            100,
            5,
            'Speed Bike',
            5,
            ['']
        )
        const repo = new PrismaBikeRepo()
        await repo.add(bike1)
        await repo.add(bike2)
        const bikeList = await repo.list()
        expect(bikeList.length).toEqual(2)
    })

    it('updates user in the database', async () => {
        const bike1 = new Bike(
            'Caloi',
            'Mountain',
            22,
            120,
            5,
            'Mountain Bike',
            5,
            ['']
        )
        const bike2 = new Bike(
            'Caloi',
            'Speed',
            24,
            100,
            5,
            'Speed Bike',
            5,
            ['']
        )
        const repo = new PrismaBikeRepo()
        await repo.add(bike1)
        await repo.update(bike1.id, bike2)
        const bikeList = await repo.list()
        expect(bikeList.length).toEqual(1)
        expect(bikeList[0].type).toEqual('Speed')
    })
})