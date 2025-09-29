const fs = require('fs');

// Чтение бинарного сообщения из файла
function readBinaryMessage(filename) {
    return fs.readFileSync(filename, 'utf-8').trim();
}

// Подсчет количества проверочных битов
function calculateRedundantBits(k) {
    let r = 0;
    while (Math.pow(2, r) < k + r + 1) {
        r++;
    }
    return r;
}

// Генерация матрицы Хемминга H
function generateHMatrix(r, n) {
    const H = Array.from({ length: r }, () => Array(n).fill(0));
    for (let col = 0; col < n; col++) {
        let val = col + 1;
        for (let row = 0; row < r; row++) {
            H[row][col] = (val >> row) & 1;
        }
    }
    return H;
}

// Кодирование Хемминга
function encodeHamming(data) {
    const k = data.length;
    const r = calculateRedundantBits(k);
    const n = k + r;
    const code = Array(n).fill(0);

    let j = 0;
    for (let i = 0; i < n; i++) {
        if ((i & (i + 1)) === 0) continue; // Степени двойки
        code[i] = parseInt(data[j++]);
    }

    for (let i = 0; i < r; i++) {
        const pos = (1 << i) - 1;
        let parity = 0;
        for (let j = 0; j < n; j++) {
            if ((j + 1) & (1 << i)) {
                parity ^= code[j];
            }
        }
        code[pos] = parity;
    }

    return code;
}

// Внесение случайных ошибок
function introduceErrors(encoded, numErrors) {
    const n = encoded.length;
    const positions = new Set();
    const result = [...encoded];

    while (positions.size < numErrors) {
        const pos = Math.floor(Math.random() * n);
        if (!positions.has(pos)) {
            result[pos] ^= 1;
            positions.add(pos);
        }
    }

    console.log('\nОшибки в позициях (с 1):', [...positions].map(p => p + 1).join(' '));
    return result;
}

// Синдром
function calculateSyndrome(received, H) {
    const r = H.length;
    const n = H[0].length;
    const S = Array(r).fill(0);
    for (let i = 0; i < r; i++) {
        for (let j = 0; j < n; j++) {
            S[i] ^= (H[i][j] & received[j]);
        }
    }
    return S;
}

// Синдром -> позиция ошибки
function syndromeToIndex(S) {
    let pos = 0;
    for (let i = 0; i < S.length; i++) {
        pos |= (S[i] << i);
    }
    return pos - 1;
}

// Исправление ошибки
function correctError(received, H) {
    const S = calculateSyndrome(received, H);
    const errorPos = syndromeToIndex(S);
    if (errorPos >= 0 && errorPos < received.length) {
        received[errorPos] ^= 1;
        console.log('Ошибка исправлена в позиции:', errorPos + 1);
    } else {
        console.log('Синдром нулевой — ошибок нет или слишком много для исправления.');
    }
    return received;
}

// Печать
function printVector(label, vec) {
    console.log(label + vec.join(''));
}

function printMatrix(label, matrix) {
    console.log(`\n${label}`);

    const rows = matrix.length;
    const cols = matrix[0].length;

    const header = ['   |'];
    for (let j = 0; j < cols; j++) {
        header.push(String(j + 1).padStart(2, ' '));
    }
    console.log(header.join(' '));
    console.log('-'.repeat(header.join(' ').length));

    // Строки матрицы с индексами строк
    for (let i = 0; i < rows; i++) {
        const row = [` h${i + 1}|`];
        for (let j = 0; j < cols; j++) {
            row.push(` ${matrix[i][j]}`);
        }
        console.log(row.join(' '));
    }
}

// === MAIN ===
function main() {
    const binary = readBinaryMessage('msg.txt');
    const k = binary.length;
    const r = calculateRedundantBits(k);
    const n = k + r;

    console.log(`k = ${k}, r = ${r}, n = ${n}`);

    const Xn = encodeHamming(binary);
    const H = generateHMatrix(r, n);

    printVector('Xn (исходное кодовое слово): ', Xn);
    printMatrix('Матрица Хэмминга H:', H);

    for (let errors = 0; errors <= 2; errors++) {
        console.log(`\n--- Случай с ${errors} ошибками ---`);
        const Yn = introduceErrors(Xn, errors);
        const S = calculateSyndrome(Yn, H);
        printVector('Синдром S: ', S);
        const corrected = correctError([...Yn], H);
        printVector('Yn (принятое): ', Yn);
        printVector('Исправленное: ', corrected);
    }
}

main();
