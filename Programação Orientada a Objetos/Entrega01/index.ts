import { Bikes } from "./bikes";
import { Cliente } from "./cliente";
import { Contrato } from "./contrato";

const Thiago = new Cliente("Thiago", "111222333-45", "01/01/1970")
const monark_bike = new Bikes("Monark", "Urban", "Vermelha", 1, 26, "001")
const contrato1 = new Contrato(monark_bike, Thiago, 120, 24)
contrato1.cliente.contrato()
console.log(Thiago.vezesContratado)
