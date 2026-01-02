from selenium.webdriver.common.by import By

class CartPageLocators:
    REMOVE_BUTTON = (By.XPATH, "//button[contains(@class,'btn_secondary') and contains(text(),'Remove')]")
    CART_ITEM = (By.CLASS_NAME, "cart_item")