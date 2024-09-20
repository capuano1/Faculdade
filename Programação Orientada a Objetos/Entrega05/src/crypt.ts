import bcrypt from 'bcrypt'

export class Crypt {
    private rounds = 10
    //Método assíncrono, sempre retorna uma Promise (uma promessa)
    async encrypt (plain: string): Promise<string> {
        return await bcrypt.hash(plain, this.rounds)
    }

    async compare (plain: string, encrypted: string): Promise<boolean> {
        return await bcrypt.compare(plain, encrypted)
    }
}
//Fazer assim, em um .ts diferente, faz com que a gente possa simplesmente mudar a nossa
//implementação sem trazer problemas aos outros .ts. Fora isso, caso a gente decida usar
//criptografia em outras partes do código, também facilita caso a gente mude. Aí, só
//precisamos mudar duas linhas do crypt.ts ao invés de diversas linhas de diversas .ts