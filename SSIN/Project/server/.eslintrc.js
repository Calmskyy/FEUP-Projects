module.exports = {
  'env': {
    'browser': true,
    'commonjs': true,
    'es2020': true
  },
  'extends': 'eslint:recommended',
  'parserOptions': {
    'ecmaVersion': 11
  },
  'globals': {
    'process': true,
    '__dirname': true,
  },
  'rules': {
    // Best practices
    'curly': ['error', 'all'],
    'eqeqeq': ['error', 'always'],
    'no-multi-spaces': 'error',
    'no-useless-return': 'error',
    'no-use-before-define': 'warn',
    'linebreak-style': ['error', 'unix'],

    // Stylistic issues
    'array-bracket-newline': ['error', { 'multiline': true }],
    'array-bracket-spacing': ['error', 'never'],
    'block-spacing': 'error',
    'brace-style': ['error', '1tbs'],
    'camelcase': ['error', { 'properties': 'never' }],
    'comma-dangle': ['error', 'only-multiline'],
    'comma-spacing': ['error', { 'before': false, 'after': true }],
    'comma-style': ['error', 'last'],
    'indent': ['error', 2, { 'SwitchCase': 1 }],
    'jsx-quotes': ['error', 'prefer-double'],
    'key-spacing': ['error', { 'beforeColon': false, 'afterColon': true }],
    'keyword-spacing': ['error', { 'before': true, 'after': true }],
    'no-trailing-spaces': 'error',
    'prefer-arrow-callback': ['error'],
    'quotes': ['error', 'single'],
    'semi': ['error', 'always'],

    // ECMAScript 6
    'no-duplicate-imports': 'error',
    'no-var': 'error',
    'prefer-const': 'error',
  }
};
