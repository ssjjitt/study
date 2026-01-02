const express = require('express');
const bodyParser = require('body-parser');
const { JSONRPCServer } = require("json-rpc-2.0");

const app = express();
const server = new JSONRPCServer();

app.use(bodyParser.json());

server.addMethod('sum', (params) => {
    return params.reduce((a, b) => a + b, 0);
});

server.addMethod('mul', (params) => {
    return params.reduce((a, b) => a * b, 1);
});

server.addMethod('div', (params) => {
    const [x, y] = params;
    if (y === 0) {
        throw new Error('Division by zero');
    }
    return x / y;
});

server.addMethod('proc', (params) => {
    const [x, y] = params;
    if (y === 0) {
        throw new Error('Division by zero');
    }
    return (x / y) * 100;
});

app.post('/jsonrpc', (req, res) => {
    server.receive(req.body).then((jsonrpcRes) => {
        res.json(jsonrpcRes);
    }).catch((err) => {
        res.status(400).json({ error: err.message });
    });
});

app.listen(3000, () => {
    console.log('http://localhost:3000');
});
// http://localhost:3000/jsonrpc