const input = "глуховадарья";

class HuffmanNode {
    constructor(symbol, probability, left = null, right = null) {
        this.symbol = symbol;
        this.probability = probability;
        this.bitCode = "";
        this.left = left;
        this.right = right;
    }
}

class HuffmanEncoding {
    static encode(input) {
        const frequency = {};
        for (const ch of input) {
            frequency[ch] = (frequency[ch] || 0) + 1;
        }

        const priorityQueue = Object.entries(frequency).map(([symbol, count]) =>
            new HuffmanNode(symbol, count / input.length)
        );

        while (priorityQueue.length > 1) {
            priorityQueue.sort((a, b) => a.probability - b.probability);
            const left = priorityQueue.shift();
            const right = priorityQueue.shift();
            const newNode = new HuffmanNode(null, left.probability + right.probability, left, right);
            priorityQueue.push(newNode);
        }

        const root = priorityQueue[0];
        const codeTable = {};
        HuffmanEncoding.traverse(root, "", codeTable);
        return { codeTable, frequency };
    }

    static traverse(node, code, codeTable) {
        if (!node.left && !node.right) {
            codeTable[node.symbol] = code;
            node.bitCode = code;
        } else {
            if (node.left) HuffmanEncoding.traverse(node.left, code + "0", codeTable);
            if (node.right) HuffmanEncoding.traverse(node.right, code + "1", codeTable);
        }
    }
}

class EncodeDecode {
    static getEncodedMessage(input, codeTable) {
        return input.split('').map(ch => codeTable[ch]).join('');
    }

    static getDecodedMessage(encodedMessage, codeTable) {
        const reverseCodeTable = Object.fromEntries(
            Object.entries(codeTable).map(([k, v]) => [v, k])
        );
        let decodedMessage = '';
        let currentBits = '';
        for (const bit of encodedMessage) {
            currentBits += bit;
            if (reverseCodeTable[currentBits]) {
                decodedMessage += reverseCodeTable[currentBits];
                currentBits = '';
            }
        }
        return decodedMessage;
    }

    static encodingToBytes(message) {
        const encoder = new TextEncoder();
        const bytes = encoder.encode(message);
        return Array.from(bytes).map(b => b.toString(2).padStart(8, '0')).join('');
    }
}

console.log("Сообщение:", input);

const { codeTable, frequency } = HuffmanEncoding.encode(input);

console.log("\nТаблица частот и вероятностей:");
console.table(
    Object.entries(frequency).map(([char, count]) => ({
        Символ: char,
        Частота: count,
        Вероятность: (count / input.length).toFixed(6)
    }))
);

console.log("Метод сжатия Хаффмана:");
console.table(
    Object.entries(codeTable).map(([char, bits]) => ({
        Символ: char,
        Биты: bits
    }))
);

const encodedMessage = EncodeDecode.getEncodedMessage(input, codeTable);
const decodedMessage = EncodeDecode.getDecodedMessage(encodedMessage, codeTable);

console.log("Закодированное сообщение:", encodedMessage);
console.log("Декодированное сообщение:", decodedMessage);

console.log("\nВ ASCII:");
const asciiEncoded = EncodeDecode.encodingToBytes(input);
console.log("Закодированное сообщение:", asciiEncoded);
console.log("Сообщение:", input);

console.log("\nСимволов после сжатия:");
console.log("методом Хаффмана:", encodedMessage.length);
console.log("в ASCII:", asciiEncoded.length);

const times = (asciiEncoded.length / encodedMessage.length).toFixed(2);
console.log("\nЭффективность сжатия:");
console.log("Методом Хаффмана мы уменьшили общий размер данных в " + times + " раз по сравнению с кодом, полученным преобразованием в коды ASCII");
