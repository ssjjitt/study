function NOD(x, y) {
	if (y > x) return NOD(y, x);
	if (!y) return x;
	return NOD(y, x % y);
}

function SIMPLE(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % j === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	console.log("Количество простых числе в диапазоне: [" + x + "," + y + "]:" + primes.length);
	return primes;
}

function PRINT(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		primes.push(i);
	}
	return primes;
}

function TWO(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function THREE(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if ((i % 3 === 0) || (i % 2 === 0)) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function FIVE(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 5 === 0 || i % 3 === 0 || i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function SEVEN(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 7 === 0 || i % 5 === 0 || i % 3 === 0 || i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function ELEVEN(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 11 === 0 || i % 7 === 0 || i % 5 === 0 || i % 3 === 0 || i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function THIRTEEN(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 13 === 0 || i % 11 === 0 || i % 7 === 0 || i % 5 === 0 || i % 3 === 0 || i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

function SEVENTEEN(x, y) {
	let primes = [];
	for (let i = x; i <= y; i++) {
		let isPrime = true;
		for (let j = 2; j < i; j++) {
			if (i % 17 === 0 || i % 13 === 0 || i % 11 === 0 || i % 7 === 0 || i % 5 === 0 || i % 3 === 0 || i % 2 === 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) primes.push(i);
	}
	return primes;
}

console.log("NOD:");
console.log(NOD(450, 503));
console.log("SIMPLE:");
console.log(SIMPLE(2, 589));

console.log("ERATOSPHEN:");
console.log(PRINT(450, 503));
console.log("S = 2:");
console.log(TWO(450, 503));
console.log("S = 3:");
console.log(THREE(450, 503));
console.log("S = 5:");
console.log(FIVE(450, 503));
console.log("S = 7:");
console.log(SEVEN(450, 503));
console.log("S = 11:");
console.log(ELEVEN(450, 503));
console.log("S = 13:");
console.log(THIRTEEN(450, 503));
console.log("S = 17:");
console.log(SEVENTEEN(450, 503));