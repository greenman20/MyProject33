# 🎯 Настройка AI ботов для уровня Lvl_ThirdPerson

## ✅ Что готово:
- ✅ Уровень `Lvl_ThirdPerson` существует
- ✅ Navigation Mesh добавлен
- ✅ `AMyProject3GameMode` модифицирован для поддержки AI ботов
- ✅ Проект скомпилирован без ошибок

## 🚀 Пошаговая настройка Blueprint классов

### 1. Создание BP_BotCharacter

1. **Откройте Content Browser**
2. **Создайте Blueprint Class**
   - Right Click → `Blueprint Class`
   - Найдите `BotCharacter` в списке классов
   - Нажмите `Select`
3. **Назовите Blueprint**
   - Назовите `BP_BotCharacter`
   - Сохраните в `Content/Blueprints/`

### 2. Создание BP_BotAIController

1. **Создайте Blueprint Class**
   - Right Click → `Blueprint Class`
   - Найдите `BotAIController` в списке
   - Нажмите `Select`
2. **Назовите Blueprint**
   - Назовите `BP_BotAIController`
   - Сохраните в `Content/Blueprints/`

### 3. Создание BB_BotBlackboard

1. **Создайте Blackboard**
   - Right Click → `Miscellaneous` → `Blackboard`
   - Назовите `BB_BotBlackboard`
   - Сохраните в `Content/AI/`

2. **Добавьте ключи Blackboard**
   - Откройте `BB_BotBlackboard`
   - Нажмите `New Key` → `Object`
   - Назовите `Player`
   - Base Class: `Actor`

3. **Добавьте остальные ключи**
   - `New Key` → `Bool` → `CanSeePlayer`
   - `New Key` → `Vector` → `LastKnownPlayerLocation`

### 4. Создание BT_BotBehavior

1. **Создайте Behavior Tree**
   - Right Click → `Miscellaneous` → `Behavior Tree`
   - Назовите `BT_BotBehavior`
   - Сохраните в `Content/AI/`

2. **Настройте Behavior Tree**
   - Откройте `BT_BotBehavior`
   - В `Details` панели найдите `Blackboard Asset`
   - Назначьте `BB_BotBlackboard`

3. **Создайте структуру дерева**
   ```
   Selector
   ├── Sequence (Преследование)
   │   ├── CheckPlayerVisibility
   │   └── ChasePlayer
   └── Sequence (Патрулирование)
       └── Patrol
   ```

### 5. Настройка BP_BotAIController

1. **Откройте BP_BotAIController**
2. **Назначьте Behavior Tree и Blackboard**
   - `Bot Behavior Tree` → `BT_BotBehavior`
   - `Bot Blackboard Asset` → `BB_BotBlackboard`

### 6. Настройка BP_BotCharacter

1. **Откройте BP_BotCharacter**
2. **Назначьте AI Controller**
   - `AI Controller Class` → `BP_BotAIController`

### 7. Создание BP_ThirdPersonGameMode

1. **Создайте Blueprint Class**
   - Right Click → `Blueprint Class`
   - Найдите `MyProject3GameMode` в списке
   - Нажмите `Select`
2. **Назовите Blueprint**
   - Назовите `BP_ThirdPersonGameMode`
   - Сохраните в `Content/Blueprints/`

3. **Настройте AI Bot Settings**
   - Откройте `BP_ThirdPersonGameMode`
   - В `Details` панели найдите секцию `AI Bot Settings`
   - `Bot Class` → `BP_BotCharacter`
   - `Number Of Bots` → `2` (или желаемое количество)
   - `Bot Spawn Radius` → `800`
   - `Min Spawn Distance` → `300`
   - `Auto Spawn Bots` → `True`

### 8. Настройка уровня Lvl_ThirdPerson

1. **Откройте уровень Lvl_ThirdPerson**
2. **Настройте Game Mode**
   - `Edit` → `Project Settings` → `Maps & Modes`
   - `Default GameMode` → `BP_ThirdPersonGameMode`

3. **Проверьте Navigation Mesh**
   - Убедитесь, что `Nav Mesh Bounds Volume` покрывает всю игровую область
   - Если нужно, добавьте дополнительные Nav Mesh Volumes

### 9. Тестирование

1. **Запустите игру**
   - Нажмите `Play`
   - Через 2 секунды должны появиться AI боты

2. **Проверьте поведение**
   - Боты должны патрулировать по уровню
   - При приближении игрока боты должны начать преследование
   - При потере игрока боты должны вернуться к патрулированию

## 🔧 Дополнительные настройки

### Настройка параметров бота в BP_BotCharacter
- `Run Speed`: 600 (скорость бега)
- `Walk Speed`: 300 (скорость ходьбы)
- `Detection Radius`: 1000 (радиус обнаружения)
- `Field Of View`: 90 (угол обзора)

### Настройка AI Controller в BP_BotAIController
- `Sight Radius`: 1000 (радиус зрения)
- `Lose Sight Radius`: 1200 (радиус потери зрения)
- `Peripheral Vision Angle`: 90 (угол периферийного зрения)

### Настройка Game Mode в BP_ThirdPersonGameMode
- `Number Of Bots`: Количество ботов для создания
- `Bot Spawn Radius`: Максимальный радиус размещения
- `Min Spawn Distance`: Минимальное расстояние от игрока
- `Auto Spawn Bots`: Автоматическое создание при старте

## 🎉 Готово!

Теперь ваш уровень `Lvl_ThirdPerson` будет автоматически создавать AI ботов при запуске игры. Боты будут:
- Патрулировать по уровню
- Обнаруживать ThirdPerson персонажа
- Преследовать игрока
- Возвращаться к патрулированию при потере игрока

Удачного тестирования! 🤖✨



