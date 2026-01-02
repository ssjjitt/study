const fs = require('fs');

function convertToBase64(filePath, outputFile) {
    if (!fs.existsSync(filePath)) {
        console.error("файл не найден.");
        return;
    }

    const fileContent = fs.readFileSync(filePath);
    const base64String = fileContent.toString('base64');

    fs.writeFileSync(outputFile, base64String, 'utf-8');
    console.log(`сохранено в ${outputFile}`);
}

const inputFilePath = 'text1.txt';  
const outputFilePath = 'text64.txt'; 

convertToBase64(inputFilePath, outputFilePath);
