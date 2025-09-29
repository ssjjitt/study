from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class BasePage:
    def __init__(self, browser):
        self.browser = browser

    def find_element(self, by, value):
        return WebDriverWait(self.browser, 10).until(EC.presence_of_element_located((by, value)))

    def find_elements(self, by, value):
        return self.browser.find_elements(by, value)
