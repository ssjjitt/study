function printMatrix(matrix) {
    let output = '';
    matrix.forEach(row => {
        output += row + '\n';
    });
    console.log(output);
}

function sortedMatrix(matrix) {
    return matrix.slice().sort();
}

function createMatrix(input) {
    const matrix = [];
    for (let i = 0; i < input.length; i++) {
        matrix.push(input);
        input = input.substring(1) + input[0];
    }
    return matrix;
}

function getTheLastColumnFromMatrix(matrix) {
    let theLastColumn = "";
    matrix.forEach(row => {
        theLastColumn += row[row.length - 1];
    });
    return theLastColumn;
}

function getRowNumberFromMatrix(input, matrix) {
    for (let i = 0; i < matrix.length; i++) {
        if (matrix[i] === input) {
            return i;
        }
    }
    return -1;
}

function addDecodingMatrixRows(input, matrix) {
    for (let i = 0; i < matrix.length; i++) {
        matrix[i] = input[i] + matrix[i];
    }
    return matrix;
}

function getDecodingMatrix(message) {
    const messageMatrix = new Array(message.length).fill("");

    for (let i = 0; i < message.length; i++) {
        addDecodingMatrixRows(message, messageMatrix);
        messageMatrix.sort();
    }
    printMatrix(messageMatrix);
    return messageMatrix;
}


const main = () => {
    const input3Letters = "лет";
    const output3Letters = Array.from(input3Letters)
        .map(char => char.charCodeAt(0).toString(2))
        .join("");

    console.log("Строка в ASCII: " + output3Letters);

    
    // const input = [
    //     "дарья"
    // ];
    
    // const input = [
    //     "глухова"
    // ];

    // const input = [
    //     "летоисчисление"
    // ];

    const input = [
        output3Letters
    ];

    input.forEach(words => {
        console.log(input[0].length);
        console.log("Сообщение: " + words);
        console.log("Кодирование: ");

        const startEncoding = performance.now(); // Начало измерения времени кодирования

        const w1 = createMatrix(words);
        console.log("Матрица W1 - сдвиг строк: ");
        printMatrix(w1);
        const w2 = sortedMatrix(w1);
        console.log("Матрица W2 - отсортированные строки: ");
        printMatrix(w2);

        const inputEncode =
            getTheLastColumnFromMatrix(w2) + getRowNumberFromMatrix(words, w2);
        const gettedMessage = inputEncode.slice(0, words.length);
        console.log("Закодированное сообщение: " + gettedMessage);
        console.log("Номер строки содержащей корректное сообщение: " + getRowNumberFromMatrix(words, w2));

        const endEncoding = performance.now(); // Конец измерения времени кодирования
        const encodingTime = endEncoding - startEncoding;

        console.log("Декодирование");
        const startDecoding = performance.now(); // Начало измерения времени декодирования

        
        const w2ForDecode = getDecodingMatrix(gettedMessage);
        console.log("Восстановленная матрица W2 - отсортировали");
        printMatrix(w2ForDecode);

        const numberOfInitialMessage = parseInt(
            inputEncode.slice(words.length),
            10
        );

        console.log( "Декодированное сообщение: " + w2ForDecode[numberOfInitialMessage]);

        const endDecoding = performance.now(); // Конец измерения времени декодирования
        const decodingTime = endDecoding - startDecoding;

        const output = w2ForDecode[numberOfInitialMessage];

        if (output === words) {
            console.log("Упешно");
        } else {
            console.log("Анлак");
        }
        console.log("Время кодирования: " + encodingTime.toFixed(4));
        console.log("Время декодирования: " + decodingTime.toFixed(4));
    });
}
main();
