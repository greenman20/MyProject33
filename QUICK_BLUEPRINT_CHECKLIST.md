# 🚀 Быстрое создание Blueprint классов для Lvl_ThirdPerson

## ✅ Готово к созданию:
- ✅ `AMyProject3GameMode` модифицирован для AI ботов
- ✅ Редактор Unreal Engine запущен
- ✅ Проект скомпилирован без ошибок
- ✅ Уровень `Lvl_ThirdPerson` с Navigation Mesh готов

## 📋 Чек-лист создания Blueprint классов:

### 1. BP_BotCharacter
```
Content Browser → Right Click → Blueprint Class
→ BotCharacter → Назвать "BP_BotCharacter"
→ Сохранить в Content/Blueprints/
```

### 2. BP_BotAIController  
```
Content Browser → Right Click → Blueprint Class
→ BotAIController → Назвать "BP_BotAIController"
→ Сохранить в Content/Blueprints/
```

### 3. BB_BotBlackboard
```
Content Browser → Right Click → Miscellaneous → Blackboard
→ Назвать "BB_BotBlackboard" → Сохранить в Content/AI/
→ Добавить ключи:
  - Player (Object, Actor)
  - CanSeePlayer (Bool)  
  - LastKnownPlayerLocation (Vector)
```

### 4. BT_BotBehavior
```
Content Browser → Right Click → Miscellaneous → Behavior Tree
→ Назвать "BT_BotBehavior" → Сохранить в Content/AI/
→ Blackboard Asset → BB_BotBlackboard
→ Создать структуру:
  Selector
  ├── Sequence (CheckPlayerVisibility + ChasePlayer)
  └── Sequence (Patrol)
```

### 5. BP_ThirdPersonGameMode
```
Content Browser → Right Click → Blueprint Class
→ MyProject3GameMode → Назвать "BP_ThirdPersonGameMode"
→ Сохранить в Content/Blueprints/
→ AI Bot Settings:
  - Bot Class → BP_BotCharacter
  - Number Of Bots → 2
  - Auto Spawn Bots → True
```

### 6. Настройка связей
```
BP_BotAIController:
- Bot Behavior Tree → BT_BotBehavior
- Bot Blackboard Asset → BB_BotBlackboard

BP_BotCharacter:
- AI Controller Class → BP_BotAIController

Project Settings → Maps & Modes:
- Default GameMode → BP_ThirdPersonGameMode
```

## 🎮 Тестирование:
1. Откройте уровень `Lvl_ThirdPerson`
2. Нажмите `Play`
3. Через 2 секунды появятся AI боты
4. Подойдите к боту - он начнет преследование!

## 📖 Подробная инструкция:
См. файл `THIRDPERSON_LEVEL_SETUP.md`

## 🎉 Готово к созданию!
Все C++ классы готовы, редактор запущен - можно создавать Blueprint классы! 🤖



