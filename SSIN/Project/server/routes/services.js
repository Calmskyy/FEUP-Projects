const Router = require('express-promise-router');
const router = new Router();
const db = require('../db');
const CryptoJS = require("crypto-js"); // Shared AES encryption


const { makeid } = require('./../utils');
const { decryptAES } = require('./../utils');

/**
 * Calculates the nth root of a number.
 */
function nthroot(x, n) {
  if (n === 0) {
    return 1;
  }
  const negate = n % 2 === 1 && x < 0;
  if (negate) {
    x = -x;
  }
  const possible = Math.pow(x, 1 / n);
  n = Math.pow(possible, n);
  if (Math.abs(x - n) < 1 && (x > 0 === n > 0)) {
    return negate ? -possible : possible;
  }
}

/**
 * Gets the user's security clearance level.
 */
async function getSecLevel(username) {
  let secLevel;
  const rec = await new Promise((resolve, reject) => db.findOne({ username: username }, (err, rec) => {
    if (err) {
      reject(err);
    } else {
      resolve(rec);
    }
  }));
  if (rec !== null) {
    secLevel = rec.secLevel;
  }
  return secLevel;
}

/**
 * Computes the square root of a number.
 */
router.post('/squareRoot', async (req, res) => {
  const token = req.body.token;
  const user = JSON.parse(req.app.authTable.get(token));
  
  const content = decryptAES(req.body.encryptedContent, user.sharedKey);
  
  const secLevel = await getSecLevel(user.username);
  if (secLevel === null || !req.app.authTable.get(token)) {
    return res.json({ status: 1, msg: 'Authentication error' });
  }
  
  const newToken = makeid(12);
  req.app.authTable.delete(token);
  req.app.authTable.set(newToken, JSON.stringify({ username: user.username, sharedKey: user.sharedKey}));

  if (secLevel < 1) {
    return res.json({
      status: 2, 
      msg: 'Security level insufficient', 
      encryptedNewToken: 
        CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString()});
  }
  if (content.number < 0) {
    return res.json({ status: 2, 
      msg: 'Cannot calculate the square root of a negative number', 
      encryptedNewToken: 
        CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString()
      });
  }
  const result = Math.sqrt(content.number);
  

  return res.json({ 
    status: 0, 
    encryptedResult: 
      CryptoJS.AES.encrypt(JSON.stringify(result), user.sharedKey).toString(),
    encryptedNewToken: 
      CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString()
  });
});

/**
 * Computes the cubic root of a number.
 */
router.post('/cubicRoot', async (req, res) => {
  const token = req.body.token;
  const user = JSON.parse(req.app.authTable.get(token));
  
  const content = decryptAES(req.body.encryptedContent, user.sharedKey);
  
  const secLevel = await getSecLevel(user.username);
  if (secLevel === null || !req.app.authTable.get(token)) {
    return res.json({ status: 1, msg: 'Authentication error' });
  }
  
  const newToken = makeid(12);
  req.app.authTable.delete(token);
  req.app.authTable.set(newToken, JSON.stringify({ username: user.username, sharedKey: user.sharedKey}));

  if (secLevel < 2) {
    return res.json({
      status: 2, 
      msg: 'Security level insufficient', 
      encryptedNewToken: 
        CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString()});
  }
  
  const result = Math.cbrt(content.number);
  

  return res.json({ 
    status: 0, 
    encryptedResult: 
      CryptoJS.AES.encrypt(JSON.stringify(result), user.sharedKey).toString(),
    encryptedNewToken: 
      CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString()
  });
});

/**
 * Computes the nth root of a number.
 */
router.post('/nRoot', async (req, res) => {
  const token = req.body.token;
  const user = JSON.parse(req.app.authTable.get(token));

  const content = decryptAES(req.body.encryptedContent, user.sharedKey);

  const secLevel = await getSecLevel(user.username);
  if (secLevel === null || !req.app.authTable.get(token)) {
    return res.json({ status: 1, msg: 'Authentication error' });
  }

  const newToken = makeid(12);
  req.app.authTable.delete(token);
  req.app.authTable.set(newToken, JSON.stringify({ username: user.username, sharedKey: user.sharedKey}));

  if (secLevel < 3) {
    return res.json({ status: 2, 
      msg: 'Security level insufficient', 
      encryptedNewToken: 
        CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString() });
  }
  const result = nthroot(content.number, parseFloat(content.n));
  if (result === undefined) {
    return res.json({ 
      status: 2, 
      msg: 'n root of negative bases can only be calculated with odd positive exponents', 
      encryptedNewToken: 
        CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString() 
    });
  }
  return res.json({ 
    status: 0, 
    encryptedResult: 
      CryptoJS.AES.encrypt(JSON.stringify(result), user.sharedKey).toString(), 
    encryptedNewToken: 
      CryptoJS.AES.encrypt(JSON.stringify(newToken), user.sharedKey).toString() });
});

module.exports = router;
