# 🎯 AI Bot System - Готов к использованию!

## ✅ Что создано

### C++ Классы
- **`ABotCharacter`** - Основной класс бота с системой обнаружения игрока
- **`ABotAIController`** - AI контроллер с Behavior Tree и Blackboard
- **`UBTTask_ChasePlayer`** - Задача преследования игрока
- **`UBTTask_Patrol`** - Задача патрулирования
- **`UBTTask_CheckPlayerVisibility`** - Проверка видимости игрока
- **`ABotTestGameMode`** - Тестовый GameMode для автоматического создания ботов

### Blueprint Assets
- **`BP_BotCharacter`** - Blueprint класс бота
- **`BP_BotAIController`** - Blueprint AI контроллера
- **`BT_BotBehavior`** - Behavior Tree для логики бота
- **`BB_BotBlackboard`** - Blackboard для хранения данных AI
- **`L_BotTest`** - Тестовый уровень

## 🚀 Быстрый старт

### 1. Настройка в редакторе
1. Откройте проект в Unreal Editor
2. Создайте Blueprint класс `BP_BotCharacter`, наследующий от `BotCharacter`
3. Создайте Blueprint класс `BP_BotAIController`, наследующий от `BotAIController`
4. В `BP_BotCharacter` назначьте `BP_BotAIController` как AI Controller Class

### 2. Создание Behavior Tree
1. Создайте Behavior Tree `BT_BotBehavior`
2. Создайте Blackboard `BB_BotBlackboard` с ключами:
   - `Player` (Object) - ссылка на игрока
   - `CanSeePlayer` (Bool) - видит ли бот игрока
   - `LastKnownPlayerLocation` (Vector) - последнее известное местоположение

### 3. Настройка Behavior Tree
```
Selector
├── Sequence (Преследование)
│   ├── CheckPlayerVisibility
│   └── ChasePlayer
└── Patrol (Патрулирование)
```

### 4. Настройка AI Controller
В `BP_BotAIController`:
- Назначьте `BT_BotBehavior` в поле `Bot Behavior Tree`
- Назначьте `BB_BotBlackboard` в поле `Bot Blackboard Asset`

### 5. Тестирование
1. Создайте новый уровень или используйте существующий
2. Добавьте Navigation Mesh (Volume → Nav Mesh Bounds Volume)
3. Установите `BotTestGameMode` как Game Mode по умолчанию
4. Запустите игру - боты создадутся автоматически!

## ⚙️ Настройки

### BotCharacter параметры
- **RunSpeed**: 600 (скорость бега)
- **WalkSpeed**: 300 (скорость ходьбы)
- **DetectionRadius**: 1000 (радиус обнаружения)
- **FieldOfView**: 90 (угол обзора)

### BotAIController параметры
- **SightRadius**: 1000 (радиус зрения)
- **LoseSightRadius**: 1200 (радиус потери зрения)
- **PeripheralVisionAngleDegrees**: 90 (угол периферийного зрения)

## 🎮 Поведение бота

### Состояния
1. **Патрулирование** - Бот случайно перемещается по области
2. **Обнаружение** - При виде игрока переходит в режим преследования
3. **Преследование** - Активно преследует игрока
4. **Поиск** - Идет к последнему известному местоположению игрока

### Особенности
- ✅ Обнаружение игрока по зрению
- ✅ Проверка препятствий (Line Trace)
- ✅ Запоминание последнего местоположения игрока
- ✅ Плавное переключение между состояниями
- ✅ Отладочная визуализация (красные линии к игроку)

## 🔧 Расширение

### Добавление новых состояний
1. Создайте новый BTTask класс
2. Добавьте его в Behavior Tree
3. Настройте переходы между состояниями

### Групповое поведение
- Используйте EQS (Environment Query System) для сложной логики
- Добавьте систему коммуникации между ботами
- Реализуйте координацию атак

### Улучшения
- Система звукового обнаружения
- Память о нескольких позициях игрока
- Различные типы поведения (агрессивный, осторожный, патрульный)

## 📝 Логи и отладка

- Включите `Show Debug Lines` для визуализации обнаружения
- Используйте Behavior Tree Debugger для отслеживания состояний
- Проверяйте Output Log для диагностики проблем

## 🎉 Готово!

Ваш AI бот готов к использованию! Он будет:
- Патрулировать по уровню
- Обнаруживать игрока при приближении
- Преследовать игрока до потери из виду
- Возвращаться к патрулированию

Удачной разработки! 🚀



