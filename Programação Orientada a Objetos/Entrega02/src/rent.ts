import { Bike } from "./bike";
import { User } from "./user";

export class Rent {
    //Colocamos como private já que não queremos que um outro script simplesmente crie um Rent.
    //Não queremos isso pois queremos usar os métodos static para poder checar se nós podemos
    //criar ou não, já que precisamos checar se a data está ou não intersectando
    private constructor (
        public bike: Bike,
        public user: User,
        public dateFrom: Date,
        public dateTo: Date,
        public dateReturned?: Date
    ) {}
    //Poderíamos fazer a checagem direto dentro do constructor {}, porém o prof prefere fazer em
    //um método diferente
    
    static create(rents: Rent[], bike: Bike, user: User, startDate: Date, endDate: Date): Rent {
        const canCreate = Rent.canRent(rents, startDate, endDate)
        if (canCreate) {
            return new Rent(bike, user, startDate, endDate)
        }
        //Em questão da identação do if: Mesmo tendo apenas 1 linha, podemos não usar chaves. Porém,
        //um colega programador pode não notar e achar que tem chaves e colocar mais uma linha,
        //o que daria problema no código. Então, boa conduta de identação seria ou deixar na mesma
        //linha, caso não queira usar {}, ou simplesmente usar {}
        //Esse throw é uma exceção basicamente, então com isso damos um erro no código
        throw new Error("Overlapping dates.")
    }

    static canRent(rents: Rent[], startDate: Date, endDate: Date): boolean {
        return !rents.some(rent => {
                return startDate <= rent.dateTo && endDate >= rent.dateFrom
            }
        )
        //O some faz com que se no mínimo 1 dos rents no array for verdadeiro, ele irá
        //retornar verdadeiro. Dessa forma, ele retornaria true caso tenha ao menos 1 rent
        //intersectando. Dessa maneira, retornamos o contrário disso, não permitindo o aluguel
    }
}

//canRent poderia estar aqui fora, como function canRent, mas como estamos em orientação a objeto,
//vamos fazer de um modo mais orientado a objeto, como um método estático