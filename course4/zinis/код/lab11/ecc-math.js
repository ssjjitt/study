// ecc-math.js

// Модульная арифметика
const mod = (n, m) => ((n % m) + m) % m;

// Расширенный алгоритм Евклида для поиска обратного элемента
const modInverse = (a, m) => {
    let [m0, x, y] = [m, 1, 0];
    if (m === 1) return 0;
    while (a > 1) {
        const q = Math.floor(a / m);
        [a, m] = [m, a % m];
        [x, y] = [y, x - q * y];
    }
    return x < 0 ? x + m0 : x;
};

class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.isInfinity = (x === null && y === null);
    }

    static Infinity() {
        return new Point(null, null);
    }

    // Проверка на равенство
    equals(other) {
        if (this.isInfinity && other.isInfinity) return true;
        if (this.isInfinity || other.isInfinity) return false;
        return this.x === other.x && this.y === other.y;
    }

    toString() {
        return this.isInfinity ? "O" : `(${this.x}, ${this.y})`;
    }
}

class EllipticCurve {
    constructor(a, b, p) {
        this.a = BigInt(a);
        this.b = BigInt(b);
        this.p = BigInt(p);
    }

    // Проверка принадлежности точки кривой
    isOnCurve(point) {
        if (point.isInfinity) return true;
        const { x, y } = point;
        const left = (BigInt(y) ** 2n) % this.p;
        const right = mod(BigInt(x) ** 3n + this.a * BigInt(x) + this.b, this.p);
        return left === right;
    }

    // Сложение точек P + Q
    add(P, Q) {
        if (P.isInfinity) return Q;
        if (Q.isInfinity) return P;

        const p_val = this.p;
        
        // P + (-P) = O
        if (P.x === Q.x && mod(BigInt(P.y), p_val) === mod(-BigInt(Q.y), p_val)) {
            return Point.Infinity();
        }

        let lambda;
        const bigPx = BigInt(P.x);
        const bigPy = BigInt(P.y);
        const bigQx = BigInt(Q.x);
        const bigQy = BigInt(Q.y);

        if (P.equals(Q)) {
            // Удвоение: lambda = (3x^2 + a) / 2y
            const num = mod(3n * bigPx ** 2n + this.a, p_val);
            const den = modInverse(Number(mod(2n * bigPy, p_val)), Number(p_val));
            lambda = mod(num * BigInt(den), p_val);
        } else {
            // Сложение: lambda = (y2 - y1) / (x2 - x1)
            const num = mod(bigQy - bigPy, p_val);
            const den = modInverse(Number(mod(bigQx - bigPx, p_val)), Number(p_val));
            lambda = mod(num * BigInt(den), p_val);
        }

        const x3 = mod(lambda ** 2n - bigPx - bigQx, p_val);
        const y3 = mod(lambda * (bigPx - x3) - bigPy, p_val);

        return new Point(Number(x3), Number(y3));
    }

    // Вычитание P - Q = P + (-Q)
    subtract(P, Q) {
        if (Q.isInfinity) return P;
        const negQ = new Point(Q.x, Number(mod(-BigInt(Q.y), this.p)));
        return this.add(P, negQ);
    }

    // Скалярное умножение k * P (Double-and-Add)
    multiply(P, k) {
        if (k === 0) return Point.Infinity();
        let target = P;
        let scalar = BigInt(k);
        let result = Point.Infinity();

        while (scalar > 0n) {
            if (scalar & 1n) {
                result = this.add(result, target);
            }
            target = this.add(target, target);
            scalar >>= 1n;
        }
        return result;
    }

    // Поиск всех точек для заданного X (для Задания 1)
    findPointsForX(xVal) {
        const bigX = BigInt(xVal);
        const rhs = mod(bigX ** 3n + this.a * bigX + this.b, this.p);
        
        // Решаем y^2 = rhs mod p перебором (для малых p) или алгоритмом Тонелли-Шенкса
        // Для p=751 проще перебор
        const points = [];
        for (let y = 0n; y < this.p; y++) {
            if ((y * y) % this.p === rhs) {
                points.push(new Point(xVal, Number(y)));
            }
        }
        return points;
    }
}

// Данные из методички
const ALPHABET_MAP = [
    { char: 'А', p: [189, 297] }, { char: 'Б', p: [189, 454] }, { char: 'В', p: [192, 32] },
    { char: 'Г', p: [192, 719] }, { char: 'Д', p: [194, 205] }, { char: 'Е', p: [194, 546] },
    { char: 'Ж', p: [197, 145] }, { char: 'З', p: [197, 606] }, { char: 'И', p: [198, 224] },
    { char: 'Й', p: [198, 527] }, { char: 'К', p: [200, 30] }, { char: 'Л', p: [200, 721] },
    { char: 'М', p: [203, 324] }, { char: 'Н', p: [203, 427] }, { char: 'О', p: [205, 372] },
    { char: 'П', p: [205, 379] }, { char: 'Р', p: [206, 106] }, { char: 'С', p: [206, 645] },
    { char: 'Т', p: [209, 82] }, { char: 'У', p: [209, 669] }, { char: 'Ф', p: [210, 31] },
    { char: 'Х', p: [210, 720] }, { char: 'Ц', p: [215, 247] }, { char: 'Ч', p: [215, 504] },
    { char: 'Ш', p: [218, 150] }, { char: 'Щ', p: [218, 601] }, { char: 'Ъ', p: [221, 138] },
    { char: 'Ы', p: [221, 613] }, { char: 'Ь', p: [226, 9] }, { char: 'Э', p: [226, 742] },
    { char: 'Ю', p: [227, 299] }, { char: 'Я', p: [227, 452] }
];

module.exports = { EllipticCurve, Point, ALPHABET_MAP, modInverse };