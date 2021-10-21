const express = require('express');

const securityRouter = require('./routes/security');
const servicesRouter = require('./routes/services');
const { generateKeyPair } = require('./utils');

const app = express();

/* Globals */
app.db = require('./db.js');
app.sharedKey = null; // TODO: save in DB for each user
app.authTable = new Map();
const { publicKey, privateKey } = generateKeyPair();
app.publicKey = publicKey;
app.privateKey = privateKey;

/* Middlewares */
app.use(express.json());

app.use('/security', securityRouter);
app.use('/services', servicesRouter);

module.exports = app;
