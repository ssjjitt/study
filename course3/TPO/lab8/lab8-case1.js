const { Builder, By, until, Key } = require('selenium-webdriver');
const chrome = require('selenium-webdriver/chrome');

async function runUITest() {
  let options = new chrome.Options();
  options.addArguments("--start-maximized");
  options.addArguments("--disable-extensions");
  options.addArguments("--disable-popup-blocking");
  options.addArguments("--disable-blink-features=AutomationControlled");

  let driver = await new Builder().forBrowser('chrome').setChromeOptions(options).build();
  await driver.executeScript("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})");

  await driver.get('https://chatgpt.com/')

  try {
    let textarea = await driver.wait(until.elementLocated(By.id('prompt-textarea')), 10000);
    await driver.wait(until.elementIsVisible(textarea), 10000);

    const actions = driver.actions({ async: true });
    await actions.move({ origin: textarea }).perform();
    await actions.move({ origin: driver.findElement(By.css('body')) }).perform(); 
    
    await textarea.sendKeys('Разгадай загадку: На колесах едет ловко, если тянешь за веревку.');

    await textarea.sendKeys(Key.ENTER);

    let responseElement = await driver.wait(until.elementLocated(By.className('markdown prose dark:prose-invert w-full break-words dark')), 30000);
    await driver.wait(until.elementIsVisible(responseElement), 10000);

    let responseText = await responseElement.getText();
    console.log('Ответ от ChatGPT:', responseText);

    await driver.sleep(9000000);
  } catch (e) {
    console.log('Ошибка:', e);
  } finally {
    await driver.quit();
  }
}

runUITest();
