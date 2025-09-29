const http = require('http');
let b = ''; 

http.createServer(function (request, response) {
    request.on('data', str => { b += str; console.log('data', b); });
    
    response.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    response.end(
        `<!DOCTYPE html>
        <html>
            <head></head>
            <body>
                <h2>Структура запроса</h2>
                <p>метод: ${request.method}</p>
                <p>uri: ${request.url}</p>
                <p>версия: ${request.httpVersion}</p>
                <h2>ЗАГОЛОВКИ:</h2>
                <p>${JSON.stringify(request.headers, null, 2).replace(/,/g, '<br>')}</p>
                <h2>тело: ${b}</h2>
            </body>
        </html>`
    );
}).listen(3001);