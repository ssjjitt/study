const http = require('http');
const url = require('url');

function getfactorial(factorial) {
    if (factorial === 0 || factorial === 1) {
        return 1;
    }
    else {
        return factorial * getfactorial(factorial - 1);
    }
}

http.createServer((req, res) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    if (req.method === 'GET' && req.url.startsWith('/fact')) {

        const queryParams = new URLSearchParams(url.parse(req.url).query);
        const param = queryParams.get('k');
        const factorial = getfactorial(param);

        const response = {
            k: param,
            fact: factorial
        };

        if (param) {
            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(response));
        }
    }
}).listen(5001);

// http://localhost:5001/fact?k=5