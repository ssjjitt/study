const fs = require('fs');
const { performance } = require('perf_hooks');

function rc4(key, data) {
  const S = [];
  const K = [];
  const n = 8;

  for (let i = 0; i < n; i++) {
    S[i] = i;
    K[i] = key[i % key.length];
  }
  // KSA — Key Scheduling Algorithm
  let j = 0;
  for (let i = 0; i < n; i++) {
    j = (j + S[i] + K[i]) % n;
    [S[i], S[j]] = [S[j], S[i]];
  }
  // PRGA — Pseudo-Random Generation Algorithm
  let i = 0;
  j = 0;
  const result = [];

  for (let x = 0; x < data.length; x++) {
    i = (i + 1) % n;
    j = (j + S[i]) % n;
    [S[i], S[j]] = [S[j], S[i]];
    const K = S[(S[i] + S[j]) % n];
    result.push(data[x] ^ K);
  }

  return Buffer.from(result);
}

const key = [76, 111, 85, 54, 211];

const inputText = fs.readFileSync('input.txt');

const t0 = performance.now();
const encrypted = rc4(key, inputText);
const t1 = performance.now();
console.log(`Время генерации и шифрования: ${(t1 - t0).toFixed(3)} мс`);

fs.writeFileSync('encrypted.txt', encrypted);

const decrypted = rc4(key, encrypted);
fs.writeFileSync('decrypted.txt', decrypted);

console.log('Шифрование и расшифровка завершены.');
