const { Builder, By, until, Key } = require('selenium-webdriver');
const chrome = require('selenium-webdriver/chrome');

async function runUITest() {
    let driver = await new Builder().forBrowser('chrome').build();

    try {

        console.log('-------------------------------------');

        try {
            await driver.get('https://demoqa.com');
            const originalWindow = await driver.getWindowHandle();
            let input = await driver.wait(until.elementLocated(By.className('banner-image')), 10000);
            await driver.wait(until.elementIsVisible(input), 10000);
            const actions = driver.actions({ async: true });
            await actions.move({ origin: input }).click().perform();
            console.log('Найден элемент по css: ' + await input.getText());

            await driver.sleep(7000);
            await driver.wait(async () => {
                const handles = await driver.getAllWindowHandles();
                return handles.length > 1;
            }, 10000, 'Новая вкладка не появилась');
            const windows = await driver.getAllWindowHandles();
            for (let handle of windows) {
                if (handle !== originalWindow) {
                    await driver.switchTo().window(handle);
                    break;
                }
            }
            console.log('Переключились на новую вкладку: ' + await driver.getCurrentUrl());
            console.log('driver: ', await driver.getCurrentUrl());
            let formElement = await driver.findElement(By.id('enroll-form'));
            await driver.wait(until.elementIsVisible(formElement), 10000);
            console.log('Форма видна на странице');

            let firstName = await driver.findElement(By.name('firstName'));
            await firstName.sendKeys('daria');
            let lastName = await driver.findElement(By.name('lastName'));
            await lastName.sendKeys('gluhova');
            let email = await driver.findElement(By.name('email'));
            await email.sendKeys('ssjjitt@gmail.com');
            let mobile = await driver.findElement(By.name('mobile'));
            await mobile.sendKeys('+375297081954');
            const country = await driver.findElement(By.name('country'));
            await country.click();
            const countrySelect = await driver.findElement(By.css('select#country option[value="74"]'));
            await countrySelect.click();
            let city = await driver.findElement(By.name('city'));
            await city.sendKeys('Minsk');
            let message = await driver.findElement(By.name('message'));
            await message.sendKeys('почему чат гпт меня не пустил к себе на сайт(((( анлак');

            let formButton = await driver.findElement(By.css('form#enroll-form button'));
            await formButton.click();

            console.log('Все поля заполнены успешно');
            await driver.sleep(30000000);

        } catch (e) {
            console.log('ошибка' + e);
        }

        await driver.wait(until.urlContains('/selenium-training'), 10000);

        try {

        } catch (e) {
            console.log('текст ошибки: ' + e);
        }
        // i46277947@gmail.com
    } finally {
        await driver.quit();
    }
}

runUITest();
