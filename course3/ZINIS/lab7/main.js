const {
    generateRandomBits,
    createCheckMatrix,
    addCheckBits,
    interleave,
    deinterleave,
    introduceErrors,
    correctErrors,
    compareBits
} = require('./hamming_interleaver');

const k = 4;
const iterations = 40;
const errorLength = 6;

let totalAccuracy = 0;

for (let i = 0; i < iterations; i++) {
    const original = generateRandomBits(k * k);
    const checkMatrix = createCheckMatrix(k);
    const encoded = addCheckBits(original, k, checkMatrix);
    const interleaved = interleave(encoded, k);
    const { data: corrupted } = introduceErrors([...interleaved], errorLength);
    const deinterleaved = deinterleave(corrupted, k);
    const recovered = correctErrors(deinterleaved, k, checkMatrix);
    const accuracy = compareBits(original, recovered);
    totalAccuracy += accuracy;

    console.log(`Попытка ${i + 1}: Точность ${(accuracy * 100).toFixed(2)}%`);
}

const avg = (totalAccuracy / iterations) * 100;
console.log(`\nСредняя точность по ${iterations} попыткам: ${avg.toFixed(2)}%`);
