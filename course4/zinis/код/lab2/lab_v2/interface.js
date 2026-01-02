function getLang() {
    return document.getElementById('ruRadio').checked ? 'ru' : 'bel';
}

function normalizeBelarusian(text) {
    return text
        .replace(/i/g, "і")
        .replace(/I/g, "І")
        .replace(/Ŭ/g, "Ў")
        .replace(/ŭ/g, "ў");
}

function sanitize(text, lang) {
    if (/[A-Za-z]/.test(text)) {
        alert('Латиница запрещена');
        throw new Error('latin not allowed');
    }
    if (lang === 'ru') return text.replace(/[^А-ЯЁа-яё\s.,:;!?()\-\n\r]/g, '');
    return text.replace(/[^А-ЯЁІЎа-яёіў'\s.,:;!?()\-\n\r]/g, '');
}

function updateCounters() {
    document.getElementById('openCount').textContent = document.getElementById('openText').value.length + " символов";
    document.getElementById('cipherCount').textContent = document.getElementById('cipherText').value.length + " символов";
}
document.getElementById('openText').addEventListener('input', updateCounters);
document.getElementById('cipherText').addEventListener('input', updateCounters);

function loadTxtInto(elemId, fileInputId) {
    const f = document.getElementById(fileInputId).files[0];
    if (!f) return;
    const reader = new FileReader();
    reader.onload = e => {
        document.querySelector(elemId).value = e.target.result.toString();
        updateCounters();
    };
    reader.readAsText(f, 'UTF-8');
}
document.getElementById('loadOpen').onclick = () => loadTxtInto('#openText', 'openFile');
document.getElementById('loadCipher').onclick = () => loadTxtInto('#cipherText', 'cipherFile');

document.getElementById('downloadResult').onclick = () => {
    const txt = document.getElementById('cipherText').value || document.getElementById('openText').value || '';
    const blob = new Blob([txt], { type: 'text/plain;charset=utf-8' });
    const a = document.createElement('a');
    a.href = URL.createObjectURL(blob);
    a.download = 'result.txt';
    document.body.appendChild(a);
    a.click();
    a.remove();
    URL.revokeObjectURL(a.href);
};

function getCharFrequencies(text) {
    const freq = {};
    for (let char of text) {
        if (char.trim() === "") continue;
        freq[char] = (freq[char] || 0) + 1;
    }
    return freq;
}

document.getElementById('encryptBtn').onclick = () => {
    const lang = getLang();
    const open = sanitize(normalizeBelarusian(document.getElementById('openText').value.toUpperCase(), lang));
    const key = sanitize(normalizeBelarusian(document.getElementById('key').value.toUpperCase(), lang));
    if (!(open.length && key.length)) { alert('Пустые поля.'); return; }

    const start = performance.now();
    const result = vizhener.encryption(lang, open, key);
    const end = performance.now();

    document.getElementById('cipherText').value = result;
    updateCounters();

    console.log("Время шифрования:", (end - start).toFixed(2), "мс");
    console.log("Частоты исходного текста:");
    console.table(getCharFrequencies(open));
    console.log("Частоты шифротекста:");
    console.table(getCharFrequencies(result));
};

document.getElementById('decryptBtn').onclick = () => {
    const lang = getLang();
    const cipher = sanitize(normalizeBelarusian(document.getElementById('cipherText').value.toUpperCase(), lang));
    const key = sanitize(normalizeBelarusian(document.getElementById('key').value.toUpperCase(), lang));
    if (!(cipher.length && key.length)) { alert('Пустые поля.'); return; }

    const start = performance.now();
    const result = vizhener.decryption(lang, key, cipher);
    const end = performance.now();

    document.getElementById('openText').value = result;
    updateCounters();

    console.log("Время расшифрования:", (end - start).toFixed(2), "мс");
    console.log("Частоты шифротекста:");
    console.table(getCharFrequencies(cipher));
    console.log("Частоты расшифрованного текста:");
    console.table(getCharFrequencies(result));
};

updateCounters();
