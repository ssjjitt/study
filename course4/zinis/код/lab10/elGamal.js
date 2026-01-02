"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.ElGamal = void 0;
const crypto = __importStar(require("crypto"));
const big_integer_1 = __importDefault(require("big-integer"));
const mathUtils_1 = require("./mathUtils");
class ElGamal {
    constructor() {
        this.p = (0, mathUtils_1.generatePrimeNumber)(100);
        this.g = (0, mathUtils_1.generateCoprimeNumber)(this.p);
        this.x = big_integer_1.default.randBetween((0, big_integer_1.default)(2), this.p.subtract(1));
        this.y = this.g.modPow(this.x, this.p);
    }
    getPublicKey() {
        return { p: this.p, g: this.g, y: this.y };
    }
    createDigitalSignature(message) {
        const hash = crypto.createHash('sha256').update(message, 'utf8').digest();
        let digitalSignI;
        do {
            let k = big_integer_1.default.randBetween((0, big_integer_1.default)(2), this.p.subtract(2));
            while (!(0, mathUtils_1.isCoprime)(k, this.p.subtract(1))) {
                k = big_integer_1.default.randBetween((0, big_integer_1.default)(2), this.p.subtract(2));
            }
            digitalSignI = [];
            digitalSignI[0] = this.g.modPow(k, this.p);
            let temp = (0, big_integer_1.default)(hash.readBigInt64LE()).subtract(this.x.multiply(digitalSignI[0]));
            temp = temp.multiply(k.modInv(this.p.subtract(1))).mod(this.p.subtract(1));
            if (temp.isNegative()) {
                temp = this.p.subtract(1).subtract(temp.abs());
            }
            digitalSignI[1] = temp;
        } while (digitalSignI[1].equals(0));
        return digitalSignI;
    }
    verifyDigitalSignature(message, digitalSignature) {
        const hash = crypto.createHash('sha256').update(message, 'utf8').digest();
        const leftPart = this.g.modPow(hash.readBigInt64LE(), this.p);
        const rightPart = this.y.modPow(digitalSignature[0], this.p)
            .multiply(digitalSignature[0].modPow(digitalSignature[1], this.p))
            .mod(this.p);
        return leftPart.equals(rightPart);
    }
}
exports.ElGamal = ElGamal;
