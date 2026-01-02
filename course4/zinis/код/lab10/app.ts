import express, {Request, Response} from 'express';
import {RSA} from "./rsa";
import {ElGamal} from "./elGamal";
import {Schnorr} from "./schnorr";
import path from 'path';

const app = express();
const PORT = 3000;

app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));
app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    res.redirect('/rsa');
});

const processDigitalSignature = (algorithm: string, res: Response, originalText: string, 
                               publicKey: any, digitalSign: any, signTime: number, 
                               verificationTime: number, verified: boolean) => {
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

app.get('/rsa', (req: Request, res: Response) => {
    const originalText = "Gluhova Daria Vitalievna";
    const rsa = new RSA();
    const publicKey = rsa.getPublicKey();

    let startTime = performance.now();
    const digitalSign = rsa.createDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;

    startTime = performance.now();
    const verified = rsa.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;

    processDigitalSignature('rsa', res, originalText, publicKey, 
                          digitalSign, signTime, verificationTime, verified);
});

app.get('/el-gamal', (req: Request, res: Response) => {
    const originalText = "Gluhova Daria Vitalievna";
    const elGamal = new ElGamal();
    const publicKey = elGamal.getPublicKey();

    let startTime = performance.now();
    const digitalSign = elGamal.createDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;

    startTime = performance.now();
    const verified = elGamal.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;

    processDigitalSignature('el-gamal', res, originalText, publicKey, 
                          digitalSign, signTime, verificationTime, verified);
});

app.get('/schnorr', (req: Request, res: Response) => {
    const originalText = "Gluhova Daria Vitalievna";
    const schnorr = new Schnorr();
    const publicKey = schnorr.getPublicKey();

    let startTime = performance.now();
    const digitalSign = schnorr.generateDigitalSignature(originalText);
    let endTime = performance.now();
    const signTime = endTime - startTime;

    startTime = performance.now();
    const verified = schnorr.verifyDigitalSignature(originalText, digitalSign);
    endTime = performance.now();
    const verificationTime = endTime - startTime;

    processDigitalSignature('schnorr', res, originalText, publicKey, 
                          digitalSign, signTime, verificationTime, verified);
});

app.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}`);
});