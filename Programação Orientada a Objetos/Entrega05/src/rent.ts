import { Bike } from "./bike";
import { User } from "./user";

export class Rent {
    //Colocamos como private já que não queremos que um outro script simplesmente crie um Rent.
    //Não queremos isso pois queremos usar os métodos static para poder checar se nós podemos
    //criar ou não, já que precisamos checar se a data está ou não intersectando
    public dateTo: Date
    constructor (
        public bike: Bike,
        public user: User,
        public dateFrom: Date
    ) {}
}