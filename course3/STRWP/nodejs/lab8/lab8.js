let http = require('http');
let fs = require('fs');
let qs = require('querystring');
let url = require('url');
let parseString = require("xml2js").parseString;
let xmlbuilder = require("xmlbuilder");
const mp = require("multiparty");
const Console = require("console");

// бацаем ответ в виде xml из данных которые сам клиент нам дает
let xmlbuild = (obj) => {
    let rc = "<result>parse error</result>";
    try {
        let sum = 0;
        let concat = "";
        // новый xml док 
        let xmldoc = xmlbuilder.create("response").att("request", obj.request.$.id);
        // тут короче будет что-то типа:
        // <response request="id">
        obj.request.x.map((e, i) => {
            sum += parseInt(e.$.value);
        });

        obj.request.m.map((e, i) => {
            concat += String(e.$.value);
        });
        xmldoc.ele("sum", { element: "x", result: sum });
        // <sum element="x" result="sum">
        xmldoc.ele("concat", { element: "m", result: concat });
        // <concat element="m" result="concat">

        rc = xmldoc.toString({ pretty: true });
    } catch (e) {
        console.log(e);
    }
    return rc;
};

let server = http.createServer((req, res) => {
    switch (req.method) {
        case 'GET':
            switch (url.parse(req.url).pathname) {
                case '/':
                    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                    res.write(fs.readFileSync('./index.html'));
                    res.end();
                    break;

                // сколько времени сервер будет поддерживать открытым соединение с клиентом после завершения передачи данных
                case '/connection':
                    server.keepAliveTimeout = 10000;
                    res.write(`KeepAliveTimeout: ${server.keepAliveTimeout}`);

                    let set = Number(url.parse(req.url, true).query.set); // забираем сетик
                    if (Number.isInteger(set)) {
                        server.keepAliveTimeout = set;
                        res.write(`\nKeepAliveTimeout after changing: ${server.keepAliveTimeout}`);
                    }
                    setTimeout(() => {
                        console.log(`Closing connection after ${server.keepAliveTimeout} ms`);
                        res.end();
                    }, server.keepAliveTimeout);

                    res.end();
                    res.end();
                    break;

                case '/headers':
                    res.setHeader('CustomHeaderSmelovYdaliNenyznieLabiPzzzzlst', '1');
                    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                    const reqHeaders = JSON.stringify(req.headers, null, 2);
                    const resHeaders = JSON.stringify(res.getHeaders(), null, 2);
                    res.write(`
                            <html>
                                <body>
                                    <h3>Request Headers:</h3><pre>${reqHeaders}</pre>
                                    <h3>Response Headers:</h3><pre>${resHeaders}</pre>
                                    <h3>Custom Header:</h3><pre>CustomHeaderSmelovYdaliNenyznieLabiPzzzzlst: 1</pre>
                                </body>
                            </html>
                        `);
                    res.end();
                    break;


                case '/parameter':
                    let x = parseInt(url.parse(req.url, true).query.x);
                    let y = parseInt(url.parse(req.url, true).query.y);
                    if (Number.isInteger(x) && Number.isInteger(y)) {
                        res.end('x+y=' + (x + y) +
                            '\nx-y=' + (x - y) +
                            '\nx*y=' + (x * y) +
                            '\nx/y=' + (x / y));
                    } else {
                        res.end('Error: values are not integers')
                    }
                    break;

                case '/close':
                    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                    res.end(`<h1>Server will be closed after 10 sec.</h1>`);
                    setTimeout(() => {
                        server.close(() => console.log("Server closed"));
                        process.exit();
                    }, 10000);
                    break;

                case '/socket':
                    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                    res.write(`<h3>ClientAddress = ${req.socket.remoteAddress}</h3>`);
                    res.write(`<h3>ClientPort = ${req.socket.remotePort}</h3>`);
                    res.write(`<h3>ServerAddress =  ${req.socket.localAddress}</h3>`);
                    res.write(`<h3>ServerPort = ${req.socket.localPort}</h3>`);
                    res.end();
                    break;

                case '/req-data':
                    let dataChunks = "";

                    req.on('data', chunk => {
                        console.log(`--------Data chunk available: \n ${chunk} \n\n--------END OF CHUNK\n\n`);
                        dataChunks += chunk;  // Собираем все чанки данных в переменной
                    });

                    req.on('end', () => {
                        console.log('End of chunks');
                        console.log("Full data received:", dataChunks);
                        res.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
                        res.end("Data received successfully.");
                    });
                    break;

                case '/resp-status':
                    let statusCode = parseInt(url.parse(req.url, true).query.code);
                    let mess = url.parse(req.url, true).query.mess;
                    res.setHeader('Content-Type', 'text/html; charset=utf-8');

                    res.statusCode = statusCode;
                    res.statusMessage = mess;
                    res.write(`status code: ${res.statusCode}, status message: ${res.statusMessage}`);
                    res.end();
                    break;

                case '/formparameter':
                    res.write(fs.readFileSync('./formparameter.html'));
                    res.end();
                    break;

                case '/files':
                    fs.readdir("./static", (err, files) => {
                        res.setHeader("X-static-files-count", files.length);
                        res.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
                        res.end(`${files.length}`);
                    });
                    break;

                case '/upload':
                    res.writeHead(200, { "Content-Type": "text/html; charset=utf-8" });
                    res.end(fs.readFileSync("uploadForm.html"));
                    break;

                default:
                    if (/\/parameter\/\w+\/\w+/.test(url.parse(req.url).pathname)) {
                        let chunks = url.parse(req.url).pathname.trim().split('/');
                        let x = parseInt(chunks[2]);
                        let y = parseInt(chunks[3]);
                        if (Number.isInteger(x) && Number.isInteger(y)) {
                            res.end('x+y=' + (x + y) +
                                '\nx-y=' + (x - y) +
                                '\nx*y=' + (x * y) +
                                '\nx/y=' + (x / y));
                        } else {
                            res.write(`URI: ${req.url}`);
                            res.end();
                        }
                    }
                    else if (url.parse(req.url, true).pathname.split("/")[1] == "files") {
                        let result = url.parse(req.url, true).pathname.split("/");
                        fs.access(`./static/${result[2]}`, fs.constants.R_OK, err => {
                            if (err) {
                                res.writeHead(404, { "Content-Type": "text/plain; charset=utf-8" });
                                res.end(`файл ${result[2]} не найден`);
                            } else {
                                res.writeHead(200, { "Content-Type": "application/txt; charset=utf-8" });
                                fs.createReadStream(`./static/${result[2]}`).pipe(res);
                            }
                        });
                    }
                    else {
                        res.statusCode = 405;
                        console.log('Unhandled pathname');
                    }
            }

            break;

        case 'POST':
            switch (url.parse(req.url).pathname) {
                case '/formparameter':

                    let obj = "";
                    req.on("data", data => {
                        obj += data;
                    });
                    req.on("end", () => {
                        let result = qs.parse(obj);
                        res.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
                        res.write(`text: ${result.text}\n`);
                        res.write(`number: ${result.number}\n`);
                        res.write(`date: ${result.date}\n`);
                        res.write(`checkbox: ${result.checkbox}\n`);
                        res.write(`radio: ${result.radio}\n`);
                        res.write(`textarea: ${result.textarea}\n`);
                        res.write(`send: ${result.send}\n`);
                        res.end();
                    });
                    break;

                case '/upload':
                    let form = new mp.Form({ uploadDir: "./static" }); // вот тут библиотека мультипати
                    form.on("field", (name, value) => {
                    });
                    form.on("file", (name, file) => {
                    });

                    form.on("error", (err) => {
                        res.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
                        res.end(`${err}`);
                    });

                    form.on("close", () => {
                        res.writeHead(200, { "Content-Type": "text/plain; charset=utf-8" });
                        res.end("Файл получен");
                    });

                    form.parse(req);
                    break;

                case '/json':
                    let jsonData = "";
                    req.on("data", data => {
                        jsonData += data;
                    });
                    req.on("end", () => {
                        let result = JSON.parse(jsonData);
                        let comment = "Ответ";
                        let sum = result.x + result.y;
                        let concat = `${result.s}: ${result.o.surname}, ${result.o.name}`;
                        let length = result.m.length;
                        res.writeHead(200, { "Content-Type": "text/json; charset=utf-8" });
                        res.end(JSON.stringify(
                            {
                                "__comment": comment,
                                "x_plus_y": sum,
                                "Concatination_s_o": concat,
                                "Length_m": length
                            }
                        ));
                    });
                    break;

                case '/xml':
                    let xmltxt = "";
                    req.on("data", data => {
                        xmltxt += data;
                    });
                    req.on("end", () => {
                        parseString(xmltxt, (err, result) => {
                            if (err) res.end("bad xml");
                            else {
                                res.writeHead(200, { "Content-Type": "text/xml; charset=utf-8" });
                                res.end(xmlbuild(result));
                            }
                        });
                    });
                    break;


                default:
                    res.statusCode = 404;
                    console.log('Unhandled pathname');
            }

            break;

        default:
            console.log('Unhandled method of request');
            res.write('Unhandled method of request');
            break;
    }

});

server.listen(5000, () => {
    console.log('Server started at http://localhost:5000')
});

server.on('connection', () => {
    Console.log(`New connection. KeepAliveTimeout: ${server.keepAliveTimeout}`)
});