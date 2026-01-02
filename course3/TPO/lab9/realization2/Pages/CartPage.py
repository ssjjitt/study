from selenium.webdriver.common.by import By
from .BasePage import BasePage
from realization2.Locators.CartPageLocators import CartPageLocators

class CartPage(BasePage):
    def __init__(self, browser):
        super().__init__(browser)

    def remove_product_from_cart(self):
        self.browser.find_element(*CartPageLocators.REMOVE_BUTTON).click()

    def get_cart_items(self):
        return self.browser.find_elements(*CartPageLocators.CART_ITEM)
