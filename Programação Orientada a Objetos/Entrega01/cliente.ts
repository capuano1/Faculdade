export class Cliente {
    vezesContratado: number = 0
    constructor(
        public nome: string,
        public cpf: string,
        public nascimento: string,
    ) {}

    public contrato(): void {
        this.vezesContratado += 1
    }
}