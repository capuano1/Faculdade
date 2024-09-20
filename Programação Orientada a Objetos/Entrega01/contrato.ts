import { Bikes } from "./bikes";
import { Cliente } from "./cliente";

export class Contrato {
    constructor (
        public bike: Bikes,
        public cliente: Cliente,
        public tempo: number,
        public valor: number
    ) {}
}