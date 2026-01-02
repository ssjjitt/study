const makeGenMatrix = (gStr, k, n) => {
    const g = gStr.split('').map(Number);
    const matrix = Array.from({ length: k }, () => Array(n).fill(0));
    g.forEach((bit, i) => matrix[0][i] = bit);
    for (let i = 1; i < k; i++) {
        matrix[i] = [matrix[i - 1][n - 1], ...matrix[i - 1].slice(0, n - 1)];
    }
    return matrix;
};

const showMatrix = (matrix, rows, cols) => {
    for (let i = 0; i < rows; i++) {
        console.log(' ' + matrix[i].slice(0, cols).join(' '));
    }
};

const polyDiv = (a, b) => {
    let r = [...a];
    const q = [];

    while (r.length >= b.length) {
        q.push(r[0]);
        if (r[0] === 1) {
            for (let i = 0; i < b.length; i++) {
                r[i] ^= b[i];
            }
        }
        r.shift();
    }

    return [q, r];
};

const makeCanonicalG = (k, n, gStr) => {
    const g = gStr.split('').map(Number);
    const G = Array.from({ length: k }, (_, i) =>
        Array.from({ length: n }, (_, j) => (i === j ? 1 : 0))
    );

    for (let i = 0; i < k; i++) {
        const [, remainder] = polyDiv(G[i], g);
        const remStart = n - remainder.length;
        for (let j = 0; j < remainder.length; j++) {
            G[i][remStart + j] ^= remainder[j];
        }
    }

    return G;
};

const makeCheckMatrix = (G, k, n) => {
    const r = n - k;
    return Array.from({ length: r }, (_, i) => [
        ...Array.from({ length: k }, (_, j) => G[j][k + i]),
        ...Array.from({ length: r }, (_, j) => (i === j ? 1 : 0))
    ]);
};

const xorDivide = (dividend, divisor) => {
    let a = dividend.toString(2).split('').map(Number);
    let b = divisor.toString(2).split('').map(Number);

    while (a.length >= b.length) {
        if (a[0] === 1) {
            for (let i = 0; i < b.length; i++) {
                a[i] ^= b[i];
            }
        }
        a.shift();
    }

    return [0, parseInt(a.join('') || '0', 2)];
};

const encode = (message, g, k, n) => {
    const padded = message + '0'.repeat(n - k);
    console.log('\nx_k*x^r =', padded);

    const [, remainder] = xorDivide(parseInt(padded, 2), parseInt(g, 2));
    const remBin = remainder.toString(2).padStart(n - k, '0');
    console.log('x_k*x^r XOR g(x) =', remBin);

    return message + remBin;
};

const addRandomErrors = (str, errors = 1) => {
    const bits = str.split('').map(Number);
    while (errors--) {
        const pos = Math.floor(Math.random() * bits.length);
        bits[pos] ^= 1;
    }
    return bits.join('');
};

const getSyndrome = (received, g) => {
    const [, rem] = xorDivide(parseInt(received, 2), parseInt(g, 2));
    return rem.toString(2).padStart(4, '0');
};

const findErrorPosition = (syndrome, H, n) => {
    for (let i = 0; i < n; i++) {
        const col = H.map(row => row[i]).join('');
        if (col === syndrome) {
            return Array.from({ length: n }, (_, j) => (j === i ? 1 : 0)).join('');
        }
    }
    return '0'.repeat(n);
};

const xorStr = (a, b) => {
    const maxLen = Math.max(a.length, b.length);
    const aBits = a.padStart(maxLen, '0');
    const bBits = b.padStart(maxLen, '0');
    return [...aBits].map((bit, i) => bit ^ bBits[i]).join('');
};

module.exports = {
    makeGenMatrix, showMatrix, makeCanonicalG,
    makeCheckMatrix, encode, addRandomErrors,
    getSyndrome, findErrorPosition, xorStr
};