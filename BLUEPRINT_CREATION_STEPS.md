# 🎯 Создание Blueprint классов в Unreal Editor

## ✅ Статус:
- ✅ Все C++ классы готовы и скомпилированы
- ✅ Редактор Unreal Engine запущен
- ✅ Папки Content/Blueprints и Content/AI созданы
- ✅ Готов к созданию Blueprint классов

## 🚀 Пошаговое создание Blueprint классов

### 1. BP_BotCharacter

1. **Откройте Content Browser**
2. **Создайте Blueprint Class**
   - Right Click в Content Browser
   - Выберите `Blueprint Class`
   - В окне `Pick Parent Class` найдите `BotCharacter`
   - Если не видите, убедитесь, что проект скомпилирован
   - Нажмите `Select`

3. **Назовите и сохраните**
   - Назовите `BP_BotCharacter`
   - Сохраните в папку `Content/Blueprints/`

4. **Настройте Blueprint**
   - Откройте `BP_BotCharacter`
   - В `Details` панели найдите `AI Controller Class`
   - Пока оставьте пустым (настроим позже)

### 2. BP_BotAIController

1. **Создайте Blueprint Class**
   - Right Click → `Blueprint Class`
   - Найдите `BotAIController` в списке
   - Нажмите `Select`

2. **Назовите и сохраните**
   - Назовите `BP_BotAIController`
   - Сохраните в `Content/Blueprints/`

3. **Настройте AI Controller**
   - Откройте `BP_BotAIController`
   - В `Details` панели найдите секцию `AI`
   - Пока оставьте поля `Bot Behavior Tree` и `Bot Blackboard Asset` пустыми

### 3. BB_BotBlackboard

1. **Создайте Blackboard**
   - Right Click → `Miscellaneous` → `Blackboard`
   - Назовите `BB_BotBlackboard`
   - Сохраните в `Content/AI/`

2. **Добавьте ключи Blackboard**
   - Откройте `BB_BotBlackboard`
   - Нажмите `New Key` → `Object`
   - Назовите ключ `Player`
   - Тип: `Object`
   - Base Class: `Actor`

3. **Добавьте остальные ключи**
   - `New Key` → `Bool` → `CanSeePlayer`
   - `New Key` → `Vector` → `LastKnownPlayerLocation`

### 4. BT_BotBehavior

1. **Создайте Behavior Tree**
   - Right Click → `Miscellaneous` → `Behavior Tree`
   - Назовите `BT_BotBehavior`
   - Сохраните в `Content/AI/`

2. **Настройте Behavior Tree**
   - Откройте `BT_BotBehavior`
   - В `Details` панели найдите `Blackboard Asset`
   - Назначьте `BB_BotBlackboard`

3. **Создайте структуру дерева**
   - Перетащите `Selector` из палитры в корень дерева
   - Под `Selector` добавьте `Sequence` (для преследования)
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

### 8. BP_ThirdPersonGameMode

1. **Создайте Blueprint Class**
   - Right Click → `Blueprint Class`
   - Найдите `MyProject3GameMode` в списке
   - Нажмите `Select`

2. **Назовите и сохраните**
   - Назовите `BP_ThirdPersonGameMode`
   - Сохраните в `Content/Blueprints/`

3. **Настройте AI Bot Settings**
   - Откройте `BP_ThirdPersonGameMode`
   - В `Details` панели найдите секцию `AI Bot Settings`
   - `Bot Class` → `BP_BotCharacter`
   - `Number Of Bots` → `2`
   - `Bot Spawn Radius` → `800`
   - `Min Spawn Distance` → `300`
   - `Auto Spawn Bots` → `True`

### 9. Настройка уровня Lvl_ThirdPerson

1. **Откройте уровень Lvl_ThirdPerson**
2. **Настройте Game Mode**
   - `Edit` → `Project Settings` → `Maps & Modes`
   - `Default GameMode` → `BP_ThirdPersonGameMode`

### 10. Тестирование

1. **Запустите игру**
   - Нажмите `Play`
   - Через 2 секунды должны появиться AI боты

2. **Проверьте поведение**
   - Боты должны патрулировать по уровню
   - При приближении игрока боты должны начать преследование
   - При потере игрока боты должны вернуться к патрулированию

## 🎉 Готово!

После выполнения всех шагов у вас будет полностью функциональная система AI ботов, интегрированная с уровнем Lvl_ThirdPerson!

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

Удачного создания Blueprint классов! 🤖✨



