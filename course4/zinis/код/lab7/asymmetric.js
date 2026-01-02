"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.getDecryptedBinary = exports.decrypt = exports.encrypt = exports.generatePublicKey = exports.getPublicKeyParams = exports.generatePrivateKey = exports.Encoding = void 0;
const big_integer_1 = __importDefault(require("big-integer"));
const mathUtils_1 = require("./mathUtils");
const base64_1 = require("./base64");
var Encoding;
(function (Encoding) {
    Encoding[Encoding["ASCII"] = 0] = "ASCII";
    Encoding[Encoding["BASE64"] = 1] = "BASE64";
})(Encoding || (exports.Encoding = Encoding = {}));
const generatePrivateKey = (initialNumber, z) => {
    const sequence = [];
    let element = initialNumber;
    let sum = initialNumber;
    for (let i = 0; i < z; i++) {
        sequence.push(element);
        element = sum.add((0, big_integer_1.default)(z));
        sum = sum.add(element);
    }
    return sequence;
};
exports.generatePrivateKey = generatePrivateKey;
const getPublicKeyParams = (privateKey) => {
    const sum = privateKey.reduce((prev, curr) => prev.plus(curr));
    const n = (0, big_integer_1.default)(sum).add(1n);
    const a = (0, mathUtils_1.generateCoprime)(n);
    return { a, n };
};
exports.getPublicKeyParams = getPublicKeyParams;
const generatePublicKey = (privateKey, a, n) => {
    const sequence = [];
    let d;
    let e;
    for (let i = 0; i < privateKey.length; i++) {
        d = privateKey[i];
        e = d.multiply(a).mod(n);
        sequence.push(e);
    }
    return sequence;
};
exports.generatePublicKey = generatePublicKey;
const encrypt = (publicKey, plaintext, encoding) => {
    const encryptedList = [];
    if (encoding === Encoding.BASE64) {
        plaintext = (0, base64_1.base64Encode)(plaintext);
    }
    plaintext.split('').forEach((b, index) => {
        let binaryString;
        if (encoding === Encoding.ASCII) {
            binaryString = plaintext.charCodeAt(index).toString(2).padStart(8, '0');
        }
        else {
            binaryString = (0, base64_1.convertBase64ToBinary)(plaintext[index]);
        }
        const positions = [];
        for (let i = 0; i < binaryString.length; i++) {
            if (binaryString[i] === '1') {
                positions.push(i);
            }
        }
        let sum = big_integer_1.default.zero;
        positions.forEach(position => {
            if (position < publicKey.length) {
                sum = sum.add(publicKey[position]);
            }
        });
        encryptedList.push(sum);
    });
    return encryptedList;
};
exports.encrypt = encrypt;
const decrypt = (privateKey, encryptedText, a, n) => {
    let decryptedBytes = [];
    let binaryResult = "";
    let inverse = (0, mathUtils_1.getInverseNumber)(a, n);
    for (let cipher of encryptedText) {
        let decryptedValue = cipher.times(inverse).mod(n);
        let binaryString = (0, exports.getDecryptedBinary)(decryptedValue, privateKey);
        binaryResult += binaryString;
        let decryptedByte = parseInt(binaryString, 2);
        decryptedBytes.push(decryptedByte);
    }
    return { decoded: new Uint8Array(decryptedBytes), binary: binaryResult };
};
exports.decrypt = decrypt;
const getDecryptedBinary = (number, privateKey) => {
    let binaryString = '';
    for (let i = privateKey.length - 1; i >= 0; i--) {
        if (number.greaterOrEquals(privateKey[i])) {
            binaryString += '1';
            number = number.minus(privateKey[i]);
        }
        else {
            binaryString += '0';
        }
    }
    return binaryString.split('').reverse().join('');
};
exports.getDecryptedBinary = getDecryptedBinary;
