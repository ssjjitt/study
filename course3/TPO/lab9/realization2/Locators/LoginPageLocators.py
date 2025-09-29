from selenium.webdriver.common.by import By

class LoginPageLocators:
    USERNAME = (By.ID, "user-name")
    PASSWORD = (By.ID, "password")
    LOGIN_BUTTON = (By.XPATH, "//input[@value='Login']")
