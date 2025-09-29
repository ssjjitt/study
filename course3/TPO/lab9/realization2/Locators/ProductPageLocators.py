from selenium.webdriver.common.by import By

class ProductPageLocators:
    FIRST_PRODUCT_BUTTON = (By.XPATH, "(//button[contains(@class,'btn_inventory')])[1]")
    CART_ICON = (By.CLASS_NAME, "shopping_cart_badge")
