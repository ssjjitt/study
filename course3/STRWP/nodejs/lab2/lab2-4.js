const http = require('http');
const fs = require('fs');
const path = require('path');

http.createServer((req, res) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    if (req.method === 'GET' && req.url === '/xmlhttprequest') {
        {
            let html = fs.readFileSync('./xmlhttprequest.html');
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
            res.end(html);
        }
    }
}).listen(5000);

// https://metanit.com/web/javascript/13.1.php
// http://localhost:5000/xmlhttprequest