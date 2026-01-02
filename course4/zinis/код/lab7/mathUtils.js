"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.generateCoprime = exports.getInverseNumber = exports.gcd = exports.generateRandomNumber = void 0;
const big_integer_1 = __importDefault(require("big-integer"));
const generateRandomNumber = (n) => {
    const randomBits = [];
    for (let i = 0; i < n; i++) {
        const bit = Math.random() < 0.5 ? '0' : '1';
        randomBits.push(bit);
    }
    const randomString = randomBits.join('');
    return BigInt('0b' + randomString);
};
exports.generateRandomNumber = generateRandomNumber;
const gcd = (a, b) => {
    while (!b.isZero()) {
        const temp = b;
        b = a.mod(b);
        a = temp;
    }
    return a;
};
exports.gcd = gcd;
const getInverseNumber = (number, modulus) => {
    let m0 = modulus;
    let y = big_integer_1.default.zero;
    let x = big_integer_1.default.one;
    if (modulus.eq(1)) {
        return big_integer_1.default.zero;
    }
    while (number.gt(1)) {
        let quotient = number.divmod(modulus).quotient;
        let temp = modulus;
        modulus = number.divmod(modulus).remainder;
        number = temp;
        temp = y;
        y = x.minus(quotient.times(y));
        x = temp;
    }
    if (x.lt(0)) {
        x = x.plus(m0);
    }
    return x;
};
exports.getInverseNumber = getInverseNumber;
const generateCoprime = (n) => {
    const min = n.plus(1);
    const max = n.times(2);
    let coprime;
    do {
        coprime = big_integer_1.default.randBetween(min, max);
    } while (!(0, exports.gcd)(n, coprime).eq(1));
    return coprime;
};
exports.generateCoprime = generateCoprime;
