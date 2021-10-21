const express = require('express');
const bcrypt = require('bcrypt');

const { decrypt, decryptAES } = require('./../utils');
const { makeid } = require('./../utils');

const router = express.Router();
 
/**
 * Replies with a public key.
 * TODO: don't use always the same?
 */
router.get('/publicKeyRSARequest', (req, res) => {
  return res.json({
    status: 0,
    publicKey: req.app.publicKey
  });
});

/**
 * Encrypts a shared key.
 * TODO: save in DB for user
 */
router.post('/encryptSharedKey', (req, res) => {
  req.app.sharedKey = decrypt(req.body.encryptSharedKey, req.app.privateKey);
  // sharedKey = decrypt(req.body.encryptSharedKey, req.app.privateKey);
  // console.log("Shared key: " + req.app.sharedKey)
  return res.json({ status: 0 });
});

/**
 * Register a user session.
 * TODO: send back an OTP for next request
 */
router.post('/register', (req, res) => {

  content = decryptAES(req.body.encryptedContent, req.app.sharedKey);

  // Check if username exists
  req.app.db.findOne({ username: content.username }, (err, doc) => {

    if (doc === null) {
      res.send({ status: 2 }).end();
      return;
    }

    // Check if oneTimeID matches
    const salt = doc.salt;
    const hash = bcrypt.hashSync(content.oneTimeID, salt);
    var token = makeid(12);
    var exists = 0;

    if (hash === doc.hashedOneTimeID) {
      for (let [key, value] of req.app.authTable.entries()) {
        if(JSON.parse(value).username == content.username)
        {
          token = key;
          exists = 1;
        }
      }
  
      if(!exists)
        req.app.authTable.set(token, JSON.stringify({ username: content.username, sharedKey: req.app.sharedKey}));

      return res.send({ status: 0, token: token}).end();
    } else {
      return res.send({ status: 2 }).end();
    }
  });
});

router.post('/logout', (req,res) => {
  const token = req.body.token;
  const user = JSON.parse(req.app.authTable.get(token));
  const username = user.username;

  req.app.db.findOne({ username: username }, (err, doc) => {
    if (doc === null) {
      res.send({ status: 2 }).end();
      return;
    }
  if(req.app.authTable.get(token)){
    req.app.authTable.delete(token);
    return res.send({status: 0});
  } else {
    return res.send({ status: 2 }).end();
  }
  });
});

module.exports = router;
