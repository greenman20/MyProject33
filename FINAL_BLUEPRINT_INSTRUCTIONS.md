# 🎯 Финальная инструкция создания Blueprint классов

## ✅ Все готово для создания Blueprint классов!

### 🚀 Пошаговое создание в Unreal Editor:

## 1. BP_BotCharacter
**Шаги:**
1. Откройте **Content Browser**
2. **Right Click** в пустом месте
3. Выберите **Blueprint Class**
4. В окне **Pick Parent Class** найдите **BotCharacter**
5. Нажмите **Select**
6. Назовите **BP_BotCharacter**
7. Сохраните в папку **Content/Blueprints/**

## 2. BP_BotAIController
**Шаги:**
1. **Right Click** в Content Browser
2. Выберите **Blueprint Class**
3. Найдите **BotAIController** в списке
4. Нажмите **Select**
5. Назовите **BP_BotAIController**
6. Сохраните в **Content/Blueprints/**

## 3. BB_BotBlackboard
**Шаги:**
1. **Right Click** в Content Browser
2. Выберите **Miscellaneous** → **Blackboard**
3. Назовите **BB_BotBlackboard**
4. Сохраните в **Content/AI/**

**Добавление ключей:**
1. Откройте **BB_BotBlackboard**
2. Нажмите **New Key** → **Object**
3. Назовите **Player**, Base Class: **Actor**
4. **New Key** → **Bool** → **CanSeePlayer**
5. **New Key** → **Vector** → **LastKnownPlayerLocation**

## 4. BT_BotBehavior
**Шаги:**
1. **Right Click** в Content Browser
2. Выберите **Miscellaneous** → **Behavior Tree**
3. Назовите **BT_BotBehavior**
4. Сохраните в **Content/AI/**

**Настройка:**
1. Откройте **BT_BotBehavior**
2. В **Details** панели найдите **Blackboard Asset**
3. Назначьте **BB_BotBlackboard**

**Создание структуры:**
1. Перетащите **Selector** из палитры в корень дерева
2. Под **Selector** добавьте **Sequence** (для преследования)
3. Под **Sequence** добавьте **Sequence** (для патрулирования)
4. В первый **Sequence** добавьте **CheckPlayerVisibility** и **ChasePlayer**
5. Во второй **Sequence** добавьте **Patrol**

## 5. BP_ThirdPersonGameMode
**Шаги:**
1. **Right Click** в Content Browser
2. Выберите **Blueprint Class**
3. Найдите **MyProject3GameMode** в списке
4. Нажмите **Select**
5. Назовите **BP_ThirdPersonGameMode**
6. Сохраните в **Content/Blueprints/**

**Настройка AI Bot Settings:**
1. Откройте **BP_ThirdPersonGameMode**
2. В **Details** панели найдите секцию **AI Bot Settings**
3. **Bot Class** → **BP_BotCharacter**
4. **Number Of Bots** → **2**
5. **Bot Spawn Radius** → **800**
6. **Min Spawn Distance** → **300**
7. **Auto Spawn Bots** → **True**

## 6. Настройка связей

### BP_BotAIController:
1. Откройте **BP_BotAIController**
2. **Bot Behavior Tree** → **BT_BotBehavior**
3. **Bot Blackboard Asset** → **BB_BotBlackboard**

### BP_BotCharacter:
1. Откройте **BP_BotCharacter**
2. **AI Controller Class** → **BP_BotAIController**

### Project Settings:
1. **Edit** → **Project Settings** → **Maps & Modes**
2. **Default GameMode** → **BP_ThirdPersonGameMode**

## 🎮 Тестирование

1. **Откройте уровень Lvl_ThirdPerson**
2. **Нажмите Play**
3. **Через 2 секунды появятся AI боты**
4. **Подойдите к боту - он начнет преследование!**

## 🎉 Готово!

После выполнения всех шагов у вас будет:
- ✅ AI боты автоматически создаются при запуске игры
- ✅ Боты патрулируют по уровню
- ✅ Боты преследуют игрока при обнаружении
- ✅ Боты возвращаются к патрулированию при потере игрока

## 🔧 Дополнительные настройки

### Настройка параметров бота в BP_BotCharacter:
- **Run Speed**: 600 (скорость бега)
- **Walk Speed**: 300 (скорость ходьбы)
- **Detection Radius**: 1000 (радиус обнаружения)
- **Field Of View**: 90 (угол обзора)

### Настройка AI Controller в BP_BotAIController:
- **Sight Radius**: 1000 (радиус зрения)
- **Lose Sight Radius**: 1200 (радиус потери зрения)
- **Peripheral Vision Angle**: 90 (угол периферийного зрения)

Удачного создания Blueprint классов! 🤖✨



