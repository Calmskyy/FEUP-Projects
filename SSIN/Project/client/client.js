const axios = require("axios");
const crypto = require("crypto");
const CryptoJS = require("crypto-js"); // Shared AES encryption
const { exit } = require("process");
const { promisify } = require("util");
const exec = promisify(require("child_process").exec);
const rl = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Global variables
var sharedKey;
var username;
var oneTimeID;
var token;

const askUsername = () => {
  return new Promise((resolve, reject) => {
    rl.question("Insert username\n", (username) => {
      console.log("\n");
      resolve(username);
    });
  });
};

const askOneTimeID = () => {
  return new Promise((resolve, reject) => {
    rl.question("Insert One Time ID\n", (oneTimeID) => {
      console.log("\n");
      resolve(oneTimeID);
    });
  });
};

const handleRegistration = async () => {
  // Ask username and onetime ID
  username = await askUsername();
  oneTimeID = await askOneTimeID();

  // console.log("\033[2J");

  var content = JSON.stringify({
    username: username,
    oneTimeID: oneTimeID,
  });

  response = await sendPost(
    content,
    "",
    "/security/register",
    "Registration succeeded",
    "Registration failed: wrong username and One Time ID combination"
  );
  if (response.data.status == 1 || response.data.status == 2) {return 1};
  token = response.data.token;
  return 0;
};

/**
 * Returns stdout of a bash command
 * Only works in UNIX-based systems
 * stderr is not being handled, beware
 * @param string command
 * @returns stdout
 */
async function getCommandOutput(command) {
  const output = await exec(command);
  return output.stdout;
}

async function serverConnectionSetup() {
  consoleWarning("Connecting to the server");
  let publicKey = await getRSAPublicKey();

  // Generate shared key
  sharedKey = await getCommandOutput("dd if=/dev/urandom bs=128 count=1");
 
  // encrypt gerenated key with RSA public key
  let encryptSharedKey = encryptRSA(sharedKey, publicKey);

  // send
  consoleWarning("Sending generated shared key");
  var content = JSON.stringify({
    encryptSharedKey,
  });
  
  var config = {
    method: "post",
    url: "http://localhost:3000/security/encryptSharedKey",
    headers: {
      "Content-Type": "application/json",
    },
    data: content
  };

  await axios(config);
}

/**
 * Sends POST with content in JSON format.
 * Sends content in JSON format
 * @param string contentToSendJSON
 * @param string endpoint
 * @param string successMsg, not required
 * @param string errorMsg, , not required
 * @returns 0: success, 1: error, 2: context error
 */
async function sendPost(contentToSendJSON, token, endpoint, successMsg, errorMsg) {
  var config = {
    method: "post",
    url: "http://localhost:3000" + endpoint,
    headers: {
      "Content-Type": "application/json",
    },
    data: JSON.stringify({ encryptedContent: 
      CryptoJS.AES.encrypt(contentToSendJSON, sharedKey).toString(),
      token }),
  };

  let response = await axios(config);

  if (successMsg != null && errorMsg != null)
    switch (response.data.status) {
      case 0:
        consoleSuccess(successMsg);
        break;
      case 1:
        consoleError(errorMsg);
        break;
      case 2:
        consoleError(errorMsg);
        break;
      default:
        console.log("Unhandled code:", response.data.status);
    }

  return response;
}

/**
 * Encrypts a string with RSA public key
 * @param string toEncrypt
 * @param string publicKey
 * @returns Encrypted string
 */
function encryptRSA(toEncrypt, publicKey) {
  // const absolutePath = path.resolve(relativeOrAbsolutePathToPublicKey);
  // const publicKey = fs.readFileSync(absolutePath, "utf8");
  const buffer = Buffer.from(toEncrypt, "utf8");
  const encrypted = crypto.publicEncrypt(publicKey, buffer);

  return encrypted.toString("base64");
}

async function getRSAPublicKey() {
  let config = {
    method: "get",
    url: "http://localhost:3000/security/publicKeyRSARequest",
    headers: {},
  };

  let response = await axios(config);

  if (response.status == 200) {
    consoleSuccess("200 Receiving RSA public key");
    return response.data.publicKey;
  } else console.log("Error fetching RSA public key");
}

