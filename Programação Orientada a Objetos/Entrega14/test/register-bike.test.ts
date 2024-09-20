import request from 'supertest'
import server from '../src/server'
import prisma from '../src/external/database/db'

describe('Register bike route', () => {
    beforeEach(async () => {
        await prisma.bike.deleteMany({})
    })

    afterAll(async () => {
        await prisma.bike.deleteMany({})
    })

    it('registers a bike with valid data', async () => {
        await request(server)
            .post('/api/bike')
            .send({
                name: 'Caloi 10',
                type: 'Speed',
                bodySize: 15,
                maxLoad: 200,
                rate: 25,
                description: 'Caloi 10 Speed 15',
                ratings: 5,
                imageUrls: ['http://image1.com', 'http://image2.com'],
                available: true,
                location: {
                    latitude: 10,
                    longitude: 10
                }
            })
            .expect(201)
            .then((res) => {
                expect(res.body.id).toBeDefined()
            })
    })

    it('registers two bikes of the same model with valid data and different ids', async () => {
        let id1
        await request(server)
            .post('/api/bike')
            .send({
                name: 'Caloi 10',
                type: 'Speed',
                bodySize: 15,
                maxLoad: 200,
                rate: 25,
                description: 'Caloi 10 Speed 15',
                ratings: 5,
                imageUrls: ['http://image1.com', 'http://image2.com'],
                available: true,
                location: {
                    latitude: 10,
                    longitude: 10
                }
            })
            .expect(201)
            .then((res) => {
                id1 = res.body.id
            })

        await request(server)
            .post('/api/bike')
            .send({
                name: 'Caloi 10',
                type: 'Speed',
                bodySize: 15,
                maxLoad: 200,
                rate: 25,
                description: 'Caloi 10 Speed 15',
                ratings: 5,
                imageUrls: ['http://image1.com', 'http://image2.com'],
                available: true,
                location: {
                    latitude: 10,
                    longitude: 10
                }
            })
            .expect(201)
            .then((res) => {
                expect(res!=id1).toBeTruthy
            })
    })

})



