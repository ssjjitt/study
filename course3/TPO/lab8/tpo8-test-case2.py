import pytest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

@pytest.fixture
def browser():
    print("start browser for test..")
    chrome_options = Options()
    chrome_options.add_argument("--disable-notifications")
    chrome_options.add_argument("--disable-popup-blocking")
    chrome_options.add_argument("--disable-save-password-bubble")
    browser = webdriver.Chrome(options=chrome_options)
    yield browser
    print("quit browser..")
    browser.quit()

@pytest.fixture(autouse=True)
def prepare_data():
    print("preparing some critical data for every test..")

@pytest.mark.regression
def test_delete_from_main(browser):
    browser.get("https://www.saucedemo.com")
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.ID, "user-name")))

    username = browser.find_element(By.ID, "user-name")
    username.send_keys("standard_user")
    print("username введен успешно")

    password = browser.find_element(By.ID, "password")
    password.send_keys("secret_sauce")
    print("password введен успешно")

    password.send_keys(Keys.RETURN)
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "inventory_list")))
    print("успешно загрузился список товаров")

    first_product = browser.find_element(By.XPATH, "(//button[contains(@class,'btn_inventory')])[1]")
    first_product.click()
    print("товар успешно добавлен в корзину")

    remove_button_on_product_page = WebDriverWait(browser, 10).until(
        EC.presence_of_element_located((By.XPATH, "(//button[contains(@class,'btn_inventory')])[1]"))
    )
    remove_button_on_product_page.click()
    print("товар удален с главной страницы")



    cart_items_after_removal = browser.find_elements(By.CLASS_NAME, "cart_item")
    assert len(cart_items_after_removal) == 0, "товар все еще есть в корзине после удаления"

    print("тест завершен успешно")
