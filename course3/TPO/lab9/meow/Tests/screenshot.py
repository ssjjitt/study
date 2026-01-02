import json
import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from meow.Pages.LoginPage import LoginPage
from meow.Pages.ProductPage import ProductPage
from meow.Pages.CartPage import CartPage
import time

@pytest.fixture
def browser():
    chrome_options = Options()
    chrome_options.add_argument("--start-maximized")
    chrome_options.add_argument("--disable-notifications")
    chrome_options.add_argument("--headless")
    browser = webdriver.Chrome(options=chrome_options)
    yield browser
    browser.quit()


@pytest.mark.smoke
def test_take_screenshot(browser):
    browser.get("https://www.saucedemo.com")
    login_page = LoginPage(browser)
    login_page.login("standard_user", "secret_sauce")
    cookies = browser.get_cookies()

    with open("cookies.json", "w") as f:
        json.dump(cookies, f)
    print("Куки сохранены")

    browser.save_screenshot("screenshot_before_login.png")
    print("Скриншот до авторизации сохранен")


@pytest.fixture
def load_cookies(browser):
    browser.get("https://www.saucedemo.com")
    with open("cookies.json", "r") as f:
        cookies = json.load(f)
        for cookie in cookies:
            browser.add_cookie(cookie)
    time.sleep(2)
    browser.refresh()
    yield browser


@pytest.mark.smoke
def test__with_cookies(load_cookies):
    browser = load_cookies
    browser.get("https://www.saucedemo.com")
    assert "Swag Labs" in browser.title, "Не удалось авторизоваться"
