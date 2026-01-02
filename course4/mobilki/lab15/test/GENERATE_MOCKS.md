# Инструкция по генерации моков для тестов

## Шаг 1: Установка зависимостей

Убедитесь, что все зависимости установлены:
```bash
flutter pub get
```

## Шаг 2: Генерация моков

Запустите build_runner для генерации мок-файлов:
```bash
flutter pub run build_runner build --delete-conflicting-outputs
```

Или используйте watch режим для автоматической регенерации при изменениях:
```bash
flutter pub run build_runner watch --delete-conflicting-outputs
```

## Шаг 3: Проверка сгенерированных файлов

После генерации должны появиться следующие файлы:
- `test/unit_tests/firestore_service_test.mocks.dart`
- `test/unit_tests/auth_service_test.mocks.dart`
- `test/unit_tests/hotels_bloc_test.mocks.dart`
- `test/unit_tests/auth_bloc_test.mocks.dart`
- `test/unit_tests/favorites_bloc_test.mocks.dart`
- `test/widget_tests/login_page_test.mocks.dart`
- `test/widget_tests/register_page_test.mocks.dart`
- `test/widget_tests/add_hotel_page_test.mocks.dart`
- `test/widget_tests/hotel_detail_page_test.mocks.dart`
- `test/widget_tests/home_page_test.mocks.dart`

## Шаг 4: Запуск тестов

После генерации моков можно запускать тесты:
```bash
flutter test
```

## Примечания

- Если возникают ошибки при генерации, убедитесь, что все аннотации `@GenerateMocks` правильно указаны
- При изменении интерфейсов классов, для которых созданы моки, необходимо регенерировать моки
- Флаг `--delete-conflicting-outputs` автоматически удаляет конфликтующие файлы

