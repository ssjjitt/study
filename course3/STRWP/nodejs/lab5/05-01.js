const http = require('http');
const url = require('url');
const fs = require('fs');
const data = require('./DB');
const readline = require("node:readline");

const db = new data.DB();
const stats = { start: null, finish: null, request: 0, commit: 0 };
let serverTimeout = null;
let commitInterval = null;
let statsInterval = null;
let tempStats = { request: 0, commit: 0 };

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})


rl.on('line', (input) => {
    const [command, param] = input.split(' ');
    const x = parseInt(param);

    switch (command) {
        case 'sd':
            if (serverTimeout) {
                clearTimeout(serverTimeout);
            }
            if (!isNaN(x)) {
                serverTimeout = setTimeout(() => {
                    console.log('Stopping life...');
                    process.exit(0);
                }, x * 1000);
                serverTimeout.unref();
            }
            break;
        case 'sc': // периодич коммит
            if (commitInterval) {
                clearInterval(commitInterval);
                commitInterval = null;
            }
            if (!isNaN(x)) {
                commitInterval = setInterval(() => {
                    db.commit();
                }, x * 1000);
                commitInterval.unref(); // чтобы таймер не блокировал заверш прог
            }
            break;
        case 'ss': // сбор стат
            if (statsInterval) {
                clearInterval(statsInterval);
                statsInterval = null;
                stats.finish = new Date().toLocaleString();
                console.log('Statistics collection stopped');
            } else if (!isNaN(x)) {
                stats.start = new Date().toLocaleString();
                stats.finish = null;
                stats.request = 0;
                stats.commit = 0;
                tempStats = { request: 0, commit: 0 };
                statsInterval = setInterval(() => {
                    stats.request += tempStats.request;
                    stats.commit += tempStats.commit;
                    tempStats.request = 0;
                    tempStats.commit = 0;
                    stats.finish = null;
                    console.log(`Statistics: request - ${stats.request}, commit - ${stats.commit}`);
                }, x * 1000);
                statsInterval.unref();
            }
            break;
        default:
            console.log('Unknown command')
    }
})

db.on('COMMIT', () => {
    tempStats.commit++;
    console.log(`COMMIT #${stats.commit + tempStats.commit} done`);
})

db.on('GET', (request, response) => {
    tempStats.request++;
    response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
    response.end(JSON.stringify(db.select()));
});

db.on('POST', (request, response) => {
    tempStats.request++;
    let body = '';
    request.on('data', chunk => body += chunk);
    request.on('end', () => {
        try {
            const param = JSON.parse(body);
            param.id = db.select().length ? Math.max(...db.select().map(i => i.id)) + 1 : 1;
            let newRecord = { id: param.id, name: param.name, bday: param.bday };
            db.insert(newRecord);
            response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify(newRecord));
        } catch {
            response.writeHead(400, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify({ error: 'Invalid JSON' }));
        }
    });
});

db.on('PUT', (request, response) => {
    tempStats.request++;
    let body = '';
    request.on('data', chunk => body += chunk);
    request.on('end', () => {
        try {
            const param = JSON.parse(body);
            db.update(param);
            response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify(param));
        } catch {
            response.writeHead(400, { 'Content-Type': 'application/json; charset=utf-8' });
            response.end(JSON.stringify({ error: 'Invalid JSON' }));
        }
    });
});

db.on('DELETE', (request, response) => {
    tempStats.request++;
    const queryParams = new URLSearchParams(url.parse(request.url).query);
    const id = parseInt(queryParams.get('id'));
    const deletedItem = db.delete(id);
    response.writeHead(deletedItem ? 200 : 404, { 'Content-Type': 'application/json; charset=utf-8' });
    response.end(JSON.stringify(deletedItem || { error: 'Item not found' }));
});

const server = http.createServer(function (request, response) {
    const pathname = url.parse(request.url).pathname;

    if (pathname === '/') {
        fs.readFile('./05-01.html', 'utf-8', (err, html) => {
            response.writeHead(err ? 500 : 200, { 'Content-Type': err ? 'text/plain' : 'text/html; charset=utf-8' });
            response.end(err ? 'Error loading index.html' : html);
        });
    } else if (pathname === '/api/db') {
        db.emit(request.method, request, response);
    } else if (pathname === '/api/ss') {
        response.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
        response.end(JSON.stringify(stats));
    }
});

server.listen(5000, () => {
    console.log('Server is running at http://localhost:5000');
});