const CryptoJS = require('crypto-js');
const pako = require('pako');

function normalizeKeyTo8Bytes(keyStr) {
  let k = keyStr || "";
  if (k.length > 8) k = k.slice(0, 8);
  while (k.length < 8) k += '\0';
  return k;
}

function base64ToBytes(base64) {
  const parsed = CryptoJS.enc.Base64.parse(base64);
  const hex = parsed.toString(CryptoJS.enc.Hex);
  const bytes = [];
  for (let i = 0; i < hex.length; i += 2)
    bytes.push(parseInt(hex.substr(i, 2), 16));
  return bytes;
}
function bytesToBase64(bytes) {
  const wordArray = CryptoJS.lib.WordArray.create(Uint8Array.from(bytes));
  return CryptoJS.enc.Base64.stringify(wordArray);
}
function hexToBin(hex) {
  return hex.split('').map(h => parseInt(h,16).toString(2).padStart(4,'0')).join('');
}
function countDifferentBitsHex(hexA, hexB) {
  const a = hexToBin(hexA);
  const b = hexToBin(hexB);
  const n = Math.min(a.length, b.length);
  let cnt = 0;
  for (let i=0;i<n;i++) if (a[i] !== b[i]) cnt++;
  return cnt + Math.abs(a.length - b.length);
}

function desEncryptToNumbers(plainStr, key8) {
  const key = CryptoJS.enc.Utf8.parse(key8);
  const encrypted = CryptoJS.DES.encrypt(plainStr, key, { mode: CryptoJS.mode.ECB, padding: CryptoJS.pad.Pkcs7 });
  const bytes = base64ToBytes(encrypted.toString());
  return bytes.join(', ');
}
function desDecryptFromNumbers(numbersStr, key8) {
  const nums = numbersStr.split(',')
    .map(s => parseInt(s.trim()))
    .filter(n => !isNaN(n) && n >= 0 && n <= 255);
  const cipherBase64 = bytesToBase64(nums);
  const key = CryptoJS.enc.Utf8.parse(key8);
  const decrypted = CryptoJS.DES.decrypt(cipherBase64, key, { mode: CryptoJS.mode.ECB, padding: CryptoJS.pad.Pkcs7 });
  return decrypted.toString(CryptoJS.enc.Utf8);
}

const DES_WEAK_KEYS = [
  "0101010101010101",
  "FEFEFEFEFEFEFEFE",
  "E0E0E0E0F1F1F1F1",
  "1F1F1F1F0E0E0E0E"
];
const DES_SEMIWEAK_PAIRS = [
  ["011F011F010E010E","1F011F010E010E01"],
  ["01E001E001F101F1","E001E001F101F101"],
  ["01FE01FE01FE01FE","FE01FE01FE01FE01"],
  ["1FE01FE00EF10EF1","E01FE01FF10EF10E"],
  ["1FFE1FFE0EFE0EFE","FE1FFE1FFE0EFE0E"],
  ["E0FEE0FEF1FEF1FE","FEE0FEE0FEF1FEF1"]
];

function flipBitIn8ByteString(str8, bitIndex) {
  let bytes = Buffer.from(str8, 'utf8').slice(0,8);
  while (bytes.length < 8) bytes = Buffer.concat([bytes, Buffer.from([0])]);
  const byteIndex = Math.floor(bitIndex / 8);
  const bitInByte = 7 - (bitIndex % 8);
  const cloned = Uint8Array.from(bytes);
  cloned[byteIndex] ^= (1 << bitInByte);
  return Buffer.from(cloned).toString('latin1');
}

const plaintextEl = document.getElementById('plaintext');
const keyInputEl = document.getElementById('keyInput');
const encryptBtn = document.getElementById('encryptBtn');
const decryptBtn = document.getElementById('decryptBtn');
const cipherTextEl = document.getElementById('cipherText');
const decryptedTextEl = document.getElementById('decryptedText');
const encryptTimeEl = document.getElementById('encryptTime');
const decryptTimeEl = document.getElementById('decryptTime');
const compressBtn = document.getElementById('compressBtn');
const compressResult = document.getElementById('compressResult');
const checkWeakBtn = document.getElementById('checkWeakBtn');
const weakResult = document.getElementById('weakResult');
const avalancheBtn = document.getElementById('avalancheBtn');
const avalancheResult = document.getElementById('avalancheResult');
const avalancheTable = document.querySelector('#avalancheTable tbody');
const logOutput = document.getElementById('logOutput');

function log(msg) { logOutput.innerText += msg + '\n'; logOutput.scrollTop = logOutput.scrollHeight; }

encryptBtn.addEventListener('click', () => {
  try {
    const keyStr = normalizeKeyTo8Bytes(keyInputEl.value);
    const pt = plaintextEl.value;
    const start = performance.now();
    const result = desEncryptToNumbers(pt, keyStr);
    const end = performance.now();
    cipherTextEl.innerText = result;
    encryptTimeEl.innerText = (end - start).toFixed(2) + ' ms';
    log('Encrypted.');
  } catch (e) { log('Encrypt error: ' + e.message); }
});

