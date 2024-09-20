"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Crypt = void 0;
const bcrypt_1 = __importDefault(require("bcrypt"));
class Crypt {
    constructor() {
        this.rounds = 10;
    }
    //Método assíncrono, sempre retorna uma Promise (uma promessa)
    encrypt(plain) {
        return __awaiter(this, void 0, void 0, function* () {
            return yield bcrypt_1.default.hash(plain, this.rounds);
        });
    }
    compare(plain, encrypted) {
        return __awaiter(this, void 0, void 0, function* () {
            return yield bcrypt_1.default.compare(plain, encrypted);
        });
    }
}
exports.Crypt = Crypt;
//Fazer assim, em um .ts diferente, faz com que a gente possa simplesmente mudar a nossa
//implementação sem trazer problemas aos outros .ts. Fora isso, caso a gente decida usar
//criptografia em outras partes do código, também facilita caso a gente mude. Aí, só
//precisamos mudar duas linhas do crypt.ts ao invés de diversas linhas de diversas .ts
