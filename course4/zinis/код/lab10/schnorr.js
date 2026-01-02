"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Schnorr = void 0;
const crypto_1 = __importDefault(require("crypto"));
const big_integer_1 = __importDefault(require("big-integer"));
class Schnorr {
    constructor() {
        this.p = (0, big_integer_1.default)(48731);
        this.q = (0, big_integer_1.default)(443);
        this.g = (0, big_integer_1.default)(11444);
        do {
            this.x = big_integer_1.default.randBetween(1, this.q.subtract(1));
        } while (this.x.compare(this.q) >= 0);
        this.y = this.g.modPow(this.x, this.p).modInv(this.p);
    }
    getPublicKey() {
        return { p: this.p, q: this.q, g: this.g, y: this.y };
    }
    generateDigitalSignature(message) {
        let k;
        do {
            k = big_integer_1.default.randBetween(2, this.q.subtract(1));
        } while (!(k.compare(1) > 0 && k.compare(this.q) < 0));
        const a = this.g.modPow(k, this.p);
        message += a.toString();
        const hash = crypto_1.default.createHash('sha256').update(message, 'utf8').digest();
        return [
            (0, big_integer_1.default)(hash.readBigUInt64LE()),
            k.add(this.x.multiply((0, big_integer_1.default)(hash.readBigUInt64LE()))).mod(this.q)
        ];
    }
    verifyDigitalSignature(message, digitalSignature) {
        let x = this.g.modPow(digitalSignature[1], this.p)
            .multiply(this.y.modPow(digitalSignature[0], this.p)).mod(this.p);
        message += x.toString();
        const receivedHash = crypto_1.default.createHash('sha256').update(message, 'utf8').digest();
        return digitalSignature[0].equals(receivedHash.readBigUInt64LE());
    }
}
exports.Schnorr = Schnorr;
