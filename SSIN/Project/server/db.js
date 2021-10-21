const Datastore = require('nedb');

const db = new Datastore({
  filename: 'db/users.db',
  autoload: true,
  corruptAlertThreshold: 1,
});

module.exports = db;
