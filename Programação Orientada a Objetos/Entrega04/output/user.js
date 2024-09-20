"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.User = void 0;
const bcrypt_1 = __importDefault(require("bcrypt"));
class User {
    constructor(name, email, password, id) {
        this.name = name;
        this.email = email;
        this.password = password;
        this.id = id;
    }
    static createUser(name, email, password, id) {
        const saltRounds = 10;
        return new User(name, email, bcrypt_1.default.hashSync(password, saltRounds), id);
    }
    static checkUserPassword(password, hashed) {
        return bcrypt_1.default.compareSync(password, hashed);
    }
}
exports.User = User;
