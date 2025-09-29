const { randomInt } = require('crypto');

function hemmingLength(k) {
    return Math.floor(Math.log2(k) + 1.99);
}

function generateRandomBits(length) {
    return Array.from({ length }, () => randomInt(2));
}

function createCheckMatrix(k) {
    const r = hemmingLength(k);
    const n = k + r;
    const rPow = 2 ** (r - 1);
    const combinations = Array.from({ length: rPow }, () => Array(r).fill(0));

    for (let segmentLength = 0; segmentLength < r - 2; segmentLength++) {
        if (segmentLength * r > k) break;
        for (let i = 0; i < segmentLength + 2; i++) combinations[segmentLength * r][i] = 1;
        for (let segmentPos = 1; segmentPos < r; segmentPos++) {
            for (let i = 0; i < r - 1; i++) {
                combinations[segmentLength * r + segmentPos][i + 1] = combinations[segmentLength * r + segmentPos - 1][i];
            }
            combinations[segmentLength * r + segmentPos][0] = combinations[segmentLength * r + segmentPos - 1][r - 1];
        }
        if (segmentLength === r - 3) combinations[rPow - 1].fill(1);
    }

    const matrix = Array.from({ length: k + r }, () => Array(r).fill(0));
    for (let i = 0; i < k; i++) {
        for (let j = 0; j < r; j++) {
            matrix[i][j] = combinations[i]?.[j] ?? 0;
        }
    }
    for (let i = 0; i < r; i++) matrix[i + k][i] = 1;

    return matrix;
}

function addCheckBits(data, k, checkMatrix) {
    const r = hemmingLength(k);
    const n = k + r;
    const encoded = [];

    for (let i = 0; i < k; i++) {
        const word = data.slice(i * k, (i + 1) * k);
        const checkBits = Array(r).fill(0);

        for (let j = 0; j < r; j++) {
            checkBits[j] = word.reduce((sum, bit, idx) =>
                sum ^ (bit & checkMatrix[idx][j]), 0);
        }

        encoded.push(...word, ...checkBits);
    }
    return encoded;
}

function interleave(data, k) {
    const r = hemmingLength(k);
    const n = k + r;
    const matrix = Array.from({ length: k }, (_, i) =>
        data.slice(i * n, (i + 1) * n)
    );

    const result = [];
    for (let col = 0; col < n; col++) {
        for (let row = 0; row < k; row++) {
            result.push(matrix[row][col]);
        }
    }
    return result;
}

function deinterleave(data, k) {
    const r = hemmingLength(k);
    const n = k + r;
    const matrix = Array.from({ length: n }, (_, i) =>
        data.slice(i * k, (i + 1) * k)
    );

    const result = [];
    for (let row = 0; row < k; row++) {
        for (let col = 0; col < n; col++) {
            result.push(matrix[col][row]);
        }
    }
    return result;
}

function introduceErrors(data, errorLength) {
    const start = randomInt(data.length - errorLength);
    for (let i = start; i < start + errorLength; i++) {
        data[i] ^= 1;
    }
    return { data, start };
}

function correctErrors(data, k, checkMatrix) {
    const r = hemmingLength(k);
    const n = k + r;
    const corrected = [];

    for (let i = 0; i < k; i++) {
        const word = data.slice(i * n, (i + 1) * n);
        const syndrome = Array(r).fill(0);

        for (let j = 0; j < r; j++) {
            syndrome[j] = word.reduce((sum, bit, idx) =>
                sum ^ (bit & checkMatrix[idx][j]), 0);
        }

        const errorIndex = parseInt(syndrome.reverse().join(''), 2);
        if (errorIndex > 0 && errorIndex <= n) {
            word[errorIndex - 1] ^= 1; // исправление бита
        }

        corrected.push(...word.slice(0, k));
    }

    return corrected;
}

function compareBits(original, recovered) {
    let correct = 0;
    for (let i = 0; i < original.length; i++) {
        if (original[i] === recovered[i]) correct++;
    }
    return correct / original.length;
}

function matrixToString(matrix, rows, cols) {
    let str = '';
    for (let i = 0; i < rows; i++) {
        str += matrix[i].slice(0, cols).join('') + '\n';
    }
    return str;
}

function removeCheckBits(masK, masN, checkMatrix) {
    const lenghtK = masK.length; //Должна быть равна 2^n
    const lenghtN = masN.length;
    const k = Math.sqrt(lenghtK);
    const r = hemmingLength(k);
    const n = k + r;

    for (let i = 0; i < k; i++) {
        const temp = new Array(n);
        for (let j = 0; j < n; j++) {
            temp[j] = masN[(n * i) + j];
        }

        for (let j = 0; j < k; j++) {
            masK[i * k + j] = temp[j];
        }
    }
    return masK;
}

module.exports = {
    hemmingLength,
    generateRandomBits,
    createCheckMatrix,
    addCheckBits,
    interleave,
    deinterleave,
    introduceErrors,
    correctErrors,
    compareBits,
    matrixToString,
    removeCheckBits
};
