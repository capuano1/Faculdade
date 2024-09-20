export class Bike {
    constructor (
        public name: string,
        public type: string,
        public bodySize: number,
        public maxLoad: number,
        public rate: number,
        public description: string,
        public ratings: number,
        public imageUrls: string[],
        public id?: string
    ) {}
    //id? significa que o atributo é OPCIONAL, então podemos ou não dar esse atributo.
    //No caso, esse id seria por conta de uma base de dados que poderíamos estar puxando essas info,
    //que geralmente nos dão um ID.
}