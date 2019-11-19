const express = require('express');

const app = express();

const port = 8080

app.get('/', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('Home Api Page');
});

app.get('/client/new', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('New Client');
});

app.get('/client/delete', function(req, res) {
    res.setHeader('Content-Type', 'text/plain');
    res.send('Client gone from the shop');
});

app.listen(port);
