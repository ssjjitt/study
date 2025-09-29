from selenium.webdriver.common.by import By
from .BasePage import BasePage

class CartPage(BasePage):
    REMOVE_BUTTON = (By.XPATH, "//button[contains(@class,'btn_secondary') and contains(text(),'Remove')]")
    CART_ITEM = (By.CLASS_NAME, "cart_item")
    CART = (By.CLASS_NAME, "shopping_cart_link")

    def __init__(self, browser):
        super().__init__(browser)

    def remove_product_from_cart(self):
        self.browser.find_element(*self.REMOVE_BUTTON).click()

    def get_cart_items(self):
        return self.browser.find_elements(*self.CART_ITEM)

    def go_to_cart(self):
        self.find_element(*self.CART).click()
