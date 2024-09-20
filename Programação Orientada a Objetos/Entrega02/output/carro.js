"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Carro = void 0;
const modelo_1 = require("./modelo");
class Carro {
    constructor(placa, modelo, cor) {
        this.placa = placa;
        this.modelo = modelo;
        this.cor = cor;
    }
}
exports.Carro = Carro;
const ka = new modelo_1.Modelo('ford', 'ka', 5, 20000, 'gasolina');
const carroJoao = new Carro('abc-1234', ka, 'prata');
