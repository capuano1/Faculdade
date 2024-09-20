import express from 'express'
import bodyParser from 'body-parser'
import { Request, Response, NextFunction } from 'express'
import { App } from './app'
import { PrismaUserRepo } from './external/database/prisma-user-repo'
import { PrismaBikeRepo } from './external/database/prisma-bike-repo'
import { PrismaRentRepo } from './external/database/prisma-rent-repo'
import { DuplicateUserError } from './errors/duplicate-user-error'

const cors = (req: Request, res: Response, next: NextFunction): void => {
    res.set('access-control-allow-origin', '*')
    res.set('access-control-allow-headers', '*')
    res.set('access-control-allow-methods', '*')
    next()
}

const contentType = (req: Request, res: Response, next: NextFunction): void => {
    res.type('json')
    next()
}

const server = express()
server.use(bodyParser.json())
server.use(cors)
server.use(contentType)

const app = new App(
    new PrismaUserRepo(),
    new PrismaBikeRepo(),
    new PrismaRentRepo()
)

server.post('/api/users', async (req, res) => {
    try {
        const id = await app.registerUser(req.body)
        res.status(201).json({ id })
    } catch (e) {
        if (e instanceof DuplicateUserError) {
            res.status(400).json({
                message: 'Could not register user.'
            })
            return
        }
        res.status(500).json({
            message: 'Internal server error.'
        })        
    }
})

//Tive que colocar um catch aqui com um erro completamente genérico pois não criamos nenhum tipo de erro ao criar uma bike.
//Como não ocorrem bikes duplicadas, já que podemos ter duas bikes identicas para alugar, apenas diferenciadas pelo id, que é único e criado pelo sistema,
//então não consigo pensar em erros no momento que fariam sentido. Falta de informações pode ser segurada pelo front-end, ou seja,
//é de se esperar que o front-end não permita que seja realizada uma requisição com poucos argumentos

server.post('/api/bike', async (req, res) => {
    try {
        const id = await app.registerBike(req.body)
        res.status(201).json({ id })
    } catch (e) {
        res.status(500).json({
            message: 'Could not register bike.'
        })
    }
})

const port = 3000
server.listen(port, () => {
    console.log(`Server listening on port ${port}`)
})

export default server
