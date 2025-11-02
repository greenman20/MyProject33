# 📋 Пошаговая инструкция создания Blueprint классов

## 🎯 Создание Blueprint классов в Unreal Editor

### 1. Создание BP_BotCharacter

1. **Откройте Content Browser**
   - В Content Browser нажмите правой кнопкой мыши
   - Выберите `Blueprint Class`

2. **Выберите родительский класс**
   - В окне `Pick Parent Class` найдите `BotCharacter`
   - Если не видите, убедитесь, что проект скомпилирован
   - Нажмите `Select`

3. **Назовите Blueprint**
   - Назовите его `BP_BotCharacter`
   - Сохраните в папке `Content/Blueprints/`

4. **Настройте Blueprint**
   - Откройте `BP_BotCharacter`
   - В `Details` панели найдите `AI Controller Class`
   - Пока оставьте пустым (настроим позже)

### 2. Создание BP_BotAIController

1. **Создайте новый Blueprint Class**
   - Content Browser → Right Click → `Blueprint Class`

2. **Выберите родительский класс**
   - Найдите `BotAIController` в списке
   - Нажмите `Select`

3. **Назовите Blueprint**
   - Назовите его `BP_BotAIController`
   - Сохраните в папке `Content/Blueprints/`

4. **Настройте AI Controller**
   - Откройте `BP_BotAIController`
   - В `Details` панели найдите секцию `AI`
   - Пока оставьте поля `Bot Behavior Tree` и `Bot Blackboard Asset` пустыми

### 3. Создание BB_BotBlackboard

1. **Создайте Blackboard**
   - Content Browser → Right Click → `Miscellaneous` → `Blackboard`
   - Назовите его `BB_BotBlackboard`
   - Сохраните в папке `Content/AI/`

2. **Добавьте ключи Blackboard**
   - Откройте `BB_BotBlackboard`
   - Нажмите `New Key` → `Object`
   - Назовите ключ `Player`
   - Тип: `Object`
   - Base Class: `Actor`

3. **Добавьте остальные ключи**
   - `New Key` → `Bool` → `CanSeePlayer`
   - `New Key` → `Vector` → `LastKnownPlayerLocation`

### 4. Создание BT_BotBehavior

1. **Создайте Behavior Tree**
   - Content Browser → Right Click → `Miscellaneous` → `Behavior Tree`
   - Назовите его `BT_BotBehavior`
   - Сохраните в папке `Content/AI/`

2. **Настройте Behavior Tree**
   - Откройте `BT_BotBehavior`
   - В `Details` панели найдите `Blackboard Asset`
   - Назначьте `BB_BotBlackboard`

3. **Создайте структуру дерева**
   - Перетащите `Selector` из палитры в корень дерева
   - Под `Selector` добавьте `Sequence`
   - Под `Sequence` добавьте `Sequence` (для патрулирования)

### 5. Настройка Behavior Tree Tasks

1. **Добавьте CheckPlayerVisibility**
   - В палитре найдите `CheckPlayerVisibility`
   - Перетащите под первый `Sequence`

2. **Добавьте ChasePlayer**
   - Найдите `ChasePlayer` в палитре
   - Перетащите под `CheckPlayerVisibility`

3. **Добавьте Patrol**
   - Найдите `Patrol` в палитре
   - Перетащите под второй `Sequence`

### 6. Настройка BP_BotAIController

1. **Откройте BP_BotAIController**
2. **Назначьте Behavior Tree и Blackboard**
   - `Bot Behavior Tree` → `BT_BotBehavior`
   - `Bot Blackboard Asset` → `BB_BotBlackboard`

### 7. Настройка BP_BotCharacter

1. **Откройте BP_BotCharacter**
2. **Назначьте AI Controller**
   - `AI Controller Class` → `BP_BotAIController`

### 8. Создание тестового уровня

1. **Создайте новый уровень**
   - File → New Level → `Open World`
   - Сохраните как `L_BotTest`

2. **Добавьте Navigation Mesh**
   - Place Actors → Volumes → `Nav Mesh Bounds Volume`
   - Разместите и масштабируйте для покрытия уровня

3. **Разместите бота**
   - Перетащите `BP_BotCharacter` на уровень
   - Разместите в подходящем месте

4. **Настройте Game Mode**
   - Edit → Project Settings → Maps & Modes
   - `Default GameMode` → `BotTestGameMode`

### 9. Тестирование

1. **Запустите игру**
   - Нажмите `Play`
   - Бот должен появиться и начать патрулирование

2. **Проверьте поведение**
   - Подойдите к боту
   - Он должен начать преследование
   - Отойдите - он должен вернуться к патрулированию

## 🔧 Дополнительные настройки

### Настройка параметров бота
В `BP_BotCharacter` можно настроить:
- `Run Speed` - скорость бега
- `Walk Speed` - скорость ходьбы
- `Detection Radius` - радиус обнаружения
- `Field Of View` - угол обзора

### Настройка AI Controller
В `BP_BotAIController` можно настроить:
- `Sight Radius` - радиус зрения
- `Lose Sight Radius` - радиус потери зрения
- `Peripheral Vision Angle` - угол периферийного зрения

## 🎉 Готово!

Теперь у вас есть полностью функциональная система AI бота! Бот будет:
- Патрулировать по уровню
- Обнаруживать игрока при приближении
- Преследовать игрока
- Возвращаться к патрулированию при потере игрока

Удачного тестирования! 🚀



