const http = require('http');

let currentState = 'idle';

const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    res.end(`
        <html>
            <head>
                <title>Состояние приложения</title>
                <script>
                    function changeState() {
                        const input = document.getElementById('stateInput').value;
                        const xhr = new XMLHttpRequest();
                        xhr.open('POST', '/change-state', true);
                        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                        xhr.send('state=' + encodeURIComponent(input));
                        document.getElementById('stateInput').value = '';
                    }
                </script>
            </head>
            <body>
                <h1>Текущее состояние: <span id="currentState">${currentState}</span></h1>
                <p>Доступные состояния: norm, stop, test, idle</p>
                <input type="text" id="stateInput" placeholder="Введите состояние">
                <button onclick="changeState()">Изменить состояние</button>
            </body>
        </html>
    `);
});

server.on('request', (req, res) => {
    if (req.method === 'POST' && req.url === '/change-state') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString(); 
        });
        req.on('end', () => {
            const params = new URLSearchParams(body);
            const newState = params.get('state').trim();

            if (newState === 'exit') {
                console.log('покапока');
                process.exit();
            }
            else if (input === 'currstate') {
                console.log(`состояние: ${currentState}`);
            }
            else if (['norm', 'stop', 'test', 'idle'].includes(newState)) {
                currentState = input;
                console.log(`состояние: ${currentState}`);
            }
            else {
                console.log(`ойой "${newState}".`);
            }
            res.writeHead(200, { 'Content-Type': 'text/plain' });
            res.end(currentState);
        });
    }
}).listen(5000);