function generateRandomErrors(mas, errorLength) {
    const errorIndices = new Set();
    const n = mas.length;

    // Генерация случайных индексов для ошибок
    while (errorIndices.size < errorLength) {
        const randomIndex = Math.floor(Math.random() * n);
        errorIndices.add(randomIndex);
    }

    // Внесение ошибок в выбранные позиции
    errorIndices.forEach(index => {
        mas[index] = (mas[index] + 1) % 2; // Инвертируем бит
    });

    return mas;
}

function compareStrings(original, modified) {
    let correctBits = 0;
    for (let i = 0; i < original.length; i++) {
        if (original[i] === modified[i]) {
            correctBits++;
        }
    }

    return (correctBits / original.length) * 100; // Возвращаем процент совпадений
}

function runErrorTests() {
    const lenghtK = 16; // Должна быть равна 2^n
    const k = Math.sqrt(lenghtK);
    const r = hemmingLength(k);
    const n = k + r;

    const masK = [1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0]; // Исходная строка
    let masN = new Array(lenghtK + (r * k)); // Строка с добавленными проверочными битами
    let checkMatrix = checkMatrixFunc(k);

    addCheckBits(masK, masN, checkMatrix);
    alternation(masN, k);

    // Генерируем 30−40 случайных ситуаций для каждой длины ошибки
    const errorLengths = [0, 1, 2, 3, 4]; // Можно добавлять длины ошибок по мере необходимости
    for (let errorLength of errorLengths) {
        console.log(`Тестирование с длиной ошибки: ${errorLength}`);

        let totalAccuracy = 0;
        const numTests = 30; // Количество тестов

        for (let i = 0; i < numTests; i++) {
            let masNWithErrors = [...masN]; // Копируем строку
            generateRandomErrors(masNWithErrors, errorLength); // Генерация случайных ошибок

            // Деперемежаем и исправляем ошибки
            reAlternation(masNWithErrors, k);
            searchErrorLong(masNWithErrors, checkMatrix, k);

            // Сравниваем исходную строку с исправленной
            let accuracy = compareStrings(masK, masNWithErrors);
            totalAccuracy += accuracy;
            console.log(`Тест ${i + 1}: Точность ${accuracy.toFixed(2)}%`);
        }

        let averageAccuracy = totalAccuracy / numTests;
        console.log(`Средняя точность для длины ошибки ${errorLength}: ${averageAccuracy.toFixed(2)}%`);
    }
}

// Генерация случайной строки длины n (мод 2)
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

function hemmingLength(k) {
    return Math.floor(Math.log2(k) + 1);
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

function addCheckBits(masK, masN, checkMatrix) {
    const lenghtK = masK.length; // Должна быть равна 2^n
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

// Запуск тестов
runErrorTests();
