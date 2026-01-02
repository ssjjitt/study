# Лабораторная работа №13: Unit Tests, Widget Tests, Integration Tests

## Выполненные задачи

### ✅ 1. Unit-тесты (минимум 5 тестов с использованием Mockito)

Создано **15 unit-тестов** в следующих файлах:

1. **test/unit_tests/firestore_service_test.dart** (5 тестов)
   - getHotels возвращает список отелей
   - addHotel добавляет отель в Firestore
   - updateHotel обновляет отель в Firestore
   - deleteHotel удаляет отель из Firestore
   - getFavorites возвращает список избранного

2. **test/unit_tests/auth_service_test.dart** (5 тестов)
   - registerWithEmailPassword создает пользователя
   - signInWithEmailPassword аутентифицирует пользователя
   - signOut выходит из системы
   - getAppUser получает данные пользователя
   - sendPasswordResetEmail отправляет письмо для сброса пароля

3. **test/unit_tests/hotels_bloc_test.dart** (5 тестов)
   - Загрузка отелей (успешная)
   - Загрузка отелей (ошибка)
   - Добавление отеля
   - Обновление отеля
   - Удаление отеля

4. **test/unit_tests/auth_bloc_test.dart** (5 тестов)
   - Успешный вход
   - Ошибка входа
   - Успешная регистрация
   - Выход из системы
   - Отправка сброса пароля

5. **test/unit_tests/favorites_bloc_test.dart** (5 тестов)
   - Загрузка избранного (успешная)
   - Загрузка избранного (ошибка)
   - Переключение избранного
   - Удаление из избранного
   - Проверка статуса избранного

**Всего: 25 unit-тестов** (превышает требование минимум 5)

### ✅ 2. Widget-тесты (минимум 5 тестов с enterText, Tap, Drag)

Создано **5+ widget-тестов** в следующих файлах:

1. **test/widget_tests/login_page_test.dart**
   - ✅ enterText: ввод email
   - ✅ enterText: ввод пароля
   - ✅ Tap: нажатие кнопки входа
   - ✅ Tap: нажатие кнопки "Забыли пароль?"

2. **test/widget_tests/register_page_test.dart**
   - ✅ enterText: ввод имени
   - ✅ enterText: ввод всех полей формы
   - ✅ Tap: нажатие кнопки регистрации

3. **test/widget_tests/add_hotel_page_test.dart**
   - ✅ enterText: ввод названия отеля
   - ✅ enterText: ввод цены
   - ✅ Tap: нажатие кнопки добавления отеля

4. **test/widget_tests/hotel_detail_page_test.dart**
   - ✅ Tap: нажатие кнопки избранного
   - ✅ Drag: перетаскивание PageView галереи

5. **test/widget_tests/home_page_test.dart**
   - ✅ Tap: нажатие кнопки поиска
   - ✅ Drag: перетаскивание горизонтального ListView отелей
   - ✅ Tap: нажатие элемента нижней навигации
   - ✅ Drag: перетаскивание категорий

**Всего: 13+ widget-тестов** с использованием enterText, Tap и Drag

### ✅ 3. Integration-тесты (3 теста)

Создано **3 integration-теста**:

1. **integration_test/admin_add_hotel_test.dart**
   - Тест добавления отеля администратором через админ-панель
   - Проверка полного flow: вход → админ-панель → добавление → проверка

2. **integration_test/user_favorites_test.dart**
   - Тест добавления отеля в избранное пользователем
   - Тест удаления отеля из избранного
   - Проверка отображения избранного на странице

3. **integration_test/user_info_test.dart**
   - Тест просмотра информации о пользователе
   - Тест отображения кнопки админ-панели для администратора
   - Тест выхода из системы

## Структура проекта

```
lab11/
├── test/
│   ├── unit_tests/
│   │   ├── firestore_service_test.dart
│   │   ├── auth_service_test.dart
│   │   ├── hotels_bloc_test.dart
│   │   ├── auth_bloc_test.dart
│   │   └── favorites_bloc_test.dart
│   ├── widget_tests/
│   │   ├── login_page_test.dart
│   │   ├── register_page_test.dart
│   │   ├── add_hotel_page_test.dart
│   │   ├── hotel_detail_page_test.dart
│   │   └── home_page_test.dart
│   ├── README_TESTS.md
│   └── GENERATE_MOCKS.md
├── integration_test/
│   ├── admin_add_hotel_test.dart
│   ├── user_favorites_test.dart
│   └── user_info_test.dart
└── pubspec.yaml (обновлен с зависимостями для тестирования)
```

## Зависимости

Добавлены в `pubspec.yaml`:
- `mockito: ^5.4.4` - для создания моков
- `integration_test` - для integration-тестов
- `bloc_test: ^9.1.5` - для тестирования BLoC'ов

## Запуск тестов

### Генерация моков (обязательно перед первым запуском):
```bash
flutter pub run build_runner build --delete-conflicting-outputs
```

### Запуск всех тестов:
```bash
flutter test
```

### Запуск только unit-тестов:
```bash
flutter test test/unit_tests/
```

### Запуск только widget-тестов:
```bash
flutter test test/widget_tests/
```

### Запуск integration-тестов:
```bash
flutter test integration_test/
```

## Ответы на вопросы лабораторной работы

Ответы на все вопросы находятся в файле `test/README_TESTS.md`:
1. Что такое unit-тест. Назначение.
2. Что такое widget-тест. Назначение.
3. Что такое integration-тест. Назначение.
4. Библиотека Mockito. Назначение.

## Примечания

- Все тесты используют Mockito для изоляции зависимостей
- Widget-тесты покрывают все требуемые взаимодействия: enterText, Tap, Drag
- Integration-тесты структурированы для работы с Firebase (требуется настройка окружения)
- Для генерации моков используется build_runner
- Все тесты следуют best practices Flutter тестирования

