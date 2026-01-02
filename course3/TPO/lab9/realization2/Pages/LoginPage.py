from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from .BasePage import BasePage  # Импортируем BasePage
from realization2.Locators.LoginPageLocators import LoginPageLocators

class LoginPage(BasePage):
    def __init__(self, browser):
        super().__init__(browser)

    def login(self, username, password):
        self.browser.find_element(*LoginPageLocators.USERNAME).send_keys(username)
        self.browser.find_element(*LoginPageLocators.PASSWORD).send_keys(password)
        self.browser.find_element(*LoginPageLocators.PASSWORD).send_keys(Keys.RETURN)
