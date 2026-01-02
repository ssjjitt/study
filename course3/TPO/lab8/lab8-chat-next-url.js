const { Builder, By, until, Key } = require('selenium-webdriver');
const chrome = require('selenium-webdriver/chrome');

async function runUITest() {
    let options = new chrome.Options();

    // с богом обходим робота
    options.addArguments("--start-maximized");
    options.addArguments("--incognito");
    options.addArguments("--headless");
    options.addArguments("--disable-extensions");
    options.addArguments("--disable-popup-blocking");
    options.addArguments("--disable-infobars");

    let driver = await new Builder().forBrowser('chrome').setChromeOptions(options).build();
    
    try {
        await driver.get('https://auth.openai.com/authorize?audience=https%3A%2F%2Fapi.openai.com%2Fv1&client_id=TdJIcbe16WoTHtN95nyywh5E4yOo6ItG&country_code=FR&device_id=090172a9-1e6c-4bce-bc73-7100c4e9debb&ext-login-allow-phone=true&ext-oai-did=090172a9-1e6c-4bce-bc73-7100c4e9debb&ext-signup-allow-phone=true&prompt=login&redirect_uri=https%3A%2F%2Fchatgpt.com%2Fapi%2Fauth%2Fcallback%2Fopenai&response_type=code&scope=openid+email+profile+offline_access+model.request+model.read+organization.read+organization.write&screen_hint=login&state=VvsnNy0mSg5iFH-G1HRSlOCwHkukTuy1RnfOHJjgGRY&flow=treatment');

        console.log('-------------------------------------');

        try {
            //let input = await driver.wait(until.elementLocated(By.css('label[for="email-input"]')), 10000);
            // [data-provider="google"]
            let input = await driver.wait(until.elementLocated(By.id('email-input')), 10000);
            await driver.wait(until.elementIsVisible(input), 10000);
            await input.sendKeys('i46277947@gmail.com', Key.ENTER);

            await driver.sleep(30000000);

            console.log('Найден элемент по css: ' + await input.getText());
        } catch (e) {
            console.log('Текст ошибки: ' + e);
        }
        // i46277947@gmail.com
    } finally {
        await driver.quit();
    }
}

runUITest();
