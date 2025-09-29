// client.js
const http = require('http');
const fs = require('fs');

const boundary = '----WebKitFormBoundary';
const filePath = 'img.png'; 
const fileContent = fs.readFileSync(filePath);

const body = `--${boundary}\r\n` +
             `Content-Disposition: form-data; name="file"; filename="img.png"\r\n` +
             `Content-Type: image/png\r\n\r\n` +
             fileContent + `\r\n` +
             `--${boundary}--\r\n`;

const options = {
    host: 'localhost',
    path: '/mypath',
    port: 3000,
    method: 'POST',
    headers: {
        'Content-Type': `multipart/form-data; boundary=${boundary}`,
        'Content-Length': Buffer.byteLength(body) 
    }
};

const req = http.request(options, (res) => {
    let data = '';
    res.on('data', (chunk) => {
        data += chunk.toString('utf8');
    });
    res.on('end', () => {
        console.log('HTTP response:', data);
    });
});

req.on('error', (error) => {
    console.log('HTTP request error:', error.message);
});
req.write(body);
req.end();