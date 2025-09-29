function searchErrorLong(masN, checkMatrix, k) {
    const r = hemmingLength(k);
    const n = r + k;

    for (let i = 0; i < k; i++) {
        const temp = new Array(n);
        for (let j = 0; j < n; j++) {
            temp[j] = masN[(n * i) + j];
        }
        searchError(temp, checkMatrix, k);

        for (let j = 0; j < n; j++) {
            masN[i * n + j] = temp[j];
        }
    }

    return masN;
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

function addCheckBits(masK, masN, checkMatrix) {
    const lenghtK = masK.length; //Должна быть равна 2^n
    const lenghtN = masN.length;
    const k = Math.sqrt(lenghtK);
    const r = hemmingLength(k);
    const n = k + r;

    for (let i = 0; i < k; i++) {
        const temp = new Array(n);
        for (let j = 0; j < k; j++) {
            temp[j] = masK[(k * i) + j];
        }
        sindrom(checkMatrix, temp, k);

        for (let j = 0; j < n; j++) {
            masN[i * n + j] = temp[j];
        }
    }
    return masN;
}

function alternation(masN, k) {
    const r = hemmingLength(k);
    const n = k + r;

    const matrix = [];
    for (let i = 0, m = 0; i < k; i++) {
        matrix.push([]);
        for (let j = 0; j < n; j++, m++) {
            matrix[i][j] = masN[m];
        }
    }

    for (let i = 0, m = 0; i < n; i++) {
        for (let j = 0; j < k; j++, m++) {
            masN[m] = matrix[j][i];
        }
    }

    return masN;
}

function reAlternation(masN, k) {
    const r = hemmingLength(k);
    const n = k + r;

    const matrix = [];
    for (let j = 0, m = 0; j < n; j++) {
        matrix.push([]);
        for (let i = 0; i < k; i++, m++) {
            matrix[j][i] = masN[m];
        }
    }

    for (let j = 0, m = 0; j < k; j++) {
        for (let i = 0; i < n; i++, m++) {
            masN[m] = matrix[i][j];
        }
    }

    return masN;
}

function generationRandMasMod2(mas) {
    for (let i = 0; i < mas.length; i++) {
        mas[i] = Math.floor(Math.random() * 2);
    }
    return mas;
}

function checkMatrixFunc(k) {
    const r = hemmingLength(k);
    const n = r + k;
    const rPow = Math.pow(2, r - 1);
    const combinations = new Array(rPow).fill(0).map(() => new Array(r).fill(0));

    for (let segmentLenght = 0; segmentLenght < r - 2; segmentLenght++) {
        if (segmentLenght * r > k) break;

        for (let i = 0; i < segmentLenght + 2; i++) {
            combinations[segmentLenght * r][i] = 1;
        }

        for (let segmentPositin = 1; segmentPositin < r; segmentPositin++) {
            for (let i = 0; i < r - 1; i++) {
                combinations[segmentLenght * r + segmentPositin][i + 1] = combinations[segmentLenght * r + segmentPositin - 1][i];
            }
            combinations[segmentLenght * r + segmentPositin][0] = combinations[segmentLenght * r + segmentPositin - 1][r - 1];
        }

        if (segmentLenght == r - 3) {
            for (let i = 0; i < r; i++) {
                combinations[rPow - 1][i] = 1;
            }
        }
    }
    const mas = new Array(n).fill(0).map(() => new Array(r).fill(0));
    for (let i = 0; i < k; i++) {
        for (let j = 0; j < r; j++) {
            mas[i][j] = combinations[i][j] || 0; // Добавляем проверку на наличие значения
        }
    }
    for (let i = 0; i < r; i++) {
        mas[i + k][i] = 1;
    }

    return mas;
}

function sindrom(checkMatrix, mas, k) {
    const r = hemmingLength(k);
    const n = r + k;
    const sindrom = new Array(r).fill(0);

    for (let i = 0, l = 0; i < r; i++, l = 0) {
        for (let j = 0; j < k; j++) {
            if (checkMatrix[j][i] == 1 && mas[j] == 1) l++;
            else sindrom[i] = 0;
        }
        if (l % 2 == 1) sindrom[i] = 1;
        else sindrom[i] = 0;
    }

    for (let i = 0; i < r; i++) {
        mas[i + k] = sindrom[i];
    }

    return mas;
}

function hemmingLength(k) {
    return Math.floor(Math.log2(k) + 1);
}

function searchError(mas, checkMatrix, k) {
    const r = hemmingLength(k);
    const n = r + k;

    const beforeSindrom = new Array(r);

    for (let i = k; i < n; i++) {
        beforeSindrom[i - k] = mas[i];
    }

    mas = sindrom(checkMatrix, mas, k);

    for (let i = k, j = 0; i < n; i++) {
        if (beforeSindrom[i - k] === mas[i]) {
            mas[i] = 0;
            j++;
            if (j === r) {
                for (let l = k; l < n; l++) {
                    mas[l] = beforeSindrom[l - k];
                }
                return mas;
            }
        } else {
            mas[i] = 1;
        }
    }

    for (let i = 0; i < n; i++) {
        let l = 0;
        for (let j = 0; j < r; j++) {
            if (checkMatrix[i][j] === mas[j + k]) l++;
        }
        if (l === r) {
            mas[i] = (mas[i] + 1) % 2;
        }
    }

    mas = sindrom(checkMatrix, mas, k);

    return mas;
}

function outMas(mas) {
    mas = mas.join(' ');
    console.log(mas);
}

function outTable(mas) {
    let rows = [];
    for (let i = 0; i < mas.length; i += 7) {
        rows.push(mas.slice(i, i + 7));
    }

    rows.forEach(row => {
        console.log(row.join(''));
    });
}

function outTable2(mas) {
    let rows = [];
    for (let i = 0; i < mas.length; i += 7) {
        rows.push(mas.slice(i, i + 4));
    }

    rows.forEach(row => {
        console.log(row.join(''));
    });
}

function outMatrix(matrix, k, n) {
    console.log("outMatrix");
    for (let i = 0; i < k; i++) {
        let row = "";
        for (let j = 0; j < n; j++) {
            row += matrix[i][j];
        }
        console.log(row);
    }
}

function outMatrixInv(matrix, k, n) {
    for (let j = 0; j < n; j++) {
        let row = "";
        for (let i = 0; i < k; i++) {
            row += matrix[i][j];
        }
        console.log(row);
    }
}

function addToOutput(text) {
    console.log(text);
}


function main() {
    const lenghtK = 16; //Должна быть равна 2^n
    const k = Math.sqrt(lenghtK);
    const r = hemmingLength(k);
    const n = k + r;
    const lenghtN = lenghtK + (r * k);

    const masK = [1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0];
    const masK2 = new Array(lenghtK); //сюда запишеться итоговая строка после всех манипуляций 
    const masN = new Array(lenghtK + (r * k));
    let checkMatrix = new Array(n).fill(0).map(() => new Array(r));

    let error;
    let errorLength;

    // generationRandMasMod2(masK);
    addToOutput("Входная строка: ");
    console.log("k = ", k);
    console.log("r = ", r);
    console.log("n = ", n);
    addToOutput("Входная строка: ");

    outMas(masK);

    addToOutput("Проверочная матрица: ");
    checkMatrix = checkMatrixFunc(k);
    outMatrixInv(checkMatrix, n, r);

    addCheckBits(masK, masN, checkMatrix);
    addToOutput("Строка с доб. проверочными битами: ");
    outMas(masN);

    addToOutput("Таблица перемежения: ");
    outTable(masN);

    alternation(masN, k);
    addToOutput("Строка после перемежения: ");
    outMas(masN);

    error = 2; // место ошибки
    errorLength = 5; // длина ошибки
    for (let i = error; i < (error + errorLength); i++) {
        masN[i] = (masN[i] + 1) % 2;
    }

    addToOutput("Строка с ошибками: ");
    outMas(masN);

    reAlternation(masN, k);
    addToOutput("Строка после деперемежения: ");
    outTable(masN);

    addToOutput("Строка после деперемежения по строкам: ");
    outMas(masN);

    searchErrorLong(masN, checkMatrix, k);
    addToOutput("Строка после исправления ошибок: ");
    outMas(masN);

    removeCheckBits(masK2, masN, checkMatrix);
    addToOutput("Строка после удаления проверочных бит: ");
    outMas(masK2);
    addToOutput("");

    addToOutput("Исходная строка: "); outMas(masK);
}


main();