const fs = require('fs');

function calculateFrequencies(filePath) {
    const text = fs.readFileSync(filePath, 'utf-8');
    const frequencies = {}; // символ - количество
    let totalChars = 0; // сколько обработано

    const base64Chars = 'A-Za-z0-9+/='; 
    const regex = new RegExp(`[${base64Chars}а-яА-Я ]`); // кириллица, пробелы, base64

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

function calculateEntropyShannon(probabilities) {
    return -Object.values(probabilities)
        .map(p => p * Math.log2(p))
        .reduce((a, b) => a + b, 0);
}

function calculateEntropyHartley(N) {
    return Math.log2(N);
}

function calculateRedundancy(entropyShannon, entropyHartley) {
  return (entropyHartley - entropyShannon) / entropyShannon;
}

function main(filePath) {
    const { frequencies, totalChars } = calculateFrequencies(filePath);
    console.log("Частоты символов:", frequencies);

    const probabilities = calculateProbabilities(frequencies, totalChars);
    console.log("Вероятности:", probabilities);

    const entropyShannon = calculateEntropyShannon(probabilities);
    console.log(`Энтропия по Шеннону: ${entropyShannon.toFixed(4)} бит`);

    const uniqueChars = Object.keys(frequencies).length; 
    const entropyHartley = calculateEntropyHartley(uniqueChars);
    console.log(`Энтропия по Хартли: ${entropyHartley.toFixed(4)} бит`);

    const redundancy = calculateRedundancy(entropyShannon, entropyHartley);
    console.log(`Избыточность алфавита: ${(redundancy * 100).toFixed(2)}%`);
}

const filePath = 'text64.txt'; 
main(filePath);
