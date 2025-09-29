const http = require('http');
const fs = require('fs');
const path = require('path');

http.createServer((req, res) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    if (req.method === 'GET' && req.url === '/fetch') {
        {
            let html = fs.readFileSync('./fetch.html');
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
            res.end(html);
        }
    }
}).listen(5000);




// https://habr.com/ru/companies/otus/articles/795559/
// http://localhost:5000/fetch