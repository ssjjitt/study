const nodemailer = require("nodemailer");
const gmail = 'ssjjitt@gmail.com';
const password = 'zeqh zgyf touq vzcm';

const transporter = nodemailer.createTransport({
    host: 'smtp.gmail.com',
    port: 587,
    secure: false,
    auth: {
        user: gmail,
        pass: password
    }
});

function send(email) {
    transporter.sendMail({
        from: 'ssjjitt@gmail.com',
        to: gmail,
        subject: 'СТРВП-6',
        text: email
    }, (smtpErr, info) => {
        if (smtpErr) {
            console.error('Ошибка отправки через nodemailer:', smtpErr);
        } else {
            console.log('Сообщение успешно отправлено!');
        }
    });
    return email.toString();
}

exports.send = send;