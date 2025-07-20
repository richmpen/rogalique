# Система Инвентаря и Drag & Drop

## Обзор

Система инвентаря в Rogalique представляет собой модульную архитектуру для управления предметами игрока с поддержкой перетаскивания (drag & drop). Система состоит из нескольких ключевых компонентов, работающих вместе для обеспечения плавного пользовательского опыта.

## Архитектура

### Основные компоненты

1. **InventorySystem** - ядро системы, управляющее данными
2. **InventoryState** - UI состояние для отображения инвентаря
3. **ImageUI** - компонент для drag & drop операций
4. **TextUI** - отображение количества предметов

### Структура данных

```cpp
// Предмет в инвентаре
struct InventoryItem {
    std::string textureName;  // Название текстуры
    int count;                // Количество предметов
    // ... другие свойства
};

// Слоты экипировки (0-2)
std::vector<InventoryItem> equippedItems;
```

## Drag & Drop Система

### Принцип работы

Система drag & drop использует статические переменные в `ImageUI` для отслеживания состояния перетаскивания:

```cpp
// Статические переменные для отслеживания перетаскивания
static ImageUI* draggedItem = nullptr;        // Перетаскиваемый элемент
static sf::Vector2f dragOffset;               // Смещение курсора
static sf::Vector2f originalPosition;         // Исходная позиция
```

### Жизненный цикл перетаскивания

1. **Начало перетаскивания**
   - Пользователь нажимает левую кнопку мыши на предмете
   - Устанавливается `draggedItem = this`
   - Запоминается `originalPosition` и `dragOffset`

2. **Перемещение**
   - При движении мыши обновляется позиция перетаскиваемого элемента
   - Элемент следует за курсором с учетом смещения

3. **Завершение**
   - При отпускании кнопки мыши проверяется возможность drop
   - Если drop возможен - вызывается колбэк `onDropCallback`
   - Если нет - элемент возвращается на исходную позицию
   - Состояние очищается: `draggedItem = nullptr`

### Поддерживаемые операции

#### Инвентарь → Слот экипировки
- Предмет из инвентаря перетаскивается в слот экипировки (0-2)
- Вызывается `InventorySystem::EquipItem(slot, inventoryIndex)`
- UI пересоздается для отражения изменений

#### Слот экипировки → Инвентарь
- Предмет из слота экипировки возвращается в инвентарь
- Вызывается `InventorySystem::UnequipItem(slot)`
- UI пересоздается для отражения изменений

## UI Компоненты

### InventoryState

Основной класс для управления UI инвентаря:

```cpp
class InventoryState {
private:
    std::vector<std::shared_ptr<ImageUI>> inventoryItems;    // Предметы инвентаря
    std::vector<std::shared_ptr<ImageUI>> equipmentSlots;    // Слоты экипировки
    std::vector<std::shared_ptr<ImageUI>> equipmentItems;    // Предметы в слотах
    std::vector<std::shared_ptr<TextUI>> countTexts;         // Тексты количества
};
```

### Создание UI

1. **Сетка инвентаря** (5x5 слотов)
   - Фоновые слоты для drop операций
   - Предметы с их текстурами
   - Тексты количества для предметов > 1

2. **Слоты экипировки** (3 слота)
   - Слоты для экипировки предметов
   - Отображение экипированных предметов

### Управление текстами количества

```cpp
// Удаление старых текстов
for (auto& text : countTexts) {
    if (text) {
        uiManager->RemoveElement(text);
    }
}
countTexts.clear();

// Создание новых текстов
if (itemData.count > 1) {
    auto countText = std::make_shared<TextUI>(...);
    uiManager->AddElement(countText);
    countTexts.push_back(countText);  // Сохраняем ссылку
}
```

## Безопасность и стабильность

### Защита от ошибок

1. **Очистка состояния перетаскивания**
   ```cpp
   // Перед пересозданием UI
   ImageUI::ClearDraggedItem();
   CreateInventoryGrid();
   UpdateEquipmentSlots();
   ```

2. **Проверка валидности индексов**
   ```cpp
   if (inventoryIndex >= static_cast<int>(inventory.size())) {
       LOG_ERROR("Invalid inventory index");
       return;
   }
   ```

3. **Проверка указателей**
   ```cpp
   if (!draggedItem || !inventorySystem) {
       LOG_ERROR("Null pointer detected");
       return;
   }
   ```

### Предотвращение утечек памяти

- Все UI элементы хранятся в `shared_ptr`
- Правильная очистка старых элементов перед созданием новых
- Использование RAII для автоматического управления ресурсами

## Использование

### Открытие инвентаря
```cpp
// В PlayState
if (event.key.code == sf::Keyboard::I) {
    GameWorld::Instance()->SetPaused(true);
    GameStateManager::Instance()->PushState(std::make_unique<InventoryState>());
}
```

### Закрытие инвентаря
```cpp
// ESC или I
if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::I) {
    GameStateManager::Instance()->PopState();
}
```

### Использование предметов
```cpp
// Клавиши 1-3 для быстрого использования
if (event.key.code == sf::Keyboard::Num1) {
    inventorySystem->UseEquippedItem(0);
}
```

## Производительность

### Оптимизации

1. **Пересоздание UI только при необходимости**
   - UI пересоздается только после успешных операций
   - Минимизация количества перерисовок

2. **Эффективное управление памятью**
   - Использование `shared_ptr` для автоматического освобождения
   - Очистка старых элементов перед созданием новых

3. **Статические переменные для drag & drop**
   - Минимальные накладные расходы
   - Простота реализации

## Расширение системы

### Добавление новых типов предметов

1. Расширить структуру `InventoryItem`
2. Добавить логику в `InventorySystem`
3. Обновить UI для отображения новых свойств

### Добавление новых операций

1. Создать новый колбэк в `ImageUI`
2. Добавить обработку в `InventoryState`
3. Реализовать логику в `InventorySystem`

## Отладка

### Логирование

Система использует подробное логирование для отладки:

```cpp
LOG_INFO("Started dragging item from index: " << inventoryIndex);
LOG_INFO("Successfully equipped item to slot " << equipmentSlot);
LOG_ERROR("Invalid inventory index: " << inventoryIndex);
```

### Частые проблемы

1. **Некорректные индексы** - проверить очистку `draggedItem`
2. **Текст количества остается** - проверить очистку `countTexts`
3. **Краши при перетаскивании** - проверить валидность указателей

## Заключение

Система инвентаря и drag & drop в Rogalique обеспечивает стабильный и интуитивный пользовательский интерфейс. Модульная архитектура позволяет легко расширять функциональность, а встроенные механизмы безопасности предотвращают ошибки и утечки памяти. 