let fs = require('fs');
let path = require('path');

function Stat(sfn = './static') {

    this.STATIC_FOLDER = sfn;

    let pathStatic = (fn) => {
        return path.join(this.STATIC_FOLDER, fn);
    }

    this.writeHTTP404 = (res) => {
        res.statusCode = 404;
        res.statusMessage = '404 Not Found';
        res.end('Not Found');
    }

    
    let pipeFile = (req, res, headers) => { 
        res.writeHead(200, headers);
        fs.createReadStream(pathStatic(req.url)).pipe(res); // поток для чтения файла, путь до файла, pipe проталкивает результат в res
    }

    this.isStatic = (extension, fn) => {
        let reg = new RegExp(`^\/.+\.${extension}$`);
        return reg.test(fn);
    }

    this.sendFile = (req, res, headers) => {
        fs.access(pathStatic(req.url), fs.constants.R_OK, err => {
            if (err) {
                this.writeHTTP404(res);
            } else {
                const extension = path.extname(req.url).toLowerCase();
                const filename = path.basename(req.url);
                if (extension !== '.json' && extension !== '.xml' && filename !== 'client.html') {
                    headers['Content-Disposition'] = 'attachment; filename="' + path.basename(req.url) + '"'; // если не будет этого говна то браузер будет интерпретировать html, css и прочее и открывать его тупо во вкладке, как делает это с json
                }
                pipeFile(req, res, headers); // отправка конечная
            }
        });
    }
};

module.exports = (parm) => { return new Stat(parm); }