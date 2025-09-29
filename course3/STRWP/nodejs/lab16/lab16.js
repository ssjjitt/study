import fetch from 'node-fetch';

import express from 'express';

const app = express();
const PORT = process.env.PORT || 3000;

const TELEGRAM_API_URL = 'https://api.telegram.org/bot7798847789:AAE9VGOaXQx77YjlHF7wAG1poqUHJizN_F8'; 
const LONG_POLL_URL = `${TELEGRAM_API_URL}/getUpdates`;

let lastUpdateId = 0;

const handleUpdate = (update) => {
    const message = update.message;
    if (message) {
        const chatId = message.chat.id;
        const text = message.text;

        sendMessage(chatId, `echo: ${text}`);
    }
};

const sendMessage = (chatId, text) => {
    const url = `${TELEGRAM_API_URL}/sendMessage?chat_id=${chatId}&text=${encodeURIComponent(text)}`;
    fetch(url).catch(err => console.error('Error sending message: ', err));
};

const longPoll = () => {
    fetch(`${LONG_POLL_URL}?offset=${lastUpdateId + 1}&timeout=60`)
        .then(response => response.json())
        .then(data => {
            if (data.result && data.result.length > 0) {
                data.result.forEach(update => {
                    lastUpdateId = update.update_id;
                    handleUpdate(update);
                });
            }
        })
        .catch(err => console.error('Error getting updates: ', err));

    setTimeout(longPoll, 1000);
};

longPoll();

app.get('/', (req, res) => {
    res.send('Telegram bot is running...');
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
