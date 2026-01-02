"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const asymmetric_1 = require("./asymmetric");
const big_integer_1 = __importDefault(require("big-integer"));
const mathUtils_1 = require("./mathUtils");
const base64_1 = require("./base64");
const app = (0, express_1.default)();
app.use(express_1.default.json());
app.use(express_1.default.urlencoded({ extended: false }));
app.set('view engine', 'ejs');
app.get('/', (req, res) => {
    res.redirect('/ascii');
});
app.get("/ascii", (req, res) => {
    const originalText = 'Gluhova Daria Vitalievna';
    const firstSequenceElement = (0, mathUtils_1.generateRandomNumber)(100);
    const privateKeyASCII = (0, asymmetric_1.generatePrivateKey)((0, big_integer_1.default)(firstSequenceElement), 8);
    const { a, n } = (0, asymmetric_1.getPublicKeyParams)(privateKeyASCII);
    const publicKey = (0, asymmetric_1.generatePublicKey)(privateKeyASCII, a, n);
    let startTime = performance.now();
    const encrypted = (0, asymmetric_1.encrypt)(publicKey, originalText, asymmetric_1.Encoding.ASCII);
    let endTime = performance.now();
    const encodingTime = (endTime - startTime).toFixed(4);
    startTime = performance.now();
    const decrypted = (0, asymmetric_1.decrypt)(privateKeyASCII, encrypted, a, n);
    endTime = performance.now();
    const decodingTime = (endTime - startTime).toFixed(4);
    const decoder = new TextDecoder('utf-8');
    const decodedString = decoder.decode(decrypted.decoded);
    res.render('asymmetric-ascii', {
        originalText: originalText,
        privateKey: privateKeyASCII.join(', '),
        n: n,
        a: a,
        publicKey: publicKey.join(', '),
        encrypted: encrypted.join(', '),
        decrypted: decodedString,
        encodingTime: encodingTime,
        decodingTime: decodingTime
    });
});
app.get("/base64", (req, res) => {
    const originalText = 'Bigmouth Strikes Again';
    const originalBase64 = (0, base64_1.base64Encode)(originalText);
    const firstSequenceElement = (0, mathUtils_1.generateRandomNumber)(100);
    const privateKeyBase64 = (0, asymmetric_1.generatePrivateKey)((0, big_integer_1.default)(firstSequenceElement), 6);
    const { a, n } = (0, asymmetric_1.getPublicKeyParams)(privateKeyBase64);
    const publicKey = (0, asymmetric_1.generatePublicKey)(privateKeyBase64, a, n);
    let startTime = performance.now();
    const encrypted = (0, asymmetric_1.encrypt)(publicKey, originalText, asymmetric_1.Encoding.BASE64);
    let endTime = performance.now();
    const encodingTime = (endTime - startTime).toFixed(4);
    startTime = performance.now();
    const decrypted = (0, asymmetric_1.decrypt)(privateKeyBase64, encrypted, a, n);
    endTime = performance.now();
    const decodingTime = (endTime - startTime).toFixed(4);
    const decodedString = (0, base64_1.convertBinaryToBase64String)(decrypted.binary);
    res.render('asymmetric-base64', {
        originalText: originalBase64,
        privateKey: privateKeyBase64.join(', '),
        n: n,
        a: a,
        publicKey: publicKey.join(', '),
        encrypted: encrypted.join(', '),
        decrypted: decodedString,
        encodingTime: encodingTime,
        decodingTime: decodingTime
    });
});
app.listen(3000, () => console.log(`Server is running at http://localhost:3000`));
