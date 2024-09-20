import { Bike } from "./bike";
import { Rent } from "./rent";
import { User } from "./user";
import { App } from "./app";
import sinon from 'sinon' //=> fake timers, para testes
/*
const app = new App
const mbike = new Bike('mountain bike', 'mountain', 123, 500, 100.5, 'desc', 5, [])
const sbike = new Bike('speed bike', 'speed', 456, 250, 90.5, 'desc', 4, [])
//Quando criamos uma Date no js, ele coloca como a data atual
const today = new Date()
const twoDaysFromToday = new Date()
twoDaysFromToday.setDate(twoDaysFromToday.getDate() + 2)
const tomorrow = new Date()
tomorrow.setDate(tomorrow.getDate() + 1)
const sevenDaysFromToday = new Date()
sevenDaysFromToday.setDate(sevenDaysFromToday.getDate() + 7)
const sevenDaysAgo = new Date()
sevenDaysAgo.setDate(sevenDaysAgo.getDate() - 7)
const twoDaysAgo = new Date()
twoDaysAgo.setDate(twoDaysAgo.getDate() - 2)
//const rent1 = Rent.create([], mbike, maria, today, twoDaysFromToday)
//const rent2 = Rent.create([rent1], bike, user, tomorrow, sevenDaysFromToday)
//Como ele vai dar uma exceção, por conta da bike não estar disponível, ele para o código e dá erro
//console.log(rent2)

app.addUser('Maria', 'maria@mail.com', '1234')
app.addUser('João', 'joao@mail.com', '5678')
app.addBike(mbike)
app.addBike(sbike)
console.log(app.users)
console.log(app.bikes)
app.rentBike(app.bikes[app.bikes.findIndex(rBike => {return rBike.name === 'speed bike'})].id, 'joao@mail.com', '5678', sevenDaysAgo, twoDaysAgo)
console.log(app.rents)
console.log("FINALIZADO 1")
app.removeUser('maria@mail.com')
app.removeBike(app.bikes[app.bikes.findIndex(rBike => {return rBike.name === 'mountain bike'})].id)
app.returnBike('joao@mail.com', app.bikes[app.bikes.findIndex(rBike => {return rBike.name === 'speed bike'})].id)
console.log(app.users)
console.log(app.bikes)
console.log(app.rents)
*/
// PROFESSOR, CRIANDO MAIN POR CONTA DO ASYNC (tudo precisa ser async se chama métodos async)
/*async*/ function main(): void {
    let clock = sinon.useFakeTimers()
    let app = new App()
    app.addUser('Jose', 'jose@mail.com', '1234')
    console.log(app.users) //=> Para ver as senhas criptografadas
    //console.log(await app.authenticate('jose@mail.com', '4321')) //=> Imprime "false"
    //console.log(await app.authenticate('jose@mail.com', '1234')) //=> Imprime "true"
    const bike = new Bike('Caloi Mountain', 'Mountain', 1234, 1234, 100.0, 'My Bike', 5, [])
    app.addBike(bike)
    console.log("Bike disponível: ", bike.available) //=> Deve estar disponível
    app.rentBike(bike.id, 'jose@mail.com', '1234')
    console.log("Bike disponível: ", bike.available) //=> Não pode estar disponível
    clock.tick(1000 * 60 * 60)
    console.log(app.returnBike('jose@mail.com', bike.id))
    console.log("Bike disponível: ", bike.available) //=> Deve estar disponível
}

main()