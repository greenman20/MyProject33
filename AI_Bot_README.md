# AI Bot System для MyProject3

## Описание
Система AI бота, который преследует игрока при обнаружении. Бот использует Behavior Tree и Blackboard для управления поведением.

## Компоненты системы

### 1. BotCharacter (C++)
- Основной класс персонажа бота
- Содержит логику обнаружения игрока
- Управляет движением и анимациями
- Настраиваемые параметры: скорость бега/ходьбы, радиус обнаружения, угол обзора

### 2. BotAIController (C++)
- AI контроллер для управления поведением бота
- Использует Behavior Tree и Blackboard
- Система восприятия для обнаружения игрока
- Настраиваемые параметры зрения

### 3. Behavior Tree Tasks (C++)
- **BTTask_ChasePlayer**: Преследование игрока
- **BTTask_Patrol**: Патрулирование по области
- **BTTask_CheckPlayerVisibility**: Проверка видимости игрока

## Настройка в редакторе

### 1. Создание Blueprint классов
1. Создайте Blueprint класс `BP_BotCharacter`, наследующий от `BotCharacter`
2. Создайте Blueprint класс `BP_BotAIController`, наследующий от `BotAIController`
3. Назначьте `BP_BotAIController` в `BP_BotCharacter`

### 2. Создание Behavior Tree
1. Создайте Behavior Tree `BT_BotBehavior`
2. Создайте Blackboard `BB_BotBlackboard` с ключами:
   - `Player` (Object) - ссылка на игрока
   - `CanSeePlayer` (Bool) - видит ли бот игрока
   - `LastKnownPlayerLocation` (Vector) - последнее известное местоположение игрока

### 3. Настройка Behavior Tree
Структура дерева:
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
- Настройте параметры зрения в `SightConfig`

## Параметры настройки

### BotCharacter
- `RunSpeed`: Скорость бега (по умолчанию: 600)
- `WalkSpeed`: Скорость ходьбы (по умолчанию: 300)
- `DetectionRadius`: Радиус обнаружения (по умолчанию: 1000)
- `FieldOfView`: Угол обзора (по умолчанию: 90)

### BotAIController
- `SightRadius`: Радиус зрения (по умолчанию: 1000)
- `LoseSightRadius`: Радиус потери зрения (по умолчанию: 1200)
- `PeripheralVisionAngleDegrees`: Угол периферийного зрения (по умолчанию: 90)

### Behavior Tree Tasks
- `AcceptableRadius`: Радиус достижения цели (по умолчанию: 100)
- `PatrolRadius`: Радиус патрулирования (по умолчанию: 500)
- `WaitTime`: Время ожидания в точке патрулирования (по умолчанию: 2)

## Использование

1. Разместите `BP_BotCharacter` на уровне
2. Убедитесь, что на уровне есть Navigation Mesh
3. Запустите игру
4. Бот будет патрулировать, а при обнаружении игрока начнет преследование

## Отладка

- Включите отображение Debug Lines для визуализации обнаружения игрока
- Используйте Behavior Tree Debugger для отслеживания состояния AI
- Проверьте логи в Output Log для диагностики проблем

## Расширение функциональности

- Добавьте новые состояния поведения (атака, поиск, возврат на пост)
- Реализуйте систему памяти для запоминания нескольких позиций игрока
- Добавьте групповое поведение для нескольких ботов
- Интегрируйте систему звукового обнаружения



