import { Bike } from "./bike";
import { Rent } from "./rent";
import { User } from "./user";
import crypto from 'crypto';

export class App {
    users: User[] = []
    bikes: Bike[] = []
    rents: Rent[] = []
    //Em uma aplicação real, essas coisas estariam em um banco de dados, não no código. Pois o
    //banco de dados é persistente, ou seja, o dado fica ainda que a gente desligue o programa.
    //O programa aqui perderia os dados.

    addUser(user: User): void {
        //push adiciona novos elementos em um array
        //Vamos verificar aqui se o usuário já está cadastrado, dentro do array
        //== faz uma comparação mas ignora o tipo de dado, === compara incluindo o tipo de dado
        //'1' == 1 => true; '1' === 1 => false
        //Apesar dos dados nesse caso serem iguais, usamos === para ser mais safe
        //Além do some, temos o every também, que aí todos os elementos do array devem satisfazer
        if (this.users.some(rUser => {return rUser.email === user.email})) {
            throw new Error("User already exists")
        }
        user.id = crypto.randomUUID()
        this.users.push(user)
    }
    addBike(bike: Bike): void {
        bike.id = crypto.randomUUID()
        this.bikes.push(bike)
    }
    findBikes(UUID: string): number {
        return this.bikes.findIndex(rBike => {return rBike.id === UUID})
    }
    findUser(email: string): number {
        return this.users.findIndex(rUser => {return rUser.email == email})
    }
    findRent(UUID: string, email: string): number {
        return this.rents.findIndex(rRent => {return rRent.bike.id === UUID && rRent.user.email === email})
    }
    removeBike(UUID: string): void {
        var index = this.findBikes(UUID)
        if (index == -1) {
            throw new Error("Bike not found")
        }
        this.bikes.splice(index, 1)
    }
    removeUser(email: string): void {
        var index = this.findUser(email)
        if (index == -1) {
            throw new Error("User not found")
        }
        this.users.splice(index, 1)
    }
    //Passar a descrição da bike e email do user para encontrar e fazer a reserva
    rentBike(UUID: string, email: string, startDate: Date, endDate: Date): void {
        const bike = this.bikes[this.findBikes(UUID)]
        const user = this.users[this.findUser(email)]
        const bRents = this.rents.filter(bRent => bRent.bike.id === bike.id)
        this.rents.push(Rent.create(bRents, bike, user, startDate, endDate))
    }
    returnBike(email: string, UUID: string): void {
        var index = this.findRent(UUID, email)
        this.rents[index].dateReturned = new Date()
    }
}