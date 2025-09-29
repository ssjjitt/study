import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from meow.Pages.LoginPage import LoginPage


@pytest.fixture
def browser():
    chrome_options = Options()
    chrome_options.add_argument("--start-maximized")
    chrome_options.add_argument("--disable-notifications")
    chrome_options.add_argument("--headless")
    browser = webdriver.Chrome(options=chrome_options)
    yield browser
    browser.quit()


@pytest.mark.parametrize("username, password", [
    ("visual_user", "secret_sauce"),
    ("standard_user", "secret_sauce")
])

def test_login_with_multiple_credentials(browser, username, password):
    browser.get("https://www.saucedemo.com")

    login_page = LoginPage(browser)
    login_page.login(username, password)

    assert "Swag Labs" in browser.title, f"Ошибка! Ожидался заголовок 'Swag Labs', но был '{browser.title}'"

    browser.save_screenshot(f"{username}_login_success.png")
    print(f"Скриншот для {username} после авторизации сохранен")

@pytest.mark.skip(reason="Этот тест временно пропущен")
def test_skip(browser):
    username = "meow"
    password = "meowwww"
    browser.get("https://www.saucedemo.com")

    login_page = LoginPage(browser)
    login_page.login(username, password)

    assert "Swag Labs" in browser.title, f"Ошибка! Ожидался заголовок 'Swag Labs', но был '{browser.title}'"

@pytest.mark.xfail
def test_skip(browser):
    username = "meow"
    password = "meowwww"
    browser.get("https://www.saucedemo.com")

    login_page = LoginPage(browser)
    login_page.login(username, password)

    assert "Swag Labs" in browser.title, f"Ошибка! Ожидался заголовок 'Swag Labs', но был '{browser.title}'"
