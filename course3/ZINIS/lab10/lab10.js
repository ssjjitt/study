// Lempel-Ziv Compression and Decompression in Node.js
const readline = require("readline");

function toAddSymbols(symbolAmount, buffer, slidingWindow) {
  if (symbolAmount > slidingWindow.length) symbolAmount = slidingWindow.length;
  if (symbolAmount > 0) {
    buffer += slidingWindow.slice(0, symbolAmount);
    slidingWindow = slidingWindow.slice(symbolAmount);
  }
  return [buffer, slidingWindow];
}

function toCheckBufferSize(size, buffer) {
  if (buffer.length > size) buffer = buffer.slice(buffer.length - size);
  return buffer;
}

function toSearchSymbols(buffer, slidingWindow) {
  let coincideLength = 0;
  let theNextSymbol = slidingWindow[0];
  let indeedSet = 0;

  while (
    coincideLength + 1 <= slidingWindow.length &&
    buffer.includes(slidingWindow.slice(0, coincideLength + 1))
  ) {
    indeedSet = buffer.indexOf(slidingWindow.slice(0, coincideLength + 1)) + 1;
    coincideLength++;
    if (coincideLength === slidingWindow.length) {
      theNextSymbol = ' ';
      break;
    } else {
      theNextSymbol = slidingWindow[coincideLength];
    }
  }

  return [indeedSet, coincideLength, theNextSymbol];
}

async function main() {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });

  const ask = (query) => new Promise((resolve) => rl.question(query, resolve));

  try {
    console.log("Программа сжатия методом Лемпеля-Зива");
    const input = "1100001111";
    console.log("Исходное сообщение:", input);

    let dictionaryBuffer = parseInt(await ask("Размер словаря: "));
    let slidingWindowDataBuffer = parseInt(await ask("Размер буфера: "));

    let mainDictionary = "0".repeat(dictionaryBuffer);
    let slidingWindowMessage = input.slice(0, slidingWindowDataBuffer);
    let afterSlidingWindowMessage = input.slice(slidingWindowDataBuffer);

    console.log("\nСжатие методом Лемпеля-Зива:\n");
    let encodedInput = "";

    const startEncode = Date.now();

    while (slidingWindowMessage.length > 0) {
      let [indexStart, extLength, nextSymbol] = toSearchSymbols(mainDictionary, slidingWindowMessage);

      [mainDictionary, slidingWindowMessage] = toAddSymbols(extLength + 1, mainDictionary, slidingWindowMessage);
      mainDictionary = toCheckBufferSize(dictionaryBuffer, mainDictionary);

      [slidingWindowMessage, afterSlidingWindowMessage] = toAddSymbols(extLength + 1, slidingWindowMessage, afterSlidingWindowMessage);
      slidingWindowMessage = toCheckBufferSize(slidingWindowDataBuffer, slidingWindowMessage);

      console.log(`${mainDictionary} |\t${slidingWindowMessage}\t|${indexStart}${extLength}${nextSymbol}`);
      encodedInput += `${indexStart}${extLength}${nextSymbol}`;
    }

    const endEncode = Date.now();
    console.log("\nИтоговое сообщение:", encodedInput);

    console.log("\nРаспаковка\n");

    let unwrappedMessage = "";
    let tempStr = "";
    mainDictionary = "0".repeat(dictionaryBuffer);
    const startDecode = Date.now();

    for (let i = 0; i < encodedInput.length / 3; i++) {
      let indexStart = parseInt(encodedInput[3 * i]);
      let extLength = parseInt(encodedInput[3 * i + 1]);
      let nextSymbol = encodedInput[3 * i + 2];

      if (indexStart === 0 && extLength === 0) {
        unwrappedMessage += nextSymbol;
        mainDictionary += nextSymbol;
      } else {
        tempStr = mainDictionary.slice(indexStart - 1, indexStart - 1 + extLength) + nextSymbol;
        unwrappedMessage += tempStr;
        mainDictionary += tempStr;
      }

      mainDictionary = toCheckBufferSize(dictionaryBuffer, mainDictionary);
      console.log(`${indexStart}${extLength}${nextSymbol} |\t${mainDictionary}\t|${unwrappedMessage}`);
    }

    const endDecode = Date.now();

    console.log(`\nРазмер буфера: ${dictionaryBuffer}`);
    console.log(`Размер словаря: ${slidingWindowDataBuffer}`);
    console.log(`Время сжатия: ${endEncode - startEncode} мс`);
    console.log(`Время распаковки: ${endDecode - startDecode} мс`);
    console.log(`\nИсходное сообщение: ${input.length} символов`);
    console.log(`Сжатое сообщение: ${encodedInput.length} символов`);

    const efficiency = (input.length / encodedInput.length) * 100;
    console.log(`Эффективность применения метода Лемпеля-Зива составляет: ${efficiency.toFixed(2)}%`);
  } catch (e) {
    console.error("Ошибка при выполнении программы. Попробуйте ввести другие значения для буфера.");
  } finally {
    rl.close();
  }
}

main();
