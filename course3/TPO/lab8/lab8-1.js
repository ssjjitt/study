const { Builder, By, until, Key } = require('selenium-webdriver');

async function runUITest() {
    let driver = await new Builder().forBrowser('chrome').build();
    let driver2 = await new Builder().forBrowser('chrome').build();

    try {
        await driver.get('https://ssjjitt.github.io/KP_1sem/main.html');

        // для name
        await driver2.get('https://ssjjitt.github.io/KP_1sem/contacts.html');

        console.log('-------------------------------------');

        // ID
        try {
            let elementById = await driver2.findElement(By.id('message'));
            await elementById.sendKeys('что зачем нам рыба, раз есть икра, что готический стиль победит, как школа, как способность торчать избежав укола.', Key.RETURN);
            console.log('Найден элемент по ID: ' + await elementById.getText());
        } catch (e) {
            console.log('Элемент по ID не найден');
        }

        console.log('-------------------------------------');

        // NAME
        try {
            let elementByName = await driver2.findElement(By.name('name'));
            await elementByName.sendKeys('я всегда твердил что судьба игра');
            console.log('Найден элемент по NAME:', await elementByName.getCssValue('border'));
        } catch (e) {
            console.log('Элемент по NAME не найден');
        }

        try {
            let elementByName2 = await driver2.findElement(By.name('email'));
            await elementByName2.sendKeys('tpo8@gmail.com');
            console.log('Найден элемент по NAME:', await elementByName2.getCssValue('border'));
        } catch (e) {
            console.log('Элемент по NAME не найден');
        }
    
        try {
            let elementByName3 = await driver2.findElement(By.name('phone'));
            await driver2.sleep(5000);
            const actions = driver2.actions({async: true});
            await actions.move({ x: 0, y: 0, origin: elementByName3 }).perform();
            console.log('Найден элемент по NAME:', await elementByName3.getCssValue('border'));
        } catch (e) {
            console.log('Элемент по NAME не найден');
        }

        console.log('-------------------------------------');

        // CLASSNAME
        try {
            let elementByName = await driver.findElement(By.className('background-text-annotation'));
            console.log('Найден элемент по CLASSNAME:', await elementByName.getText());
        } catch (e) {
            console.log('Элемент по CLASSNAME не найден');
        }

        console.log('-------------------------------------');

        // TAGNAME
        try {
            let elementByName = await driver.findElement(By.tagName('h2'));
            console.log('Найден элемент по TAGNAME:', await elementByName.getText());
        } catch (e) {
            console.log('Элемент по TAGNAME не найден');
        }

        console.log('-------------------------------------');

        // CSS-селекторы (два составных)
        try {
            let css1 = await driver.findElement(By.css('section.services div:nth-child(1) h4'));
            console.log('CSS-селектор 1:', await css1.getText());
        } catch {
            console.log('CSS-селектор 1 не найден');
        }
        
        try {
            let css2 = await driver.findElement(By.css('section.team div:nth-child(3) p'));
            console.log('CSS-селектор 2:', await css2.getText());
        } catch {
            console.log('CSS-селектор 2 не найден');
        }
        
        try {
            let css3 = await driver.findElement(By.css('body > section.img > section.team > div > div:nth-child(3) > p'));
            console.log('CSS-селектор 3:', await css3.getText());
        } catch {
            console.log('CSS-селектор 3 не найден');
        }

        console.log('-------------------------------------');

        // XPath (два составных)
        try {
            let xpath1 = await driver.findElement(By.xpath('//div[@class="team-container"]//div//h4'));
            console.log('XPath 1:', await xpath1.getText());
        } catch {
            console.log('XPath 1 не найден');
        }

        try {
            let xpath2 = await driver.findElement(By.xpath('//header[@id="header"]//div[contains(@id, "bar2")]'));
            console.log('XPath 2:', await xpath2.getCssValue('background-color'));
        } catch {
            console.log('XPath 2 не найден');
        }

        console.log('-------------------------------------');

        // Частичный текст ссылки
        try {
            let partialLink = await driver.findElement(By.partialLinkText('рис'));
            console.log('Найдена ссылка с текстом "рис":', await partialLink.getAttribute('href'));
        } catch {
            console.log('Ссылка с текстом "рис" не найдена');
        }

        console.log('-------------------------------------');

        // Несколько элементов
        try {
            let items = await driver.findElements(By.css('a'));
            console.log(`Найдено ${items.length} ссылок:`);
            for (let item of items) {
                console.log('-', await item.getText());
            }
        } catch {
            console.log('Не удалось найти список элементов');
        }

    } finally {
        await driver.quit();
    }
}

runUITest();
