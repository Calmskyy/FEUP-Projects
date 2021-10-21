const app = require("./app");
const bcrypt = require("bcrypt");

const db = require("./db");
const { makeid } = require('./utils');

const rl = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Global variables
let sharedKey;
console.log(sharedKey);

console.log("\033[2J");
console.log(
  `

      ╔═══╗╔═══╗╔══╗╔═╗ ╔╗    ╔═══╗                   ╔╗
      ║╔═╗║║╔═╗║╚╣╠╝║║╚╗║║    ║╔═╗║        ╔╗        ╔╝╚╗
      ║╚══╗║╚══╗ ║║ ║╔╗╚╝║    ║╚═╝║╔═╗╔══╗ ╚╝╔══╗╔══╗╚╗╔╝
      ╚══╗║╚══╗║ ║║ ║║╚╗║║    ║╔══╝║╔╝║╔╗║ ╔╗║╔╗║║╔═╝ ║║
      ║╚═╝║║╚═╝║╔╣╠╗║║ ║║║    ║║   ║║ ║╚╝║ ║║║║═╣║╚═╗ ║╚╗
      ╚═══╝╚═══╝╚══╝╚╝ ╚═╝    ╚╝   ╚╝ ╚══╝ ║║╚══╝╚══╝ ╚═╝
                                          ╔╝║
                                          ╚═╝


`
);

const question1 = () => {
  return new Promise((resolve) => {
    rl.question("Insert full name\n", (fullName) => {
      // console.log("\033[2J");
      console.log(`Hey there ${fullName}!`);
      resolve(fullName);
    });
  });
};

const question2 = () => {
  return new Promise((resolve) => {
    rl.question("Insert security clearance level\n", (secLevel) => {
      resolve(secLevel);
    });
  });
};

const consoleError = (msg) => {
  console.log("\033[1;31m" + msg + "\033[0m");
};

const handlerFaceRegistration = async () => {
  await sleep(10)

  // Face to face registration, ask full name and sec level
  const q1 = await question1();
  q2 = await question2();
  numberReg = /^-?\d+\.?\d*$/;
  while (!(numberReg.test(q2) && Number.isInteger(parseFloat(q2)))) {
    consoleError('Security clearance level must be an integer');
    q2 = await question2();
  }
  q2 = Math.round(q2).toString();
  const oneTimeID = makeid(12).toLowerCase();
  const salt = bcrypt.genSaltSync(10);
  const hashedOneTimeID = bcrypt.hashSync(oneTimeID, salt);

  console.log("\033[2J");

  // Generate a username
  const username = q1.replace(/\s/g, "").toLowerCase();

  function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }

  const user = {
    username: username,
    secLevel: q2,
    hashedOneTimeID: hashedOneTimeID,
    salt: salt,
  };

  // Check if username exists
  await db.findOne({ username }, async (err, doc) => {
    if (doc != null) {
      consoleError("Username already exists!");
      return 0;
    }
    else {
      console.log("Username: ", username);
      console.log("One Time ID: ", oneTimeID);
      console.log("Security Level: ", q2);
      console.log("\n");
      db.insert(user, () => {});
    }
  });

  // rl.close();

  return 0;
};

/* ------ MAIN ------- */
const main = async () => {
  while ((await handlerFaceRegistration()) == 0);
};

app.listen(3000, () => {
  //console.log(`Listening at http://localhost:${port}`);
});

main();
