export class CannotDeleteUserWithRentError extends Error {
    public readonly name = 'CannotDeleteUserWithRentError'

    constructor() {
        super('Cannot delete user with an active rent.')
    }
}