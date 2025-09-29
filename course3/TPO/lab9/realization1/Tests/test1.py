import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from realization1.Pages.LoginPage import LoginPage
from realization1.Pages.ProductPage import ProductPage
from realization1.Pages.CartPage import CartPage

@pytest.fixture
def browser():
    chrome_options = Options()
    browser = webdriver.Chrome(options=chrome_options)
    yield browser
    browser.quit()

@pytest.mark.smoke
def test_delete_from_cart(browser):
    login_page = LoginPage(browser)
    product_page = ProductPage(browser)
    cart_page = CartPage(browser)

    browser.get("https://www.saucedemo.com")

    login_page.login("standard_user", "secret_sauce")

    product_page.add_product_to_cart()

    cart_page.go_to_cart()
    cart_page.remove_product_from_cart()

    assert len(cart_page.get_cart_items()) == 0, "Товар все еще есть в корзине"

    print("Тест успешно завершен")
