const { Console } = require('console');
const fs = require('fs');

function stringToAsciiBuffer(str, length) {
    const buffer = new Uint8Array(length).fill(0);
    for (let i = 0; i < str.length; i++) {
        buffer[i] = str.charCodeAt(i);
    }
    return buffer;
}

function xorBuffers(bufferA, bufferB) {
    if (bufferA.length !== bufferB.length) {
        throw new Error("Buffers must have the same length");
    }
    const result = new Uint8Array(bufferA.length);
    for (let i = 0; i < bufferA.length; i++) {
        result[i] = bufferA[i] ^ bufferB[i];
    }
    return result;
}

function bufferToAsciiString(buffer) {
    return String.fromCharCode(...buffer);
}

function bufferToBase64(buffer) {
    return Buffer.from(buffer).toString('base64');
}

function base64ToBuffer(base64Str, length) {
    const decoded = Buffer.from(base64Str, 'base64');
    const buffer = new Uint8Array(length).fill(0);
    decoded.forEach((byte, i) => buffer[i] = byte);
    return buffer;
}

const surname = "Gluhova";
const name = "Daria";
const maxLength = Math.max(surname.length, name.length);

const bufferA = stringToAsciiBuffer(surname, maxLength);
const bufferB = stringToAsciiBuffer(name, maxLength);

const xorAB = xorBuffers(bufferA, bufferB);
const xorAB_B = xorBuffers(xorAB, bufferB);

console.log("ASCII XOR result xorAB:");
console.log(xorAB);
console.log("ASCII XOR result xorAB_B:");
console.log(xorAB_B);

const base64A = bufferToBase64(bufferA);
const base64B = bufferToBase64(bufferB);

const bufferA_base64 = base64ToBuffer(base64A, maxLength);
const bufferB_base64 = base64ToBuffer(base64B, maxLength);

const xorAB_base64 = xorBuffers(bufferA_base64, bufferB_base64);
const xorAB_B_base64 = xorBuffers(xorAB_base64, bufferB_base64);

console.log("ASCII XOR result xorAB_base64:");
console.log(xorAB_base64);
console.log("ASCII XOR result xorAB__B_base64:");
console.log(xorAB_B_base64);

console.log("XOR result:");
console.log(bufferToAsciiString(xorAB));
console.log("XOR again with B (should be A):");
console.log(bufferToAsciiString(xorAB_B));
console.log("Base64 XOR result:");
console.log(bufferToBase64(xorAB_base64));
console.log("XOR again with B (should be A):");
console.log(bufferToBase64(xorAB_B_base64));

console.log("ПРОВЕРКА: ");
console.log("Ascii: ");
console.log(71 ^ 68); // 3
console.log(108 ^ 97); // 13
console.log(117 ^ 114); // 7
console.log(104 ^ 105); // 1
console.log(111 ^ 97); // 14
console.log(118 ^ 0); // 118
console.log(97 ^ 0); // 97

console.log("Base64: ");
console.log(Buffer.from("Gluhova").toString('base64')); // "R2x1aG92YQ=="
console.log(Buffer.from("Daria").toString('base64')); // "RGFyaWE="
console.log("Decoded Base64 A:", Buffer.from("R2x1aG92YQ==", "base64").toString()); // фамилия