function consoleSuccess(msg) {
  console.log("\033[1;32m" + msg + "\033[0m");
}

function consoleWarning(msg) {
  console.log("\033[1;33m" + msg + "\033[0m");
}

function consoleError(msg) {
  console.log("\033[1;31m" + msg + "\033[0m");
}

const handleMenu = async () => {
  const askService = () => {
    console.log("1. Calculate square root");
    console.log("2. Calculate cubic root");
    console.log("3. Calculate n root");
    console.log("4. Logout");
    console.log("\n");

    return new Promise((resolve, reject) => {
      rl.question("Select service\n", (serviceNum) => {
        resolve(serviceNum);
      });
    });
  };

  const askNumber = () => {
    return new Promise((resolve, reject) => {
      rl.question("Enter a number\n", (number) => {
        resolve(number);
      });
    });
  };

  const askN = () => {
    return new Promise((resolve, reject) => {
      rl.question("Enter a n root\n", (n) => {
        resolve(n);
      });
    });
  };

  const serviceNum = await askService();
  const numberReg = /^-?\d+\.?\d*$/;

  switch (serviceNum) {
    case "1":
      number = await askNumber();
      while (!(numberReg.test(number) && Number.isFinite(parseFloat(number)))) {
        console.log("\033[1;31m" + 'Input is not a number\n' + "\033[0m");
        number = await askNumber();
      }
      response = await sendPost(
        JSON.stringify({ number }),
        token,
        "/services/squareRoot"
      );
      if (response.data.status == 0)
      {

        consoleSuccess("Result: " + decryptAES(response.data.encryptedResult, sharedKey));
        token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      else {
        consoleError("Error: " + response.data.msg);
        if (response.data.status == 2)
          token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      await handleMenu();
      break;
    case "2":
      number = await askNumber();
      while (!(numberReg.test(number) && Number.isFinite(parseFloat(number)))) {
        console.log("\033[1;31m" + 'Input is not a number\n' + "\033[0m");
        number = await askNumber();
      }
      response = await sendPost(
        JSON.stringify({ number }),
        token,
        "/services/cubicRoot"
      );
      if (response.data.status == 0)
      {
        consoleSuccess("Result: " + decryptAES(response.data.encryptedResult, sharedKey));
        token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      else {
        consoleError("Error: " + response.data.msg);
        if (response.data.status == 2)
          token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      await handleMenu();
      break;
    case "3":
      number = await askNumber();
      while (!(numberReg.test(number) && Number.isFinite(parseFloat(number)))) {
        console.log("\033[1;31m" + 'Input is not a number\n' + "\033[0m");
        number = await askNumber();
      }
      n = await askN();
      while (!(numberReg.test(n) && Number.isFinite(parseFloat(n)))) {
        console.log("\033[1;31m" + 'Input is not a number\n' + "\033[0m");
        n = await askN();
      }
      response = await sendPost(
        JSON.stringify({ number, n }),
        token,
        "/services/nRoot"
      );
      if (response.data.status == 0)
      {
        consoleSuccess("Result: " + decryptAES(response.data.encryptedResult, sharedKey));
        token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      else {
        consoleError("Error: " + response.data.msg);
        if (response.data.status == 2)
          token = decryptAES(response.data.encryptedNewToken, sharedKey);
      }
      await handleMenu();
      break;
    case '4':
      response = await sendPost(
        "",
        token,
        "/security/logout"
      );
      if (response.data.status == 0)
      {
        consoleSuccess("Logged out successfully!");
      }
      else
        consoleError("Unexpected logout error!");
      exit();
    case '5':
      // TODO: initiate p2p messaging
      break;
    default:
      console.log("\033[2J");
      consoleWarning("Option " + serviceNum + " does not exist!\n");
      await handleMenu();
  }
};

const decryptAES = (ciphertext, sharedKey) => {
  let bytes  = CryptoJS.AES.decrypt(ciphertext, sharedKey);
  let content = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
  return content;
}


/* ------ MAIN ------- */
const main = async () => {
  console.log("\033[2J");
  await serverConnectionSetup();

  while ((await handleRegistration()) != 0);

  await handleMenu();
};

main();
