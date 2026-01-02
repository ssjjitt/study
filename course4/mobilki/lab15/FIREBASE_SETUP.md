# Firebase Setup Instructions

## Требования

1. Установите FlutterFire CLI:
```bash
dart pub global activate flutterfire_cli
```

2. Настройте Firebase проект:
```bash
flutterfire configure
```

Это создаст файл `lib/firebase_options.dart` с конфигурацией вашего Firebase проекта.

## Настройка Firebase Services

### 1. Firestore
- Создайте Firestore Database в Firebase Console
- Включите режим разработки (Development mode) или настройте правила безопасности

### 2. Authentication
- Включите Email/Password провайдер в Firebase Console > Authentication > Sign-in method
- Включите Google Sign-In провайдер (требуется настройка OAuth)

### 3. Realtime Database
- Создайте Realtime Database в Firebase Console
- Настройте правила безопасности:
```json
{
  "rules": {
    "userStatus": {
      "$uid": {
        ".read": "$uid === auth.uid",
        ".write": "$uid === auth.uid"
      }
    }
  }
}
```

### 4. Cloud Messaging
- Настройка выполняется автоматически при первом запуске
- Для Android: добавьте `google-services.json` в `android/app/`
- Для iOS: добавьте `GoogleService-Info.plist` в `ios/Runner/`

### 5. Remote Config
- Настройте параметры в Firebase Console > Remote Config:
  - `like_button_enabled` (boolean): включить/выключить кнопку like
  - `block_color` (string): цвет блока (формат: #RRGGBB, например #F5C78E)

### 6. Analytics
- Включите Google Analytics в Firebase Console
- События логируются автоматически

## Структура Firestore

### Коллекция `hotels`
```
hotels/{hotelId}
  - title: string
  - place: string
  - price: number
  - rating: number
  - reviews: string
  - image: string
  - description: string
```

### Коллекция `favorites`
```
favorites/{favoriteId}
  - userId: string
  - hotelId: string
  - addedAt: timestamp
```

### Коллекция `users`
```
users/{userId}
  - name: string
  - email: string
  - role: string ("user" или "admin")
  - createdAt: timestamp
```

## Структура Realtime Database

```
userStatus/{userId}
  - status: string ("online" или "offline")
  - lastSeen: timestamp
  - lastActivity: timestamp
```

## Примечания

- Приложение поддерживает офлайн-режим Firestore (автоматическая синхронизация)
- Все данные синхронизируются при восстановлении подключения к интернету
- Статус пользователя обновляется автоматически при входе/выходе

