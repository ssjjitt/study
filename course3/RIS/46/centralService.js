const express = require("express");
const axios = require("axios");
const db = require("better-sqlite3")("central.db");
const cron = require("node-cron");
const winston = require("winston");
const ntpClient = require("ntp-client");

const app = express();
const port = 4000;

// Список источников данных
const sources = [
  // асинхронный опрос двух веб сервисов источников ТИ, центральным веб сервисом
  {
    name: "source1",
    url: "http://localhost:3001/api/data",
    pushUrl: "http://localhost:3001/api/push",
  },
  {
    name: "source2",
    url: "http://localhost:3002/api/data",
    pushUrl: "http://localhost:3002/api/push",
  },
];


const logger = winston.createLogger({
  level: "info",
  format: winston.format.combine(
    winston.format.timestamp(),
    winston.format.printf(
      ({ timestamp, level, message }) => `${timestamp} [${level}]: ${message}`
    )
  ),
  transports: [
    new winston.transports.Console(),
    new winston.transports.File({ filename: "central.log" }),
  ],
});

// Парсер JSON
app.use(express.json());

// Инициализация базы данных
const initializeDatabase = () => {
  const createTable = `
        CREATE TABLE IF NOT EXISTS received_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            source TEXT,
            timestamp TEXT,
            value REAL
        )
    `;
  db.exec(createTable);
};

// Функция для синхронизации времени с NTP сервером
const synchronizeTime = () => {
  ntpClient.getNetworkTime("pool.ntp.org", 123, (err, date) => {
    if (err) {
      logger.error(`Ошибка синхронизации времени через NTP: ${err.message}`);
      return;
    }
    const localTime = new Date();
    const timeDifference = Math.abs(localTime - date);
    logger.info(
      `Время синхронизировано с NTP. Разница во времени: ${timeDifference} мс`
    );
  });
};

// опрашивает оба источника для получения данных:
cron.schedule("* * * * *", async () => {
  for (const [index, source] of sources.entries()) {
    try {
      const { data } = await axios.get(source.url);
      if (!data?.data) continue;

      // сохраняем данные в базу, если такие записи еще не были добавлены
      data.data.forEach((entry) => {
        const existingEntry = db
          .prepare(
            "SELECT 1 FROM received_data WHERE source = ? AND timestamp = ?"
          )
          .get(source.name, entry.timestamp);

        if (!existingEntry) {
          db.prepare(
            "INSERT INTO received_data (source, timestamp, value) VALUES (?, ?, ?)"
          ).run(source.name, entry.timestamp, entry.value);
        }
      });
      logger.info(
        `[ВЫТЯГИВАНИЕ] Получено ${data.data.length} записей от ${source.name}`
      );
    } catch (error) {
      logger.error(
        `Ошибка при получении данных от ${source.name}: ${error.message}`
      );
    }
  }
});

//  для получения всех данных
app.get("/api/data", (req, res) => {
  const rows = db.prepare("SELECT * FROM received_data").all();
  res.json({ time: new Date(), data: rows });
});

//  для получения статуса данных
app.get("/api/status", (req, res) => {
  const rows = db
    .prepare(
      "SELECT source, COUNT(*) as count FROM received_data GROUP BY source"
    )
    .all();
  res.json(rows);
});

app.get("/api/delete", (req, res) => {
  const { id } = req.query;
  try {
    const result = db.prepare("DELETE FROM received_data WHERE id = ?").run(id);
    res.json({ success: true, message: "Запись удалена" });
    logger.info(`Удалена запись с ID: ${id}`);
  } catch (error) {
    logger.error(`Ошибка при удалении записи: ${error.message}`);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

// Периодическая вставка случайных данных и синхронизация времени с NTP (Выталкивание)
setInterval(async () => {
  const insertData = {
    value: Math.random() * 100,
    timestamp: new Date().toISOString(),
  };

  db.prepare(
    "INSERT INTO received_data (source, timestamp, value) VALUES (?, ?, ?)"
  ).run("central", insertData.timestamp, insertData.value);

  for (const source of sources) {
    try {
      await axios.post(source.pushUrl, { data: insertData });
      logger.info(`[ВЫТАЛКИВАНИЕ] Данные отправлены в ${source.name}`);
    } catch (error) {
      logger.error(
        `Ошибка при отправке данных в ${source.name}: ${error.message}`
      );
    }
  }

  // Синхронизация времени с NTP
  synchronizeTime();
}, 15000);

initializeDatabase();

app.listen(port, () =>
  logger.info(`Центральная бд запущен : http://localhost:${port}`)
);
