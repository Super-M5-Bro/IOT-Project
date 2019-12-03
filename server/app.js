const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const cors = require('cors');

const app = express();
const db = new sqlite3.Database('db');
const tableName = 'logs';
const dateCol = 'timeLogged';
const enteredCol = 'entered';

const port = 8081;

app.use(cors());

const server = app.listen(port, () => {
  const sql = `CREATE TABLE IF NOT EXISTS ${tableName}(id INTEGER PRIMARY KEY AUTOINCREMENT, ${dateCol} TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL, ${enteredCol} BOOLEAN NOT NULL)`;
  db.run(sql, () => null);
});

app.post('/client/enter', (req, res) => {
  db.run(`INSERT INTO ${tableName}(${enteredCol}) VALUES(?)`, 1);
  res.status(200);
  res.send();
});

app.post('/client/leave', (req, res) => {
  db.run(`INSERT INTO ${tableName}(${enteredCol}) VALUES(?)`, 0);
  res.status(200);
  res.send();
});

app.get('/client', (req, res) => {
  db.get(`SELECT COUNT(*) AS left, (SELECT COUNT(*) as entered FROM ${tableName} WHERE ${enteredCol} = 1) AS entered FROM ${tableName} WHERE ${enteredCol} = 0`, (err, row) => {
    if (err !== null) res.sendStatus(500);
    const current = row.entered - row.left;
    const inDates = [];
    const outDates = [];
    db.each(`SELECT entered, DATETIME(timeLogged, 'LOCALTIME') AS timeLogged FROM ${tableName} WHERE ${dateCol} >= date('now', 'start of day', 'localtime')`, (err2, row2) => {
      if (row2.entered) {
        inDates.push(row2.timeLogged);
      } else {
        outDates.push(row2.timeLogged);
      }
    }, () => {
      res.status(200);
      res.json({ in_today: inDates, out_today: outDates, current });
    });
  });
});

app.get('/client/m5', (req, res) => {
  db.get(`SELECT COUNT(*) AS left, (SELECT COUNT(*) as entered FROM ${tableName} WHERE ${enteredCol} = 1) AS entered FROM ${tableName} WHERE ${enteredCol} = 0`, (err, row) => {
    if (err !== null) res.sendStatus(500);
    const current = row.entered - row.left;
    res.status(200);
    res.send(`${current}`);
  });
});

process.on('SIGINT', () => {
  server.close(() => {
    db.close();
  });
});
