const {
    makeGenMatrix, showMatrix, makeCanonicalG,
    makeCheckMatrix, encode, addRandomErrors,
    getSyndrome, findErrorPosition, xorStr
} = require('./mylib');

const main = () => {
    const g = '10011';
    const message = '10011';
    const k = message.length;
    const r = g.length - 1;
    const n = k + r;

    console.log('Xk:', message);
    console.log('G:', g);
    console.log(`k = ${k}`);
    console.log(`r = ${r}`);
    console.log(`n = ${n}`);

    const genMatrix = makeGenMatrix(g, k, n);
    console.log('\nПорождающая матрица:');
    showMatrix(genMatrix, k, n);

    const canonicalG = makeCanonicalG(k, n, g);
    console.log('\nКаноническая порождающая матрица:');
    canonicalG.forEach(row => console.log(' ' + row.join(' ')));

    const checkMatrix = makeCheckMatrix(canonicalG, k, n);
    console.log('\nПроверочная матрица:');
    checkMatrix.forEach(row => console.log(' ' + row.join(' ')));

    const encoded = encode(message, g, k, n);
    console.log('Кодовое слово:', encoded);

    let received = addRandomErrors(encoded, 0);
    console.log('\nПринятое без ошибок:', received);
    let syndrome = getSyndrome(received, g);
    console.log('Синдром:', syndrome);

    for (let mistakes = 1; mistakes <= 2; mistakes++) {
        received = addRandomErrors(encoded, mistakes);
        console.log(`\nПринятое сообщение (${mistakes} ошибк${mistakes > 1 ? 'и' : 'а'}):`, received);
        syndrome = getSyndrome(received, g);
        console.log('Синдром:', syndrome);
        const errVec = findErrorPosition(syndrome, checkMatrix, n);
        console.log('Вектор ошибки:', errVec);
        console.log('Исправленное сообщение:', xorStr(received, errVec));
    }
};

main();