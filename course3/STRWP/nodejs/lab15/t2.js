const express = require('express');
const path = require('path');
const fs = require('fs');

const app = express();
const PORT = 3000;

app.use(express.static(__dirname));

app.get('/wasm', async (req, res) => {
    try {
        const wasmPath = path.join(__dirname, 'lab15.wasm');
        const buffer = fs.readFileSync(wasmPath);
        res.set('Content-Type', 'application/wasm');
        res.send(buffer);
    } catch (err) {
        res.status(500).send('Error loading WASM file');
    }
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});