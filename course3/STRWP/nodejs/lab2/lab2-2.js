const http = require('http');
const fs = require('fs');

http.createServer((req, res) => {
    if (req.method === 'GET' && req.url === '/img') {
        {
            const fname = './img.jpg';
            fs.stat(fname, (err, stat) => {
                if (err) {
                    console.error(`Error: ${err.message}`);
                    return;
                }
                else {
                    let jpg = fs.readFileSync(fname);
                    res.writeHead(200, { 'Content-Type': 'image/jpeg' });
                    res.end(jpg);
                }
            })
        }
    }
}).listen(5000);

// http://localhost:5000/img