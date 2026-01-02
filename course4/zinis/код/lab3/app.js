const fs = require('fs');
const path = require('path');
const { codeMulti, decodeMulti } = require('./multi');
const { codeRoute, decodeRoute } = require('./route');
const ExcelJS = require('exceljs');

async function saveFrequencyToExcel(frequencyData, outputPath) {
    const workbook = new ExcelJS.Workbook();
    const worksheet = workbook.addWorksheet('Frequency Data');

    worksheet.columns = [
        { header: 'Символ', key: 'char', width: 10 },
        { header: 'Частота', key: 'freq', width: 10 },
    ];

    frequencyData.forEach(item => {
        worksheet.addRow(item);
    });

    await workbook.xlsx.writeFile(outputPath);
    console.log(`Данные сохранены в ${outputPath}`);
}

function countFrequency(text) {
    const frequency = {};

    for (const char of text) {
        if (char !== ' ' && char !== '.' && char !== "'") { 
            frequency[char] = (frequency[char] || 0) + 1;
        }
    }

    return Object.entries(frequency)
        .map(([char, freq]) => ({ char, freq }))
        .sort((a, b) => b.freq - a.freq);
}


function getFrequency(text) {
    const freq = {};
    for (const char of text) {
        if (char.trim() === '') continue; 
        freq[char] = (freq[char] || 0) + 1;
    }
    return freq;
}

function writeFrequencyCSV(freq, filename) {
    const rows = ["Символ,Частота"];
    for (const [char, count] of Object.entries(freq)) {
        rows.push(`"${char}",${count}`);
    }
    fs.writeFileSync(filename, rows.join("\n"), 'utf8');
    console.log(`Частота символов записана в ${filename}`);
}


const filePath = path.join(__dirname, 'text.txt');

fs.readFile(filePath, 'utf8', (err, data) => {
    if (err) {
        console.error("Ошибка чтения файла:", err);
        return;
    }

    const text = data.trim();
    console.log("\n\nОригинальный текст:\n", text);

    // ---------- множественная ----------
    console.log("\n\nМножественная перестановка\n");
    let start = Date.now();
    const shifrMulti = codeMulti(text);
    const decodedMulti = decodeMulti(shifrMulti);
    let end = Date.now();

    console.log("\n\nЗашифровано:\n", shifrMulti);
    console.log("\n\nРасшифровано:\n", decodedMulti);
    console.log("\n\nВремя выполнения\n:", end - start, "ms");

    const frequencyMulti = countFrequency(shifrMulti);
    const outputPathMulti = path.join(__dirname, 'frequency_multi.xlsx');
    saveFrequencyToExcel(frequencyMulti, outputPathMulti);


    // ---------- маршрутная ----------
    console.log("\n\nМаршрутная перестановка\n");
    start = Date.now();
    const shifrRoute = codeRoute(text);
    const decodedRoute = decodeRoute(shifrRoute);

    console.log("\n\nЗашифровано:\n", shifrRoute);
    console.log("\n\nРасшифровано:\n", decodedRoute);

    end = Date.now();
    console.log("\n\nВремя выполнения:\n", end - start, "ms");

    const frequencyRoute = countFrequency(shifrRoute);
    const outputPathRoute = path.join(__dirname, 'frequency_route.xlsx');
    saveFrequencyToExcel(frequencyRoute, outputPathRoute);
});