decryptBtn.addEventListener('click', () => {
  try {
    const keyStr = normalizeKeyTo8Bytes(keyInputEl.value);
    const nums = cipherTextEl.innerText.trim();
    const start = performance.now();
    const result = desDecryptFromNumbers(nums, keyStr);
    const end = performance.now();
    decryptedTextEl.innerText = result;
    decryptTimeEl.innerText = (end - start).toFixed(2) + ' ms';
    log('Decrypted.');
  } catch (e) { log('Decrypt error: ' + e.message); }
});

checkWeakBtn.addEventListener('click', () => {
  const key8 = normalizeKeyTo8Bytes(keyInputEl.value);
  const hexKey = Buffer.from(key8, 'utf8').toString('hex').toUpperCase();
  let out = `Key (hex): ${hexKey}\n`;
  if (DES_WEAK_KEYS.includes(hexKey)) out += 'Ключ — СЛАБЫЙ (из стандартного списка)\n';
  const foundSemi = DES_SEMIWEAK_PAIRS.some(p => p[0] === hexKey || p[1] === hexKey);
  if (foundSemi) out += 'Ключ — ПОЛУСЛАБЫЙ\n';
  if (!DES_WEAK_KEYS.includes(hexKey) && !foundSemi)
    out += 'Ключ не найден в стандартных списках слабых/полуслабых.\n';
  weakResult.innerText = out;
  log('Checked weak/semi-weak key.');
});

compressBtn.addEventListener('click', () => {
  try {
    const pt = plaintextEl.value;
    const ct = cipherTextEl.innerText.trim();
    const ptBytes = new TextEncoder().encode(pt);
    const ctBytes = new TextEncoder().encode(ct);
    const gzPt = pako.gzip(ptBytes);
    const gzCt = pako.gzip(ctBytes);
    const out = [
      `Plaintext bytes: ${ptBytes.length}`,
      `Plaintext gzip: ${gzPt.length}`,
      `Ciphertext bytes: ${ctBytes.length}`,
      `Ciphertext gzip: ${gzCt.length}`,
      `Compression ratio plaintext: ${(gzPt.length / ptBytes.length).toFixed(3)}`,
      `Compression ratio ciphertext: ${(gzCt.length / ctBytes.length).toFixed(3)}`
    ].join('\n');
    compressResult.innerText = out;
    log('Compression done.');
  } catch (e) { log('Compression error: ' + e.message); }
});

avalancheBtn.addEventListener('click', () => {
  avalancheResult.innerText = 'Running...';
  avalancheTable.innerHTML = '';
  setTimeout(() => {
    try {
      const key8raw = normalizeKeyTo8Bytes(keyInputEl.value);
      let block = plaintextEl.value.slice(0,8);
      while (Buffer.from(block,'utf8').length < 8) block += '\0';
      const blockRaw = Buffer.from(block,'utf8').toString('latin1');
      const baseCipher = CryptoJS.DES.encrypt(blockRaw, CryptoJS.enc.Utf8.parse(key8raw), {
        mode: CryptoJS.mode.ECB, padding: CryptoJS.pad.Pkcs7
      }).toString();
      const baseCipherHex = CryptoJS.enc.Base64.parse(baseCipher).toString(CryptoJS.enc.Hex);

      const results = [];
      for (let i=0;i<64;i++) {
        const modBlock = flipBitIn8ByteString(blockRaw,i);
        const c = CryptoJS.DES.encrypt(modBlock, CryptoJS.enc.Utf8.parse(key8raw),
          { mode: CryptoJS.mode.ECB, padding: CryptoJS.pad.Pkcs7 }).toString();
        const diff = countDifferentBitsHex(baseCipherHex, CryptoJS.enc.Base64.parse(c).toString(CryptoJS.enc.Hex));
        results.push({type:'plaintext',bit:i,diff});
      }
      for (let i=0;i<64;i++) {
        const modKey = flipBitIn8ByteString(Buffer.from(key8raw,'utf8').toString('latin1'),i);
        const c = CryptoJS.DES.encrypt(blockRaw, CryptoJS.enc.Utf8.parse(modKey),
          { mode: CryptoJS.mode.ECB, padding: CryptoJS.pad.Pkcs7 }).toString();
        const diff = countDifferentBitsHex(baseCipherHex, CryptoJS.enc.Base64.parse(c).toString(CryptoJS.enc.Hex));
        results.push({type:'key',bit:i,diff});
      }
      const avgP = results.filter(r=>r.type==='plaintext').reduce((s,r)=>s+r.diff,0)/64;
      const avgK = results.filter(r=>r.type==='key').reduce((s,r)=>s+r.diff,0)/64;
      avalancheResult.innerText =
        `Среднее изменение бит: plaintext ${avgP.toFixed(2)} / key ${avgK.toFixed(2)}`;
      log('Avalanche done.');
    } catch (e) {
      avalancheResult.innerText = 'Ошибка: ' + e.message;
      log('Avalanche error: ' + e.message);
    }
  }, 50);
});
