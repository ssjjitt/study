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
exports.RSA = void 0;
const crypto = __importStar(require("crypto"));
const big_integer_1 = __importDefault(require("big-integer"));
const mathUtils_1 = require("./mathUtils");
class RSA {
    constructor() {
        this.p = (0, mathUtils_1.generatePrimeNumber)(100);
        this.q = (0, mathUtils_1.generatePrimeNumber)(100);
        this.n = this.p.multiply(this.q);
        this.fi = this.p.subtract(1).multiply(this.q.subtract(1));
        this.e = (0, mathUtils_1.generateCoprimeNumber)(this.fi);
        this.d = this.e.modInv(this.fi);
    }
    getPublicKey() {
        return { e: this.e, n: this.n };
    }
    createDigitalSignature(text) {
        const hash = crypto.createHash('sha256').update(text, 'utf8').digest();
        return (0, big_integer_1.default)(hash.readBigInt64LE()).modPow(this.d, this.n);
    }
    verifyDigitalSignature(text, digitalSign) {
        const signBytes = digitalSign.modPow(this.e, this.n);
        const receivedHash = crypto.createHash('sha256').update(text, 'utf8').digest();
        return (0, big_integer_1.default)(receivedHash.readBigInt64LE()).eq(signBytes);
    }
}
exports.RSA = RSA;
