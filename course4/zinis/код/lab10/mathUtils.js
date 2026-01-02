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
Object.defineProperty(exports, "__esModule", { value: true });
exports.isCoprime = exports.generateCoprimeNumber = exports.generatePrimeNumber = void 0;
const big_integer_1 = __importStar(require("big-integer"));
const generatePrimeNumber = (bitLength) => {
    let primeCandidate;
    do {
        primeCandidate = big_integer_1.default.randBetween((0, big_integer_1.default)(2).pow(bitLength - 1), (0, big_integer_1.default)(2).pow(bitLength));
    } while (!primeCandidate.isPrime());
    return primeCandidate;
};
exports.generatePrimeNumber = generatePrimeNumber;
const generateCoprimeNumber = (fi) => {
    const min = fi.plus(1);
    const max = fi.times(2);
    let coprime;
    do {
        coprime = big_integer_1.default.randBetween(min, max);
    } while (!(0, exports.isCoprime)(fi, coprime));
    return coprime;
};
exports.generateCoprimeNumber = generateCoprimeNumber;
const isCoprime = (a, b) => {
    return (0, big_integer_1.gcd)(a, b).eq(1);
};
exports.isCoprime = isCoprime;
