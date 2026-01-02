const input = "глуховадарья ";

const chars = [];
const frequency = [];
const probability = [];
const lettersArray = [];
const frequenciesArray = [];
const probabilitiesArray = [];
const letterBitsArray = [];

function log(message) {
    console.log(message);
}

function displayTable(headers, rows) {
    const tableData = rows.map(row => {
        const obj = {};
        headers.forEach((h, i) => {
            obj[h] = row[i];
        });
        return obj;
    });
    console.table(tableData);
}


function getProbabilityAndFrequency(inputMessage) {
    [...new Set(inputMessage)].forEach(ch => {
        const count = inputMessage.split(ch).length - 1;
        chars.push(ch);
        frequency.push(count);
        probability.push(count / inputMessage.length);
    });
}

function getArrayFromChars() {
    for (let i = 0; i < chars.length; i++) {
        lettersArray[i] = chars[i];
        frequenciesArray[i] = frequency[i];
        probabilitiesArray[i] = probability[i];
    }
}

function printResults() {
    const headers = ["Символ", "Частота", "Вероятность"];
    const rows = lettersArray.map((char, i) => [char, frequenciesArray[i], probabilitiesArray[i].toFixed(6)]);
    displayTable(headers, rows);
}

function getSortedArray() {
    const combined = lettersArray.map((char, i) => ({ char, probability: probabilitiesArray[i] }));
    combined.sort((a, b) => b.probability - a.probability);

    combined.forEach((item, i) => {
        lettersArray[i] = item.char;
        probabilitiesArray[i] = item.probability;
    });
}

function getSummaryProbabilities() {
    return probabilitiesArray.reduce((acc, prob) => acc + prob, 0);
}

function shannonFano(left, right) {
    if (left >= right) return;
    const splitPoint = toSplitSequences(left, right);
    for (let i = left; i <= splitPoint; i++) letterBitsArray[i] += "0";
    for (let i = splitPoint + 1; i <= right; i++) letterBitsArray[i] += "1";
    shannonFano(left, splitPoint);
    shannonFano(splitPoint + 1, right);
}

function toSplitSequences(left, right) {
    const total = probabilitiesArray.slice(left, right + 1).reduce((acc, prob) => acc + prob, 0);
    const halfTotal = total / 2;
    let acc = 0;
    let i;
    for (i = left; i <= right; i++) {
        acc += probabilitiesArray[i];
        if (acc >= halfTotal) break;
    }
    return i;
}

function getEncodedMessage(input, charsArray, charBitsArray) {
    return input.split('').map(ch => charBitsArray[charsArray.indexOf(ch)]).join('');
}

function getDecodedMessage(encodedMessage, charsArray, charBitsArray) {
    let decodedMessage = '';
    let currentBits = '';
    for (const bit of encodedMessage) {
        currentBits += bit;
        const index = charBitsArray.indexOf(currentBits);
        if (index !== -1) {
            decodedMessage += charsArray[index];
            currentBits = '';
        }
    }
    return decodedMessage;
}

function encodingToBytes(message) {
    const encoder = new TextEncoder(); // default UTF-8
    const bytes = encoder.encode(message);
    return Array.from(bytes).map(b => b.toString(2).padStart(8, '0')).join('');
}

// Запуск
log("Сообщение: " + input);
log("Рассчет вероятностей появления символов в сообщении:\n");

getProbabilityAndFrequency(input);
getArrayFromChars();
printResults();

getSortedArray();

letterBitsArray.length = lettersArray.length;
letterBitsArray.fill("");

const sumOfProbabilities = getSummaryProbabilities();
log("Сумма вероятностей = " + sumOfProbabilities.toFixed(6) + "\n");

log("Метод сжатия Шеннона-Фано:");
shannonFano(0, lettersArray.length - 1);

const bitTableHeaders = ["Символы", "Биты"];
const bitTableRows = lettersArray.map((char, i) => [char, letterBitsArray[i]]);
displayTable(bitTableHeaders, bitTableRows);

const encodedMessage = getEncodedMessage(input, lettersArray, letterBitsArray);
const decodedMessage = getDecodedMessage(encodedMessage, lettersArray, letterBitsArray);

log("Закодированное сообщение: " + encodedMessage);
log("Декодированное сообщение: " + decodedMessage + "\n");

log("В ASCII:");
const asciiEncoded = encodingToBytes(input);
log("Закодированное сообщение: " + asciiEncoded);
log("Сообщение: " + input + "\n");

log("Символов после сжатия:");
log("методом Шеннона-Фано: " + encodedMessage.length);
log("в ASCII: " + asciiEncoded.length);

const times = (asciiEncoded.length / encodedMessage.length).toFixed(2);
log("\nЭффективность сжатия:");
log("Методом Шеннона-Фано мы уменьшили общий размер данных в " + times + " раз по сравнению с кодом ASCII");
