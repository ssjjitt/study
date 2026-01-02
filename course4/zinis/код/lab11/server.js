const express = require('express');
const bodyParser = require('body-parser');
const { EllipticCurve, Point, ALPHABET_MAP, modInverse } = require('./ecc-math');

const app = express();
app.use(bodyParser.json());
app.use(express.static('public'));

// Инициализация кривой из задания: y^2 = x^3 - x + 1 mod 751
const curve = new EllipticCurve(-1, 1, 751);

// ЗАДАНИЕ 1: Поиск точек и операции
app.post('/api/task1/find-points', (req, res) => {
    const { xMin, xMax } = req.body;
    let points = [];
    for (let x = xMin; x <= xMax; x++) {
        const found = curve.findPointsForX(x);
        points = points.concat(found);
    }
    res.json({ points });
});

app.post('/api/task1/operations', (req, res) => {
    const { P, Q, R, k, l } = req.body;
    
    // Преобразуем входные данные в объекты Point
    const pObj = new Point(P.x, P.y);
    const qObj = new Point(Q.x, Q.y);
    const rObj = new Point(R.x, R.y);

    // a) kP
    const kP = curve.multiply(pObj, k);
    
    // b) P + Q
    const PplusQ = curve.add(pObj, qObj);
    
    // c) kP + lQ - R
    const lQ = curve.multiply(qObj, l);
    const sumPQ = curve.add(kP, lQ);
    const resC = curve.subtract(sumPQ, rObj);

    // d) P - Q + R
    const diffPQ = curve.subtract(pObj, qObj);
    const resD = curve.add(diffPQ, rObj);

    res.json({
        kP: kP,
        PplusQ: PplusQ,
        resC: resC,
        resD: resD
    });
});

// ЗАДАНИЕ 2: Шифрование (ElGamal)
app.post('/api/task2/encrypt', (req, res) => {
    const { text, d, k } = req.body; // d - приватный ключ получателя, k - случайное число
    
    const G = new Point(0, 1);
    // Вычисляем открытый ключ Q = dG
    const Q = curve.multiply(G, d);

    let encrypted = [];
    
    // Шифруем посимвольно
    for (let char of text.toUpperCase()) {
        const mapEntry = ALPHABET_MAP.find(e => e.char === char);
        if (mapEntry) {
            const Pm = new Point(mapEntry.p[0], mapEntry.p[1]);
            
            // C1 = kG
            const C1 = curve.multiply(G, k);
            // C2 = Pm + kQ
            const kQ = curve.multiply(Q, k);
            const C2 = curve.add(Pm, kQ);

            encrypted.push({ char, C1, C2 });
        }
    }

    res.json({ Q, encrypted });
});

app.post('/api/task2/decrypt', (req, res) => {
    const { encrypted, d } = req.body;
    let decrypted = "";

    for (let item of encrypted) {
        const C1 = new Point(item.C1.x, item.C1.y);
        const C2 = new Point(item.C2.x, item.C2.y);

        // Pm = C2 - dC1
        const dC1 = curve.multiply(C1, d);
        const Pm = curve.subtract(C2, dC1);

        // Поиск символа по точке
        const mapEntry = ALPHABET_MAP.find(e => 
            e.p[0] === Pm.x && e.p[1] === Pm.y
        );
        decrypted += mapEntry ? mapEntry.char : "?";
    }

    res.json({ decrypted });
});

// ЗАДАНИЕ 3: ЭЦП (ECDSA)
app.post('/api/task3/sign', (req, res) => {
    const { surname, d, k } = req.body;
    // Параметры из задания 3: G=(416, 55), q=13
    const G = new Point(416, 55);
    const q = 13;

    // Вычисляем Q = dG (для отображения)
    const Q = curve.multiply(G, d);

    // 1. Hash: первый символ фамилии -> x coord -> mod 13
    const firstChar = surname.toUpperCase()[0];
    const mapEntry = ALPHABET_MAP.find(e => e.char === firstChar);
    
    if (!mapEntry) return res.status(400).json({error: "Символ не найден"});

    const H_M = mapEntry.p[0] % 13; // Простейший хеш из задания

    // 2. Вычисляем точку kG = (x1, y1)
    const kG = curve.multiply(G, k);
    
    // 3. r = x1 mod q
    const r = kG.x % q;
    if (r === 0) return res.json({ error: "r = 0, выберите другое k" });

    // 4. s = k^-1 * (H(M) + d*r) mod q
    const k_inv = modInverse(k, q);
    const s = (k_inv * (H_M + d * r)) % q;
    if (s === 0) return res.json({ error: "s = 0, выберите другое k" });

    res.json({ 
        Q, 
        hash: H_M, 
        signature: { r, s },
        details: { kG_point: kG }
    });
});

app.post('/api/task3/verify', (req, res) => {
    const { surname, Q_point, r, s } = req.body;
    const G = new Point(416, 55);
    const q = 13;
    const Q = new Point(Q_point.x, Q_point.y);

    // 0. Проверка диапазона
    if (r < 1 || r >= q || s < 1 || s >= q) {
        return res.json({ valid: false, message: "Неверный диапазон r или s" });
    }

    // 1. Хеш
    const firstChar = surname.toUpperCase()[0];
    const mapEntry = ALPHABET_MAP.find(e => e.char === firstChar);
    const H_M = mapEntry.p[0] % 13;

    // 2. w = s^-1 mod q
    const w = modInverse(s, q);

    // 3. u1 = w * H(M) mod q, u2 = w * r mod q
    const u1 = (H_M * w) % q;
    const u2 = (r * w) % q;

    // 4. X = u1*G + u2*Q
    const u1G = curve.multiply(G, u1);
    const u2Q = curve.multiply(Q, u2);
    const X = curve.add(u1G, u2Q);

    if (X.isInfinity) return res.json({ valid: false, message: "Точка на бесконечности" });

    // 5. v = X.x mod q -> check v == r
    const v = X.x % q;

    res.json({
        valid: (v === r),
        calc: { w, u1, u2, X, v }
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});