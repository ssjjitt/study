const http = require('http');
const fs = require('fs');
const url = require('url');
const { parse } = require('querystring');
const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
    host: 'smtp.gmail.com',
    port: 587,
    secure: false,
    auth: {
        user: 'ssjjitt@gmail.com',
        pass: 'zeqh zgyf touq vzcm'
    }
});

http.createServer((req, resp) => {
    const pathname = url.parse(req.url).pathname;
    resp.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });

    if (pathname === '/' && req.method === 'GET') {
        fs.readFile('./index.html', (err, data) => {
            if (err) {
                console.error('Форма не загрузилась:', err);
            } else {
                resp.end(data);
            }
        });
    } else if (pathname === '/' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            const {
                from,
                to,
                message
            } = parse(body);

            if (!from || !to || !message) {
                resp.end('<h1>Все поля должны быть заполнены!</h1>');
                return;
            }

            /*
            sendmail({
                from: params.sender,
                to: params.receiver,
                subject: 'New Message',
                text: params.message
            }
            */

            transporter.sendMail({
                from: 'ssjjitt@gmail.com',
                to: to,
                subject: 'СТРВП-6',
                text: message
            }, (smtpErr, info) => {
                if (smtpErr) {
                    console.error('Ошибка отправки через nodemailer:', smtpErr);
                } else {
                    resp.end('<h1>Сообщение успешно отправлено!</h1>');
                }
            });
        });
    } else {
        resp.end('<h1>Not supported</h1>');
    }
}).listen(5001, () => console.log('Server running at http://localhost:5001/'));