const { Builder, By, until, Key } = require('selenium-webdriver');

async function runUITest() {
    let driver = await new Builder().forBrowser('chrome').build();

    try {

        console.log('-------------------------------------');

        try {
            await driver.get('https://opensource-demo.orangehrmlive.com/web/index.php/auth/login');
            let username = await driver.wait(until.elementLocated(By.name('username')), 10000);
            await driver.wait(until.elementIsVisible(username), 10000);
            await username.sendKeys('Admin');

            console.log('Найден элемент по css: ' + await username.getText());
            let password = await driver.wait(until.elementLocated(By.name('password')), 10000);
            await driver.wait(until.elementIsVisible(password), 10000);
            await password.sendKeys('admin123', Key.ENTER);
            console.log('Найден элемент по css: ' + await password.getText());

            console.log('Все поля заполнены успешно');

            let buttonTime = await driver.wait(until.elementLocated(By.className('orangehrm-attendance-card-action')), 10000);
            await driver.wait(until.elementIsVisible(buttonTime), 10000);
            buttonTime = await driver.findElement(By.className('orangehrm-attendance-card-action'));
            const actions = driver.actions({ async: true });
            await actions.move({ origin: buttonTime }).click().perform();

            await driver.sleep(30000000);
        } catch (e) {
            console.log('ошибка' + e);
        }
    } finally {
        await driver.quit();
    }
}

runUITest();
