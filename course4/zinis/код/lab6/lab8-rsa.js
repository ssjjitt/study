const forge = require('node-forge');

function generateLargePrimes(bits = 256) {
  return new Promise((resolve, reject) => {
    forge.prime.generateProbablePrime(bits, (err, p) => {
      if (err) return reject(err);
      forge.prime.generateProbablePrime(bits, (err, q) => {
        if (err) return reject(err);
        resolve({ p: new forge.jsbn.BigInteger(p.toString()), q: new forge.jsbn.BigInteger(q.toString()) });
      });
    });
  });
}
function findE(phi) {
  const e = new forge.jsbn.BigInteger('65537');
  if (phi.gcd(e).compareTo(forge.jsbn.BigInteger.ONE) === 0) {
    return e;
  }
  throw new Error('e не взаимно просто с φ(n)');
}
function rsaStep(xPrev, e, n) {
  return xPrev.modPow(e, n);
}
function getLeastSignificantBit(bigInt) {
  return bigInt.testBit(0) ? 1 : 0;
}
async function generatePRNGSequence(length = 20) {
  const { p, q } = await generateLargePrimes();
  const n = p.multiply(q);
  const phi = p.subtract(forge.jsbn.BigInteger.ONE).multiply(q.subtract(forge.jsbn.BigInteger.ONE));
  const e = findE(phi);

  const randomBytes = forge.random.getBytesSync(64);
  let x = new forge.jsbn.BigInteger(forge.util.bytesToHex(randomBytes), 16).mod(n);
  const x0 = x; // сохраняем начальное значение

  const sequence = [];
  for (let t = 0; t < length; t++) {
    x = rsaStep(x, e, n);
    sequence.push(getLeastSignificantBit(x));
    
  }

  console.log('--- RSA-based PRNG ---');
  console.log('p  =', p.toString(10));
  console.log('q  =', q.toString(10));
  console.log('n  =', n.toString(10));
  console.log('x0 =', x0.toString(10));
  const binaryStr = sequence.join('');
  const decimalValue = new forge.jsbn.BigInteger(binaryStr, 2);
  
  console.log('Generated bit sequence:', binaryStr);
  console.log('Generated ПСП (10):', decimalValue.toString(10));
}

generatePRNGSequence().catch(console.error);
