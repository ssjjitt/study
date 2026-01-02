function textToBinary(text) {
  return text
    .split('')
    .map(char => char.charCodeAt(0).toString(2).padStart(8, '0'))
    .join('');
}

export function encodeMessage(containerText, secretMessage) {
  const binaryMessage = textToBinary(secretMessage);
  
  const messageWithMarker = binaryMessage + '00000000';
  
  const chars = containerText.split('');
  const totalBits = messageWithMarker.length;
  
  if (chars.length < totalBits) {
    throw new Error('Текст-контейнер слишком короткий для кодирования сообщения');
  }
  
  let bitIndex = 0;
  const htmlParts = [];
  
  htmlParts.push('<!DOCTYPE html>\n<html>\n<head>\n<meta charset="UTF-8">\n<title>Закодированный текст</title>\n</head>\n<body>\n<p style="font-family: Arial, sans-serif; font-size: 16px;">\n');
  
  for (let i = 0; i < chars.length; i++) {
    const char = chars[i];
    let styles = [];
    
    if (bitIndex < totalBits) {
      const bit = messageWithMarker[bitIndex];
      const letterSpacing = bit === '1' ? '0.12px' : '0px';
      styles.push(`letter-spacing: ${letterSpacing}`);
      bitIndex++;
    }
    
    let displayChar = char;
    if (char === '<') displayChar = '&lt;';
    else if (char === '>') displayChar = '&gt;';
    else if (char === '&') displayChar = '&amp;';
    else if (char === '\n') displayChar = '<br>';
    
    if (styles.length > 0) {
      htmlParts.push(`<span style="${styles.join('; ')}">${displayChar}</span>`);
    } else {
      htmlParts.push(displayChar);
    }
  }
  
  htmlParts.push('\n</p>\n</body>\n</html>');
  
  return htmlParts.join('');
}

export function encodeMessageByLines(containerText, secretMessage) {
  const binaryMessage = textToBinary(secretMessage) + '00000000';
  const lines = containerText.split('\n');
  const totalBits = binaryMessage.length;
  
  if (lines.length < Math.ceil(totalBits / 2)) {
    throw new Error(`Недостаточно строк в тексте-контейнере. Требуется минимум ${Math.ceil(totalBits / 2)} строк, имеется ${lines.length}`);
  }
  
  let bitIndex = 0;
  const htmlParts = [];
  
  htmlParts.push('<!DOCTYPE html>\n<html>\n<head>\n<meta charset="UTF-8">\n<title>Закодированный текст</title>\n</head>\n<body>\n<div style="font-family: Arial, sans-serif; font-size: 16px;">\n');
  
  for (let i = 0; i < lines.length && bitIndex < totalBits; i++) {
    const line = lines[i];
    let lineStyle = [];
    
    if (bitIndex < totalBits) {
      const bit = binaryMessage[bitIndex];
      const lineHeight = bit === '1' ? '1.75' : '1.5';
      lineStyle.push(`line-height: ${lineHeight}`);
      bitIndex++;
    }
    
    if (bitIndex < totalBits) {
      const bit = binaryMessage[bitIndex];
      const letterSpacing = bit === '1' ? '0.15px' : '0px';
      lineStyle.push(`letter-spacing: ${letterSpacing}`);
      bitIndex++;
    }
    
    const styleAttr = lineStyle.length > 0 ? ` style="${lineStyle.join('; ')}"` : '';
    htmlParts.push(`<p${styleAttr}>${line}</p>\n`);
  }
  
  for (let i = Math.ceil(bitIndex / 2); i < lines.length; i++) {
    htmlParts.push(`<p>${lines[i]}</p>\n`);
  }
  
  htmlParts.push('</div>\n</body>\n</html>');
  
  return htmlParts.join('');
}

