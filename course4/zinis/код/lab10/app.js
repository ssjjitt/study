"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const rsa_1 = require("./rsa");
const elGamal_1 = require("./elGamal");
const schnorr_1 = require("./schnorr");
const path_1 = __importDefault(require("path"));
const app = (0, express_1.default)();
const PORT = 3000;
// Настройка приложения
app.set('view engine', 'ejs');
app.set('views', path_1.default.join(__dirname, 'views'));
app.use(express_1.default.static(path_1.default.join(__dirname, 'public')));
// Роутинг
app.get('/', (req, res) => {
    res.redirect('/rsa');
});
const processDigitalSignature = (algorithm, res, originalText, publicKey, digitalSign, signTime, verificationTime, verified) => {
    res.render('index', {
        algorithm,
        originalText,
        publicKey,
        digitalSign: Array.isArray(digitalSign) ? digitalSign.join(', ') : digitalSign,
        signTime: signTime.toFixed(3),
        verificationTime: verificationTime.toFixed(3),
        verified: verified ? 'да' : 'нет'
    });
};
app.get('/rsa', (req, res) => {
    const originalText = "Gluhova Daria Vitalievna";
    const rsa = new rsa_1.RSA();
    const publicKey = rsa.getPublicKey();
    let startTime = performance.now();
    const digitalSign = rsa.createDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;
    startTime = performance.now();
    const verified = rsa.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;
    processDigitalSignature('rsa', res, originalText, publicKey, digitalSign, signTime, verificationTime, verified);
});
app.get('/el-gamal', (req, res) => {
    const originalText = "Gluhova Daria Vitalievna";
    const elGamal = new elGamal_1.ElGamal();
    const publicKey = elGamal.getPublicKey();
    let startTime = performance.now();
    const digitalSign = elGamal.createDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;
    startTime = performance.now();
    const verified = elGamal.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;
    processDigitalSignature('el-gamal', res, originalText, publicKey, digitalSign, signTime, verificationTime, verified);
});
app.get('/schnorr', (req, res) => {
    const originalText = "Gluhova Daria Vitalievna";
    const schnorr = new schnorr_1.Schnorr();
    const publicKey = schnorr.getPublicKey();
    let startTime = performance.now();
    const digitalSign = schnorr.generateDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;
    startTime = performance.now();
    const verified = schnorr.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;
    processDigitalSignature('schnorr', res, originalText, publicKey, digitalSign, signTime, verificationTime, verified);
});
app.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}`);
});
