const Buffer = require('buffer').Buffer;
const CryptoJS = require("crypto-js"); // Shared AES encryption

const { generateKeyPairSync, privateDecrypt } = require('crypto');

const decryptAES = (ciphertext, sharedKey) => {
  let bytes  = CryptoJS.AES.decrypt(ciphertext, sharedKey);
  let content = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
  return content;
}

const decrypt = (toDecrypt, privateKey) => {
  // const absolutePath = path.resolve(relativeOrAbsolutePathtoPrivateKey);
  // const privateKey = fs.readFileSync(absolutePath, 'utf8');
  const buffer = Buffer.from(toDecrypt, 'base64');
  const decrypted = privateDecrypt(
    {
      key: privateKey.toString(),
      passphrase: '',
    },
    buffer
  );
  return decrypted.toString('utf8');
};

/**
 * Generates a new RSA key pair.
 */
const generateKeyPair = () => {
  return generateKeyPairSync('rsa', {
    modulusLength: 4096,
    publicKeyEncoding: {
      type: 'pkcs1',
      format: 'pem',
    },
    privateKeyEncoding: {
      type: 'pkcs1',
      format: 'pem',
      cipher: 'aes-256-cbc',
      passphrase: '',
    },
  });
};

const consoleSuccess = (msg) => {
  console.log("\033[1;32m" + msg + "\033[0m");
};

const consoleWarning = (msg) => {
  console.log("\033[1;33m" + msg + "\033[0m");
};

const consoleError = (msg) => {
  console.log("\033[1;31m" + msg + "\033[0m");
};

const makeid = (length) => {
  const result = [];
  const characters =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  const charactersLength = characters.length;
  for (let i = 0; i < length; i++) {
    result.push(
      characters.charAt(Math.floor(Math.random() * charactersLength))
    );
  }
  return result.join("");
};

module.exports = {
  decryptAES,
  decrypt,
  generateKeyPair,
  consoleSuccess,
  consoleWarning,
  consoleError,
  makeid
};
