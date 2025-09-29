const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');

const app = express();
const PORT = 3000;
const SECRET = 'supersecretkey';

app.use(bodyParser.json());

const users = {
  user1: { id: '1', username: 'user1', email: 'user1@example.com' },
  user2: { id: '2', username: 'user2', email: 'user2@example.com' },
};

app.post('/login', (req, res) => {
  const { username } = req.body;
  const user = users[username];
  if (!user) return res.status(404).json({ message: 'User not found' });

  const token = jwt.sign({ id: user.id, username: user.username }, SECRET, { expiresIn: '1h' });
  res.json({ token });
});

function authenticateToken(req, res, next) {
  const authHeader = req.headers['authorization'];
  const token = authHeader?.split(' ')[1];

  if (!token) return res.status(403).json({ message: 'Без токена' });

  jwt.verify(token, SECRET, (err, user) => {
    if (err) return res.status(403).json({ message: 'Невалидный токен' });
    req.user = user;
    next();
  });
}

app.get('/users/:id', authenticateToken, (req, res) => {
  const { id } = req.params;

  if (req.user.id !== id) {
    return res.status(403).json({ message: 'Доступ запрещен для этого юзера' });
  }

  const userData = Object.values(users).find(u => u.id === id);
  if (!userData) return res.status(404).json({ message: 'Юзер не найден' });

  res.json(userData);
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});

module.exports = app;
