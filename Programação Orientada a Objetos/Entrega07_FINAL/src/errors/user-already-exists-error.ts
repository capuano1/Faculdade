export class UserAlreadyExistsError extends Error {
    public readonly name = 'UserAlreadyExistsError'

    constructor() {
        super('User already exists.')
    }
}