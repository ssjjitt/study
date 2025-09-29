const { Builder, By, until, Key } = require('selenium-webdriver');

async function runUITest() {
    let driver = await new Builder().forBrowser('chrome').build();

    try {

        console.log('-------------------------------------');

        try {
            await driver.get('https://www.saucedemo.com');
            let username = await driver.wait(until.elementLocated(By.id('user-name')), 10000);
            await driver.wait(until.elementIsVisible(username), 10000);
            await username.sendKeys('standard_user');

            console.log('Найден элемент по css: ' + await username.getText());
            let password = await driver.wait(until.elementLocated(By.id('password')), 10000);
            await driver.wait(until.elementIsVisible(password), 10000);
            await password.sendKeys('secret_sauce', Key.ENTER);
            console.log('Найден элемент по css: ' + await username.getAttribute('value'));

            console.log('Все поля заполнены успешно');

            // let buttonTime = await driver.wait(until.elementLocated(By.className('orangehrm-attendance-card-action')), 10000);
            // await driver.wait(until.elementIsVisible(buttonTime), 10000);
            // buttonTime = await driver.findElement(By.className('orangehrm-attendance-card-action'));
            // const actions = driver.actions({ async: true });
            // await actions.move({ origin: buttonTime }).click().perform();

            // let submit = await driver.wait(until.elementLocated(By.className('oxd-button')), 10000);
            // await driver.wait(until.elementIsVisible(submit), 10000);
            // await actions.move({ origin: submit }).click().perform();

            await driver.sleep(30000000);

        } catch (e) {
            console.log('ошибка' + e);
        }
    } finally {
        await driver.quit();
    }
}

runUITest();
