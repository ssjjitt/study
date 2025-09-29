// === Импорт модулей ===
const crypto = require("crypto");

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}


// 01101111 01101011
function generateWord(length) {
  // return Array.from({ length: this.length }, () => Math.floor(Math.random() * 2));
  return [0, 1, 1, 0, 1, 1, 1, 1, // o
    0, 1, 1, 0, 1, 0, 1, 1]; // k
}

function reshapeToMatrix(word, rows, cols) {
  const matrix = [];
  let index = 0;
  for (let i = 0; i < rows; i++) {
    matrix[i] = [];
    for (let j = 0; j < cols; j++) {
      matrix[i][j] = word[index++];
    }
  }
  return matrix;
}

function flatten(matrix) {
  return matrix.reduce((acc, row) => acc.concat(row), []);
}

function sumMod2(arr) {
  return arr.reduce((a, b) => a ^ b, 0);
}

function calculateDiagonalParity(matrix, flip) {
  const data = flip ? matrix.map(row => [...row].reverse()) : matrix;
  const rows = data.length;
  const cols = data[0].length;
  const result = [];

  for (let offset = -(rows - 1); offset < cols; offset++) {
    let sum = 0;
    for (let i = 0; i < rows; i++) {
      let j = i + offset;
      if (j >= 0 && j < cols) {
        sum ^= data[i][j];
      }
    }
    result.push(sum);
  }

  return result;
}

function calculateParities(matrix, nParities) {
  const rows = matrix.length;
  const cols = matrix[0].length;
  const parities = {};

  if (nParities >= 2) {
    parities.row = matrix.map(row => sumMod2(row));
    parities.col = Array.from({ length: cols }, (_, j) => sumMod2(matrix.map(row => row[j])));
  }
  if (nParities >= 3) {
    parities.diag_down = calculateDiagonalParity(matrix, false);
  }
  if (nParities >= 4) {
    parities.diag_up = calculateDiagonalParity(matrix, true);
  }
  return parities;
}

function combineWordAndParities(word, parities) {
  let result = [...word];
  Object.values(parities).forEach(arr => result.push(...arr));
  return result;
}

function addErrors(word, numErrors) {
  const copy = [...word];
  const indices = new Set();
  while (indices.size < numErrors) {
    indices.add(getRandomInt(copy.length));
  }
  [...indices].forEach(i => (copy[i] ^= 1));
  return [copy, [...indices]];
}

function detectAndCorrect2D(matrix, expectedParities, nParities) {
  const actual = calculateParities(matrix, nParities);
  const wrongRows = actual.row.map((p, i) => p !== expectedParities.row[i] ? i : -1).filter(i => i !== -1);
  const wrongCols = actual.col.map((p, i) => p !== expectedParities.col[i] ? i : -1).filter(i => i !== -1);

  if (wrongRows.length === 1 && wrongCols.length === 1) {
    matrix[wrongRows[0]][wrongCols[0]] ^= 1;
    return { corrected: true, matrix };
  }

  return { corrected: false, matrix };
}

function analyzeCorrection(k, rows, cols, nParities, maxErrors, trials) {
  for (let numErrors = 1; numErrors <= maxErrors; numErrors++) {
    let total = 0, corrected = 0;
    console.log(`\nАнализ для ${numErrors} ошибок:`);

    for (let t = 0; t < trials; t++) {
      const word = generateWord(k);
      let wordStr = word.join(' ');
      console.log(`\n[${t + 1}] Исходное информационное слово:`, wordStr);

      const matrix = reshapeToMatrix(word, rows, cols);  
      console.log("Матрица:");
      matrix.forEach(row => console.log(row.join(' ')));

      const parities = calculateParities(matrix, nParities);
      console.log("Вычисленные паритеты:", parities);

      const code = combineWordAndParities(flatten(matrix), parities);
      console.log("Кодовое слово с паритетами Xn:", code);

      const [corrupted, errorIndices] = addErrors(code, numErrors);
      console.log("Слово с внесёнными ошибками Yn:", corrupted);
      console.log("Позиции ошибок:", errorIndices);

      const dataOnly = corrupted.slice(0, k);
      const corruptedMatrix = reshapeToMatrix(dataOnly, rows, cols);

      const result = detectAndCorrect2D(corruptedMatrix, parities, nParities);
      console.log("Исправленное слово Y'n:");
      corruptedMatrix.forEach(row => console.log(row.join(' ')));
      console.log("Результат исправления:", result.corrected ? "исправлено" : "не исправлено");

      total++;
      if (result.corrected) corrected++;
    }
    console.log(`Итог: ошибок: ${numErrors}, успешно исправлено: ${corrected}/${total}`);
  }
}

// === Запуск ===
const k = 16;
const rows = 4, cols = 4;
const nParities = 2;
const maxErrors = 1;
const trials = 3;

analyzeCorrection(k, rows, cols, nParities, maxErrors, trials);