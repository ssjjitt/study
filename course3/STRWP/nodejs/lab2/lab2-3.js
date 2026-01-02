const http = require('http');
const url = require('url');

http.createServer((req, res) => {
  res.setHeader('Access-Control-Allow-Origin', '*'); // это для 4 задания
  if (req.method === 'GET' && req.url.startsWith('/api/name')) {
    const queryParams = new URLSearchParams(url.parse(req.url).query);
    
    const name = queryParams.get('name');
    
    if (name) {
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      res.end(`${name}`);
    } else {
      res.writeHead(400, { 'Content-Type': 'text/plain' });
      res.end('Параметры обязательны');
    }
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Не найдено');
  }
}).listen(5001);

// http://localhost:5001/api/name?name=gluhova