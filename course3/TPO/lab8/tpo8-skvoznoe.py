import pytest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


@pytest.fixture
def browser():
    print("start browser for test..")
    driver = webdriver.Chrome()
    yield driver
    print("quit browser..")
    driver.quit()


def login(browser, username_value, password_value):
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.ID, "user-name")))
    username = browser.find_element(By.ID, "user-name")
    username.send_keys(username_value)
    print(f"username {username_value} введен успешно")

    password = browser.find_element(By.ID, "password")
    password.send_keys(password_value)
    print(f"password {password_value} введен успешно")

    password.send_keys(Keys.RETURN)
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "inventory_list")))
    print("успешно загрузился список товаров")

    inventory_list = browser.find_elements(By.CLASS_NAME, "inventory_item")
    assert len(inventory_list) > 0, "товары не найдены на странице"
    print(f"найдено {len(inventory_list)} товара(ов) на странице.")


def add_product_to_cart(browser):
    product_buttons = browser.find_elements(By.XPATH, "//button[contains(@class,'btn_inventory')]")
    assert len(product_buttons) > 0, "нет товаров для добавления в корзину"

    first_product = browser.find_element(By.XPATH, "(//button[contains(@class,'btn_inventory')])[1]")
    first_product.click()
    print("товар успешно добавлен в корзину")

    cart_icon = browser.find_element(By.CLASS_NAME, "shopping_cart_badge")
    assert cart_icon.text == "1", f"корзина не содержит 1 товар, а содержит {cart_icon.text} товаров."
    print(f"товар добавлен в корзину. количество товаров в корзине: {cart_icon.text}")


def go_to_cart_and_verify(browser):
    cart_button = WebDriverWait(browser, 10).until(
        EC.presence_of_element_located((By.CLASS_NAME, "shopping_cart_link"))
    )
    cart_button.click()
    print("перешли в корзину")

    product_name_in_cart = browser.find_element(By.CLASS_NAME, "inventory_item_name").text
    assert product_name_in_cart != "", f"Товар не найден в корзине. Ожидался товар, но найдено: {product_name_in_cart}"
    print(f"товар в корзине: {product_name_in_cart}")


def checkout(browser):
    checkout_button = browser.find_element(By.CLASS_NAME, "checkout_button")
    checkout_button.click()
    print("чекаут успешно выполнен")

    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "checkout_info")))

    checkout_info = browser.find_element(By.CLASS_NAME, "checkout_info")
    assert checkout_info is not None, "не удалось перейти на страницу чекаута"
    print("тест завершен успешно")


@pytest.mark.smoke
def test_checkout(browser):
    browser.get("https://www.saucedemo.com")

    login(browser, "standard_user", "secret_sauce")

    add_product_to_cart(browser)

    go_to_cart_and_verify(browser)

    checkout(browser)
