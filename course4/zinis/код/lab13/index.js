/**
 * Основной файл приложения для текстовой стеганографии
 * Реализует кодирование и декодирование сообщений через модификацию
 * пространственно-геометрических параметров текста (line-height и letter-spacing)
 */

import { encodeMessage, encodeMessageByLines } from './encode.js';
import { decodeMessage, decodeMessageByLines } from './decode.js';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

/**
 * Выводит справку по использованию
 */
function showHelp() {
  console.log(`
Использование:
  node index.js encode <контейнер.txt> <сообщение.txt> <выходной.html> [--lines]
  node index.js decode <закодированный.html> [--lines]
  node index.js help

Опции:
  encode  - Кодирует скрытое сообщение в текст-контейнер
  decode  - Декодирует скрытое сообщение из HTML файла
  --lines - Использовать метод кодирования по строкам (по умолчанию по символам)

Примеры:
  node index.js encode container.txt secret.txt output.html
  node index.js encode container.txt secret.txt output.html --lines
  node index.js decode output.html
  node index.js decode output.html --lines
  `);
}

/**
 * Кодирует сообщение
 */
function performEncode(args) {
  const useLines = args.includes('--lines');
  const files = args.filter(arg => !arg.startsWith('--'));
  
  if (files.length < 3) {
    console.error('Ошибка: Недостаточно аргументов для кодирования');
    console.error('Использование: node index.js encode <контейнер.txt> <сообщение.txt> <выходной.html>');
    process.exit(1);
  }
  
  const [containerFile, messageFile, outputFile] = files;
  
  try {
    // Читаем файлы
    const containerText = fs.readFileSync(containerFile, 'utf-8');
    const secretMessage = fs.readFileSync(messageFile, 'utf-8');
    
    console.log(`Кодирование сообщения...`);
    console.log(`Контейнер: ${containerFile}`);
    console.log(`Сообщение: ${messageFile}`);
    console.log(`Метод: ${useLines ? 'по строкам' : 'по символам'}`);
    
    // Кодируем сообщение
    const htmlContent = useLines 
      ? encodeMessageByLines(containerText, secretMessage)
      : encodeMessage(containerText, secretMessage);
    
    // Сохраняем результат
    fs.writeFileSync(outputFile, htmlContent, 'utf-8');
    
    console.log(`✓ Сообщение успешно закодировано в: ${outputFile}`);
    console.log(`  Размер контейнера: ${containerText.length} символов`);
    console.log(`  Размер сообщения: ${secretMessage.length} символов`);
    console.log(`  Использовано бит: ${secretMessage.length * 8}`);
    
  } catch (error) {
    console.error('Ошибка при кодировании:', error.message);
    process.exit(1);
  }
}

/**
 * Декодирует сообщение
 */
function performDecode(args) {
  const useLines = args.includes('--lines');
  const files = args.filter(arg => !arg.startsWith('--'));
  
  if (files.length < 1) {
    console.error('Ошибка: Не указан файл для декодирования');
    console.error('Использование: node index.js decode <закодированный.html>');
    process.exit(1);
  }
  
  const [htmlFile] = files;
  
  try {
    // Читаем HTML файл
    const htmlContent = fs.readFileSync(htmlFile, 'utf-8');
    
    console.log(`Декодирование сообщения из: ${htmlFile}`);
    console.log(`Метод: ${useLines ? 'по строкам' : 'по символам'}`);
    
    // Декодируем сообщение
    const decodedMessage = useLines
      ? decodeMessageByLines(htmlContent)
      : decodeMessage(htmlContent);
    
    if (decodedMessage) {
      console.log('\n✓ Декодированное сообщение:');
      console.log('─'.repeat(50));
      console.log(decodedMessage);
      console.log('─'.repeat(50));
      
      // Предлагаем сохранить в файл
      const outputFile = htmlFile.replace('.html', '_decoded.txt');
      fs.writeFileSync(outputFile, decodedMessage, 'utf-8');
      console.log(`\n✓ Сообщение сохранено в: ${outputFile}`);
    } else {
      console.log('⚠ Не удалось декодировать сообщение');
    }
    
  } catch (error) {
    console.error('Ошибка при декодировании:', error.message);
    process.exit(1);
  }
}

/**
 * Создает примеры файлов для тестирования
 */
function createExamples() {
  const containerText = `Это пример текста-контейнера для стеганографии.
Он содержит достаточно символов для кодирования скрытого сообщения.
Метод стеганографии основан на модификации пространственно-геометрических параметров.
А именно, мы изменяем межстрочное расстояние (line-height) и межбуквенное расстояние (letter-spacing).
Эти изменения практически незаметны для человеческого глаза, но могут быть обнаружены программно.
Таким образом, мы можем скрыть секретное сообщение в обычном тексте.
Стеганография - это искусство скрытой передачи информации.
В отличие от криптографии, стеганография скрывает сам факт существования сообщения.
Это делает её особенно полезной для защиты конфиденциальной информации.
Приложение реализует два метода кодирования: по символам и по строкам.`;

  const secretMessage = 'Секретное сообщение!';
  
  fs.writeFileSync('example_container.txt', containerText, 'utf-8');
  fs.writeFileSync('example_message.txt', secretMessage, 'utf-8');
  
  console.log('✓ Созданы примеры файлов:');
  console.log('  - example_container.txt');
  console.log('  - example_message.txt');
  console.log('\nТеперь вы можете протестировать кодирование:');
  console.log('  node index.js encode example_container.txt example_message.txt output.html');
}

// Основная логика
const args = process.argv.slice(2);

if (args.length === 0 || args[0] === 'help' || args[0] === '--help' || args[0] === '-h') {
  showHelp();
} else if (args[0] === 'encode') {
  performEncode(args.slice(1));
} else if (args[0] === 'decode') {
  performDecode(args.slice(1));
} else if (args[0] === 'examples') {
  createExamples();
} else {
  console.error('Неизвестная команда:', args[0]);
  showHelp();
  process.exit(1);
}

