#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 4; // Количество строк в матрице кнопок
const byte COLS = 4; // Количество столбцов в матрице кнопок

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};    // Пины для строк
byte colPins[COLS] = {6, 7, 8, 9};    // Пины для столбцов

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char password[] = "1234";  // Задайте свой пароль здесь
char enteredPassword[5];   // Буфер для введенного пароля

void setup() {
  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      // Проверяем введенный пароль
      if (strcmp(enteredPassword, password) == 0) {
        // Пароль верный, выполняем вход в Windows
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
      } else {
        // Пароль неверный, очищаем буфер
        memset(enteredPassword, 0, sizeof(enteredPassword));
      }
    } else {
      // Добавляем символ к введенному паролю
      strncat(enteredPassword, &key, 1);
    }
  }
}