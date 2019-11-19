const express = require('express');
const sqlite3 = require('sqlite3').verbose();

const app = express();
const db = new sqlite3.Database(':memory:');

const port = 8080

app.get('/', function (req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('Home Api Page');
});

app.get('/client/new', function (req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('New Client');

    const stmt = db.prepare("INSERT INTO client VALUES (?, ?)");
    stmt.run(1);
    stmt.finalize();

});

app.get('/client/delete', function (req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('Client gone from the shop');

    const stmt = db.prepare("INSERT INTO client VALUES (?, ?)");
    stmt.run(1);
    stmt.finalize();
});

app.get('/client/current', function (req, res) {

    db.each("SELECT entry, time FROM client", function (err, row) {
        console.log(row.entry + ": " + row.time);
    });

});

app.get('/create', function (req, res) {

    // Check if the database is already created
    db.get("SELECT name FROM sqlite_master WHERE type='table' AND name='{client}'", function (err, row) {
        
        console.log(row)

        // If we have no result, we create the table
        if (row == undefined) {
            db.run("CREATE TABLE client (entry BOOLEAN, time TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL)");
            console.log("Create")
        } else {
            console.log("Manage")
        }
    });
    

    res.setHeader('Content-Type', 'text/plain');
    res.send('Creation of the database');
    
});

app.listen(port);

// Close the database
//db.close();