import bcrypt from 'bcrypt';


export class User {
    private constructor (
        public name: string,
        public email: string,
        public password: string,
        public id?: string
    ) {}

    static createUser (name: string, email: string, password: string, id: string): User {
        const saltRounds = 10;
        return new User(name, email, bcrypt.hashSync(password, saltRounds), id)        
    }

    static checkUserPassword (password: string, hashed: string): boolean {
        return bcrypt.compareSync(password, hashed)
    }
}