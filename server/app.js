const express = require('express');
const sqlite3 = require('sqlite3').verbose();

const app = express();
const db = new sqlite3.Database('db');
const tableName = 'logs';
const dateCol = 'timeLogged';
const enteredCol = 'entered';

const port = 8080;

const server = app.listen(port, () => {
  const sql = `CREATE TABLE IF NOT EXISTS ${tableName}(id INTEGER PRIMARY KEY AUTOINCREMENT, ${dateCol} TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL, ${enteredCol} BOOLEAN NOT NULL)`;
  db.run(sql, () => null);
});

app.post('/client', (req, res) => {
  res.setHeader('Content-Type', 'text/plain');
  res.send('New Client');

  const stmt = db.prepare('INSERT INTO client VALUES (?, ?)');
  stmt.run(1);
  stmt.finalize();
});

app.delete('/client', (req, res) => {
  res.setHeader('Content-Type', 'text/plain');
  res.send('Client gone from the shop');

  const stmt = db.prepare('INSERT INTO client VALUES (?, ?)');
  stmt.run(1);
  stmt.finalize();
});

app.get('/client', (req, res) => {
  db.each('SELECT entry, time FROM client', (err, row) => {
    console.log(`${row.entry}: ${row.time}`);
  });
});

process.on('SIGINT', () => {
  server.close(() => {
    db.close();
  });
});
