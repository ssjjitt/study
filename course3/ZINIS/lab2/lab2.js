const fs = require('fs');

function calculateFrequencies(filePath) {
    const text = fs.readFileSync(filePath, 'utf-8');
    const frequencies = {}; // символ - количество
    let totalChars = 0; // сколько обработано
    const latinChars = 'a-zA-Z';
    const russianChars = 'а-яА-Я'; 
    const binaryChars = '01';
    const spaceChars = ' ';
    const serbianChars = 'АБВГДЂЕЖЗИЈКЛЉМНЊОПРСТЋУФХЦЧЏШабвгдђежзијклљмнњопрстућуфхцчџш';
    const regexString = `[${latinChars}${russianChars}${serbianChars}${spaceChars}${binaryChars}]`;
    const regex = new RegExp(regexString);

    for (const char of text) {
        if (char.match(regex)) { 
            frequencies[char] = (frequencies[char] || 0) + 1;
            totalChars++;
        }
    }

    return { frequencies, totalChars };
}

function calculateProbabilities(frequencies, totalChars) {
    const probabilities = {};
    for (const char in frequencies) {
        probabilities[char] = frequencies[char] / totalChars;
    }
    return probabilities;
}

// по шеннону
function calculateEntropy(probabilities) {
    return -Object.values(probabilities)
        .map(p => p * Math.log2(p))
        .reduce((a, b) => a + b, 0);
}

function calculateInformation(entropy, textLength) {
    return entropy * textLength;
}

function calculateConditionalEntropy(errorProb) {
    const q = 1 - errorProb;
    return -errorProb * Math.log2(errorProb) - q * Math.log2(q);
}

function calculateEffectiveEntropy(errorProb) {
    return 1 - calculateConditionalEntropy(errorProb);
}

function calculateInformationWithError(entropy, textLength, errorProb) {
    const effectiveEntropy = calculateEffectiveEntropy(errorProb);
    return entropy * textLength * effectiveEntropy;
}

// Основной процесс расчета
function main(filePath, fullName) {
    const { frequencies, totalChars } = calculateFrequencies(filePath);
    console.log("Частоты символов:", frequencies);

    const probabilities = calculateProbabilities(frequencies, totalChars);
    console.log("Вероятности:", probabilities);

    const entropy = calculateEntropy(probabilities);
    console.log(`Энтропия алфавита: ${entropy.toFixed(4)} бит`);

    const infoAmount = calculateInformation(entropy, fullName.length);
    console.log(`Количество информации (ФИО): ${infoAmount.toFixed(4)} бит`);

    [0.1, 0.5, 0.999999].forEach(errorProb => {
        const infoWithError = calculateInformationWithError(entropy, fullName.length, errorProb);
        console.log(`Информация с ошибкой ${errorProb}: ${infoWithError.toFixed(12)} бит`);
    });
}
// Глухова Дарья Витальевна
// Gluhova Daria Vitalievna
// Глухова Дарја Витаљевна
// 010001110110110001110101011010000110111101110110011000010010000001000100011000010111001001101001011000010010000001010110011010010111010001100001011011000110100101100101011101100110111001100001
const filePath = 'text1.txt'; 
const fullName = 'Глухова Дарья Витальевна'; 
main(filePath, fullName);
