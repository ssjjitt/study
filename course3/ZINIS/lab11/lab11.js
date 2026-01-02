const readline = require('readline');
const Decimal = require('decimal.js');

class Node {
    constructor(symbol, low, high) {
        this.symbol = symbol;
        this.low = low;
        this.high = high;
    }

    toString() {
        return `Low: ${this.low} | High: ${this.high}`;
    }
}

class InfoString {
    static sb = [];
}

class Compressor {
    constructor() {
        this.nodes = [];
        this.frequencies = {};
        this.resultNode = new Node('*', 0, 1);
    }

    build(source) {
        this.nodes = [];
        this.frequencies = {};
        const inc = 1 / source.length;

        for (const char of source) {
            if (!this.frequencies[char]) {
                this.frequencies[char] = 0;
            }
            this.frequencies[char] += inc;
        }

        const sortedEntries = Object.entries(this.frequencies).sort((a, b) => a[1] - b[1]);
        let low = 0;
        for (const [symbol, freq] of sortedEntries) {
            this.nodes.push(new Node(symbol, +low.toFixed(5), +(low + freq).toFixed(5)));
            low += freq;
        }
    }

    compress(source) {
        InfoString.sb = [];
        this.resultNode = new Node('*', new Decimal(0), new Decimal(1));

        for (const symbol of source) {
            const oldHigh = this.resultNode.high;
            const oldLow = this.resultNode.low;
            InfoString.sb.push(`Low: ${oldLow.toString()} | High: ${oldHigh.toString()}`);

            const node = this.nodes.find(n => n.symbol === symbol);

            const newHigh = oldLow.plus(oldHigh.minus(oldLow).times(new Decimal(node.high)));
            const newLow = oldLow.plus(oldHigh.minus(oldLow).times(new Decimal(node.low)));

            this.resultNode.low = newLow;
            this.resultNode.high = newHigh;
        }

        InfoString.sb.push(`Low: ${this.resultNode.low.toString()} | High: ${this.resultNode.high.toString()}`);
        return this.resultNode.low;
    }

    decompress(compressValue, length) {
        let result = '';
        let value = new Decimal(compressValue);
        InfoString.sb = [];

        for (let i = 0; i < length; i++) {
            const node = this.nodes.find(n =>
                value.greaterThanOrEqualTo(n.low) && value.lessThan(n.high)
            );
            InfoString.sb.push(`${value.toString()}\t-- ${node.symbol}`);
            result += node.symbol;

            const low = new Decimal(node.low);
            const high = new Decimal(node.high);
            value = value.minus(low).dividedBy(high.minus(low));
        }

        return result;
    }

    printScale() {
        const scaleLength = 150; // ширина всей шкалы
        const line1 = Array(scaleLength).fill(' ');
        const line2 = Array(scaleLength).fill(' ');
        const line3 = Array(scaleLength).fill(' ');

        const positions = this.nodes.map(n => ({
            symbol: n.symbol,
            lowPos: Math.floor(n.low * scaleLength),
            highPos: Math.floor(n.high * scaleLength),
            label: n.low.toFixed(5),
            highLabel: n.high.toFixed(5)
        }));

        // Засечки
        for (const p of positions) {
            line1[p.lowPos] = '|';
        }
        // Добавим финальную засечку
        const last = positions[positions.length - 1];
        line1[last.highPos] = '|';

        // Буквы — ставим по центру интервала
        for (const p of positions) {
            const center = Math.floor((p.lowPos + p.highPos) / 2);
            line2[center] = p.symbol;
        }

        // Числа под засечками
        let lastLabelEnd = -10;
        for (const p of positions) {
            const label = p.label;
            const start = Math.max(p.lowPos - Math.floor(label.length / 2), lastLabelEnd + 1);
            for (let i = 0; i < label.length && (start + i) < scaleLength; i++) {
                line3[start + i] = label[i];
            }
            lastLabelEnd = start + label.length - 1;
        }
        // последнее значение справа
        const endLabel = last.highLabel;
        const endStart = Math.min(scaleLength - endLabel.length, last.highPos - Math.floor(endLabel.length / 2));
        for (let i = 0; i < endLabel.length && (endStart + i) < scaleLength; i++) {
            line3[endStart + i] = endLabel[i];
        }

        console.log(line1.join(''));
        console.log(line2.join(''));
        console.log(line3.join(''));
    }
}

function calculateCompressionEfficiency(compressed, original) {
    const compressedLength = Math.min(compressed.toString().length, 4);
    const efficiency = (1 - compressedLength / original.length) * 100;
    console.log(`\nЭффективность сжатия арифметическим методом: ${efficiency.toFixed(2)}%`);
}

function checkCompressionOverflow(compressed) {
    const bitsNeeded = compressed.toString(2).length;
    const maxBits = 53; // JavaScript безопасные числа
    if (bitsNeeded > maxBits) {
        console.log("Возможно переполнение при сжатии данных.");
    } else {
        console.log("Переполнение при сжатии данных маловероятно.");
    }
}

function printCompressionSteps() {
    console.log("Шаг |         Low           |         High         ");
    console.log("----|-----------------------|----------------------");

    InfoString.sb.forEach((line, index) => {
        const match = line.match(/Low: ([\d.]+) \| High: ([\d.]+)/);
        if (match) {
            const step = index.toString().padStart(3, ' ');
            const low = match[1].padStart(22, ' ');
            const high = match[2].padStart(22, ' ');
            console.log(`${step} |${low} |${high}`);
        }
    });
}


function main() {
    const word = 'SWISS_MISS';
    const wordLength = word.length;
    const compressor = new Compressor();

    compressor.build(word);

    console.log("Вероятности:");
    for (const node of compressor.nodes) {
        console.log(`p(${node.symbol}) = ${(node.high - node.low).toFixed(5)}`);
    }

    compressor.build(word);

    console.log("\nИнтервальная шкала:");
    compressor.printScale();

    const compressed = compressor.compress(word);
    console.log("\nСжатые данные:");
    printCompressionSteps();
    // console.log(InfoString.sb.join('\n'));
    // console.log(`\nРезультат: ${compressed}`);

    const decompressed = compressor.decompress(compressed, wordLength);
    console.log("\nРасжатые данные:");
    console.log(InfoString.sb.join('\n'));
    console.log(`\nРезультат: ${decompressed}`);

    checkCompressionOverflow(compressed);
    calculateCompressionEfficiency(compressed, word);
}

main();