// === Импорт модулей ===
const crypto = require("crypto");

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}

// Генерация 16-битного информационного слова
function generateWord(length) {
    // return Array.from({ length }, () => Math.floor(Math.random() * 2));
    return [0, 1, 1, 0, 1, 1, 1, 1, // o
    0, 1, 1, 0, 1, 0, 1, 1]; // k
}

// Преобразование информационного слова в 3D матрицу
function reshapeTo3DMatrix(word, rows, cols, depth) {
    const matrix = [];
    let index = 0;
    for (let z = 0; z < depth; z++) {
        matrix[z] = [];
        for (let i = 0; i < rows; i++) {
            matrix[z][i] = [];
            for (let j = 0; j < cols; j++) {
                matrix[z][i][j] = word[index++];
            }
        }
    }
    return matrix;
}

// Преобразование 3D матрицы обратно в одномерный массив
function flatten3D(matrix) {
    return matrix.reduce((acc, plane) => acc.concat(plane.reduce((rowAcc, row) => rowAcc.concat(row), [])), []);
}

// Печать 3D матрицы в наглядном виде
function print3DMatrix(matrix) {
    matrix.forEach((plane, z) => {
        console.log(`Глубина ${z + 1}:`);
        plane.forEach(row => console.log(row.join(' ')));
        console.log(''); // Пустая строка для разделения слоев
    });
}

// Подсчет суммы по модулю 2
function sumMod2(arr) {
    return arr.reduce((a, b) => a ^ b, 0);
}

// Вычисление паритетов по диагоналям в 3D матрице
function calculateDiagonalParity3D(matrix, flip) {
    const data = flip ? matrix.map(plane => plane.map(row => [...row].reverse())) : matrix;
    const depth = data.length;
    const rows = data[0].length;
    const cols = data[0][0].length;
    const result = [];

    // Диагонали на плоскостях X-Y, X-Z и Y-Z
    for (let z = 0; z < depth; z++) {
        for (let offset = -(rows - 1); offset < cols; offset++) {
            let sum = 0;
            for (let i = 0; i < rows; i++) {
                let j = i + offset;
                if (j >= 0 && j < cols) {
                    sum ^= data[z][i][j];
                }
            }
            result.push(sum);
        }
    }

    return result;
}

// Вычисление всех паритетов для 3D матрицы
function calculateParities3D(matrix, nParities) {
    const depth = matrix.length;
    const rows = matrix[0].length;
    const cols = matrix[0][0].length;
    const parities = {};

    if (nParities >= 2) {
        // Паритеты по строкам и столбцам
        parities.row = matrix.map(plane => plane.map(row => sumMod2(row)));
        parities.col = Array.from({ length: cols }, (_, j) => sumMod2(matrix.map(plane => plane.map(row => row[j]))));
    }
    if (nParities >= 3) {
        // Паритеты по диагоналям X-Y
        parities.diag_down = calculateDiagonalParity3D(matrix, false);
    }
    if (nParities >= 4) {
        // Паритеты по диагоналям X-Z и Y-Z
        parities.diag_up = calculateDiagonalParity3D(matrix, true);
    }

    return parities;
}

// Объединение информационного слова с паритетами
function combineWordAndParities(word, parities) {
    const combined = [...word];

    function extractElements(item) {
        if (typeof item === 'number') {
            combined.push(item);
        } else if (Array.isArray(item)) {
            item.forEach(extractElements);
        } else if (typeof item === 'object' && item !== null) {
            for (const key in item) {
                extractElements(item[key]);
            }
        }
    }

    extractElements(parities);

    return combined;
}

// Внесение ошибок в кодовое слово
function addErrors(word, numErrors) {
    const copy = [...word];
    const indices = new Set();
    while (indices.size < numErrors) {
        indices.add(getRandomInt(copy.length));
    }
    [...indices].forEach(i => (copy[i] ^= 1));
    return [copy, [...indices]];
}

// Детекция и коррекция ошибок для 3D матрицы
function detectAndCorrect3D(matrix, expectedParities, nParities) {
    const actual = calculateParities3D(matrix, nParities);
    const wrongRows = actual.row.map((p, i) => p !== expectedParities.row[i] ? i : -1).filter(i => i !== -1);
    const wrongCols = actual.col.map((p, i) => p !== expectedParities.col[i] ? i : -1).filter(i => i !== -1);

    if (wrongRows.length === 1 && wrongCols.length === 1) {
        matrix[wrongRows[0]][wrongCols[0]] ^= 1;
        return { corrected: true, matrix };
    }

    return { corrected: false, matrix };
}

// Основная функция
function analyzeCorrection3D(k, rows, cols, depth, nParities, maxErrors, trials) {
    for (let numErrors = 1; numErrors <= maxErrors; numErrors++) {
        let total = 0, corrected = 0;
        console.log(`\nАнализ для ${numErrors} ошибок:`);

        for (let t = 0; t < trials; t++) {
            // Генерация случайного информационного слова длиной k
            const word = generateWord(k);
            console.log(`\n[${t + 1}] Исходное информационное слово:`, word.join(' '));

            // Преобразование в 3D матрицу
            const matrix = reshapeTo3DMatrix(word, rows, cols, depth);

            // Печать 3D матрицы
            print3DMatrix(matrix);

            // Вычисление паритетов
            const parities = calculateParities3D(matrix, nParities);
            console.log("Вычисленные паритеты:", parities);

            // Объединение информационного слова с паритетами
            const code = combineWordAndParities(flatten3D(matrix), parities);

            console.log("                                0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5\n");
            console.log("Кодовое слово с паритетами Xn: ", code.join(' '));

            // Внесение ошибок
            const [corrupted, errorIndices] = addErrors(code, numErrors);
            console.log("Слово с внесёнными ошибками Yn:", corrupted.join(' '));
            console.log("Позиции ошибок:", errorIndices);

            // Восстановление и детекция ошибок
            const dataOnly = corrupted.slice(0, k);
            const corruptedMatrix = reshapeTo3DMatrix(dataOnly, rows, cols, depth);

            const result = detectAndCorrect3D(corruptedMatrix, parities, nParities);
            const correctedWord = flatten3D(result.matrix);
            const correctedCode = combineWordAndParities(correctedWord, calculateParities3D(result.matrix, nParities));
            console.log("Исправленное кодовое слово Y'n:", correctedCode.join(' '));
            
            const isActuallyCorrected = correctedCode.every((val, index) => val === code[index]);
            console.log("Результат исправления:", isActuallyCorrected ? "исправлено" : "не исправлено");

            total++;
            if (correctedCode.every((val, index) => val === code[index])) {
              corrected++;
          }
        }
        console.log(`Итог: ошибок: ${numErrors}, успешно исправлено: ${corrected}/${total}`);
    }
}

// === Запуск ===
const k = 16; // Длина информационного слова
const rows = 2, cols = 4, depth = 2; // Размер 3D матрицы
const nParities = 4; // Количество паритетов
const maxErrors = 1; // Максимальное количество ошибок
const trials = 3; // Количество испытаний

analyzeCorrection3D(k, rows, cols, depth, nParities, maxErrors, trials);