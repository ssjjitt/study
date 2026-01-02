import { JSDOM } from 'jsdom';

function binaryToText(binary) {
  const bytes = [];
  for (let i = 0; i < binary.length; i += 8) {
    const byte = binary.substr(i, 8);
    if (byte.length === 8) {
      bytes.push(String.fromCharCode(parseInt(byte, 2)));
    }
  }
  return bytes.join('');
}

export function decodeMessage(htmlContent) {
  const dom = new JSDOM(htmlContent);
  const document = dom.window.document;
  
  const spans = document.querySelectorAll('span');
  const binaryBits = [];
  
  for (const span of spans) {
    const style = span.getAttribute('style') || '';
    
    const letterSpacingMatch = style.match(/letter-spacing:\s*([\d.]+)px/);
    if (letterSpacingMatch) {
      const spacing = parseFloat(letterSpacingMatch[1]);
      binaryBits.push(spacing > 0.05 ? '1' : '0');
    }
  }
  
  let binaryString = binaryBits.join('');
  const endMarker = '00000000';
  const endIndex = binaryString.indexOf(endMarker);
  
  if (endIndex !== -1) {
    binaryString = binaryString.substring(0, endIndex);
  }
  
  return binaryToText(binaryString);
}

export function decodeMessageByLines(htmlContent) {
  const dom = new JSDOM(htmlContent);
  const document = dom.window.document;
  
  const paragraphs = document.querySelectorAll('p');
  const binaryBits = [];
  
  for (const p of paragraphs) {
    const style = p.getAttribute('style') || '';
    
    const lineHeightMatch = style.match(/line-height:\s*([\d.]+)/);
    if (lineHeightMatch) {
      const height = parseFloat(lineHeightMatch[1]);
      binaryBits.push(height > 1.6 ? '1' : '0');
    }
    
    const letterSpacingMatch = style.match(/letter-spacing:\s*([\d.]+)px/);
    if (letterSpacingMatch) {
      const spacing = parseFloat(letterSpacingMatch[1]);
      binaryBits.push(spacing > 0.1 ? '1' : '0');
    }
  }
  
  let binaryString = binaryBits.join('');
  const endMarker = '00000000';
  const endIndex = binaryString.indexOf(endMarker);
  
  if (endIndex !== -1) {
    binaryString = binaryString.substring(0, endIndex);
  }
  
  return binaryToText(binaryString);
}

