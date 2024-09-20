"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.App = void 0;
const rent_1 = require("./rent");
const user_1 = require("./user");
const crypto_1 = __importDefault(require("crypto"));
class App {
    constructor() {
        this.users = [];
        this.bikes = [];
        this.rents = [];
    }
    //Em uma aplicação real, essas coisas estariam em um banco de dados, não no código. Pois o
    //banco de dados é persistente, ou seja, o dado fica ainda que a gente desligue o programa.
    //O programa aqui perderia os dados.
    addUser(name, email, password) {
        //push adiciona novos elementos em um array
        //Vamos verificar aqui se o usuário já está cadastrado, dentro do array
        //== faz uma comparação mas ignora o tipo de dado, === compara incluindo o tipo de dado
        //'1' == 1 => true; '1' === 1 => false
        //Apesar dos dados nesse caso serem iguais, usamos === para ser mais safe
        //Além do some, temos o every também, que aí todos os elementos do array devem satisfazer
        if (this.users.some(rUser => { return rUser.email === email; })) {
            throw new Error("User already exists");
        }
        var user = user_1.User.createUser(name, email, password, crypto_1.default.randomUUID());
        this.users.push(user);
    }
    addBike(bike) {
        bike.id = crypto_1.default.randomUUID();
        this.bikes.push(bike);
    }
    allUsers() {
        console.log(this.users);
    }
    allRents() {
        console.log(this.rents);
    }
    allBikes() {
        console.log(this.bikes);
    }
    findBikes(UUID) {
        return this.bikes.findIndex(rBike => { return rBike.id === UUID; });
    }
    findUser(email) {
        return this.users.findIndex(rUser => { return rUser.email == email; });
    }
    findRent(UUID, email) {
        return this.rents.findIndex(rRent => { return rRent.bike.id === UUID && rRent.user.email === email; });
    }
    removeBike(UUID) {
        var index = this.findBikes(UUID);
        if (index == -1) {
            throw new Error("Bike not found");
        }
        this.bikes.splice(index, 1);
    }
    removeUser(email) {
        var index = this.findUser(email);
        if (index == -1) {
            throw new Error("User not found");
        }
        this.users.splice(index, 1);
    }
    //Passar a descrição da bike e email do user para encontrar e fazer a reserva
    rentBike(UUID, email, password, startDate, endDate) {
        const user = this.users[this.findUser(email)];
        if (!user_1.User.checkUserPassword(password, user.password)) {
            throw new Error("Wrong Password!");
        }
        const bike = this.bikes[this.findBikes(UUID)];
        const bRents = this.rents.filter(bRent => bRent.bike.id === bike.id);
        this.rents.push(rent_1.Rent.create(bRents, bike, user, startDate, endDate));
    }
    returnBike(email, UUID) {
        var index = this.findRent(UUID, email);
        this.rents[index].dateReturned = new Date();
    }
}
exports.App = App;
