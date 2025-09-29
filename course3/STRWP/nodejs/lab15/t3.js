const fs = require('fs');
const path = require('path');

async function loadWasm() {
    const wasmPath = path.join(__dirname, 'lab15.wasm');
    const buffer = fs.readFileSync(wasmPath);

    const { instance } = await WebAssembly.instantiate(buffer);
    return instance.exports;
}

async function main() {
    try {
        const wasmExports = await loadWasm();

        const sum = wasmExports.c;
        const mul = wasmExports.d;
        const sub = wasmExports.e;

        console.log('5 + 3 =', sum(5, 3));
        console.log('5 * 3 =', mul(5, 3));
        console.log('5 - 3 =', sub(5, 3));

    } catch (err) {
        console.error('WASM error:', err);
    }
}

main();