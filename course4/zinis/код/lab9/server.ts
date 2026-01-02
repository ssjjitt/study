import crypto from "crypto";
import { buffer } from "stream/consumers";

function generateSHA256(input: string, salt: string): string {
  let data = input + salt;
  let hashBuffer: any = crypto
    .createHash("sha256")
    .update(data, "utf8")
    .digest("hex");
  return toHex(hashBuffer);
}

function toHex(buffer: Buffer): string {
  return buffer.toString();
}

function generateRandomText(length: number): string {
  let characters =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
  const charLen: number = characters.length;
  let result = "";

  for (let i = 0; i < length; i++) {
    const randomIndex = crypto.randomBytes(4).readUInt32LE(0) % charLen;
    result += characters[randomIndex];
  }

  return result;
}

function Main() {
  let startTime = Date.now();

  let text: string = "Gluhova Daria Vitalievna";
  let salt: string = createSalt(15);
  let hash: string = generateSHA256(text, salt);

  console.log("Сообщение: " + text);
  console.log("Соль: " + salt);
  console.log("Хэш: " + hash);
  console.log("Время: " + (Date.now() - startTime) + " мс");

  console.log("------------------------------------");

  let startTime1 = Date.now();

  let text1: string = generateRandomText(1000);
  let salt1: string = createSalt(15);
  let hash1: string = generateSHA256(text, salt);

  console.log("Сообщение: " + text1);
  console.log("Соль: " + salt1);
  console.log("Хэш: " + hash1);
  console.log("Время: " + (Date.now() - startTime1) + " мс");
}

function createSalt(size: number) {
  let rng = crypto.randomBytes(size).toString("base64");
  return rng;
}

Main();
