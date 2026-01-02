const https = require('https');
const fs = require('fs');
const path = require('path');
const url = require('url');

const options = {
  key: fs.readFileSync('ca_opyat/resource-key.pem'),
  cert: fs.readFileSync('ca_opyat/resource-cert.pem'),
};

https.createServer(options, (req, res) => {
  if (req.method !== 'GET') {
    res.writeHead(405);
    res.end('Только GET!');
    return;
  }

  const parsedUrl = url.parse(req.url);
  const pathname = parsedUrl.pathname;

  const match = pathname.match(/^\/([1-3])$/);
  if (!match) {
    res.writeHead(404);
    res.end('Чё-то не то');
    return;
  }

  const num = match[1];
  const filePath = path.join('public', `index${num}.html`);

  fs.readFile(filePath, (err, data) => {
    if (err) {
      res.writeHead(404);
      res.end('Файл не найден!');
      return;
    }
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(data);
  });
}).listen(3443, () => console.log('HTTPS сервер запущен'));

// https://localhost:3443

/*
openssl genrsa -out ca/ca-key.pem 2048
openssl req -new -x509 -days 365 -key ca/ca-key.pem -out ca/ca-cert.pem -subj "/CN=CA-LAB22-GDV"

openssl genrsa -out resource-key.pem 2048
openssl req -new -key resource-key.pem -out resource.csr -subj "/CN=RS-LAB22-SAU"

openssl x509 -req -in resource.csr -CA ca/ca-cert.pem -CAkey ca/ca-key.pem -CAcreateserial -out resource-cert.pem -days 365 -extfile ca/resource.ext
*/


