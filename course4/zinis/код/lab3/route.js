function code(text, s = 6) {
    const textSize = text.length;
    const k = Math.floor(textSize / s) + 1;

    let grid = Array.from({ length: s }, () => Array(k).fill('$'));
    let index = 0;

    for (let r = 0; r < s; r++) {
        for (let c = 0; c < k; c++) {
            if (index < textSize) {
                grid[r][c] = text[index++];
            }
        }
    }

    let encryptedText = "";
    for (let c = 0; c < k; c++) {
        for (let r = 0; r < s; r++) {
            encryptedText += grid[r][c];
        }
    }

    return encryptedText;
}

function decode(encryptedText, s = 6) {
    const textSize = encryptedText.length;
    const k = Math.floor(textSize / s) + 1;

    let grid = Array.from({ length: s }, () => Array(k).fill(''));
    let index = 0;

    for (let c = 0; c < k; c++) {
        for (let r = 0; r < s; r++) {
            if (index < textSize) {
                grid[r][c] = encryptedText[index++];
            }
        }
    }

    let decryptedText = "";
    for (let r = 0; r < s; r++) {
        for (let c = 0; c < k; c++) {
            if (grid[r][c] !== '$') {
                decryptedText += grid[r][c];
            }
        }
    }

    return decryptedText;
}

module.exports = { codeRoute: code, decodeRoute: decode };
