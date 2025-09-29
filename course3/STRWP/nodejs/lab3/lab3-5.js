`
Задание 05
19. Разработайте приложение 03-05 на основе приложения                    
03-02, но функцию для вычисления факториала реализуйте 
асинхронной с помощью механизма setImmediate.
20. Выполните аналогичные заданию 3 замеры.
`

const http = require('http');
const url = require('url');
const fs = require('fs');

function getfactorial(n, callback) {
    setImmediate(() => {
        if (n === 0 || n === 1) {
            callback(null, 1);
        } else {
            getfactorial(n - 1, (err, result) => {
                if (err) {
                    return callback(err);
                }
                callback(null, n * result);
            });
        }
    });
}

http.createServer((req, res) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    if (req.method === 'GET' && req.url === '/') {
        fs.readFile('fetch.html', 'utf8', (err, data) => {
            if (err) {
                res.writeHead(500);
                res.end('Error loading fetch.html');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } else if (req.method === 'GET' && req.url.startsWith('/fact')) {
        const queryParams = new URLSearchParams(url.parse(req.url).query);
        const param = parseInt(queryParams.get('k'), 10);

        getfactorial(param, (err, factorial) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Error calculating factorial');
                return;
            }

            const response = {
                k: param,
                fact: factorial
            };

            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(response));
        });
    }
}).listen(5001);

// http://localhost:5001/

//https://habr.com/ru/companies/ruvds/articles/424553/
