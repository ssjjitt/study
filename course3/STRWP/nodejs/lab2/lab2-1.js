const http = require('http');
const fs = require('fs');
const path = require('path');

http.createServer((req, res) => {
    if (req.method === 'GET' && req.url === '/html') {
        {
            let html = fs.readFileSync('./lab2-1.html');
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
            res.end(html);
        }
    }
}).listen(5000);

// http://localhost:5000/html