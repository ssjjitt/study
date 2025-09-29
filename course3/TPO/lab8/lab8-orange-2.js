// href="/web/index.php/time/viewTimeModule"

const { Builder, By, until, Key } = require('selenium-webdriver');

async function runUITest() {
    let driver = await new Builder().forBrowser('chrome').build();

    try {

        console.log('-------------------------------------');

        try {
            await driver.get('https://opensource-demo.orangehrmlive.com/');
            let username = await driver.wait(until.elementLocated(By.name('username')), 1000);
            await driver.wait(until.elementIsVisible(username), 1000);
            await username.sendKeys('Admin');

            console.log('Найден элемент по css: ' + await username.getText());
            let password = await driver.wait(until.elementLocated(By.name('password')), 1000);
            await driver.wait(until.elementIsVisible(password), 1000);
            await password.sendKeys('admin123', Key.ENTER);
            console.log('Найден элемент по css: ' + await password.getText());

            console.log('Все поля заполнены успешно');

            await driver.sleep(3000);

            let buttonTime = await driver.findElement(By.partialLinkText('Time'));
            await driver.wait(until.elementIsVisible(buttonTime), 1000);
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
