# Документация InventoryState

## Обзор

`InventoryState` - это UI контроллер для интерфейса инвентаря в Rogalique. Он управляет визуальным представлением системы инвентаря и обрабатывает простые пользовательские взаимодействия через клики мыши. Класс служит мостом между UI слоем и игровой логикой инвентаря.

## Архитектура Класса

### Наследование
```cpp
class InventoryState : public EngineCore::GameState
```

`InventoryState` наследуется от `GameState`, делая его частью системы управления состояниями игры. Это позволяет помещать его в стек состояний при открытии инвентаря.

### Основные Обязанности

1. **Управление UI** - Создание и управление всеми UI элементами инвентаря
2. **Координация Событий** - Обработка кликов мыши по предметам
3. **Простые Взаимодействия** - Экипировка/снятие предметов одним кликом
4. **Синхронизация Состояния** - Поддержание UI в синхронизации с `InventorySystem`

## Ключевые Компоненты

### Коллекции UI Элементов

```cpp
// Визуализация экипировки
std::vector<std::shared_ptr<ImageUI>> equipmentSlots{3};    // Фоновые слоты
std::vector<std::shared_ptr<ImageUI>> equipmentItems{3};    // Экипированные предметы

// Визуализация инвентаря
std::vector<std::shared_ptr<ImageUI>> inventoryItems;       // Предметы инвентаря
std::vector<std::shared_ptr<ImageUI>> inventorySlots;       // Слоты сетки

// Текстовые наложения
std::vector<std::shared_ptr<TextUI>> countTexts;            // Количества предметов
std::vector<std::shared_ptr<TextUI>> equipmentCountTexts;   // Количества экипировки
```

### UI Менеджер
```cpp
std::shared_ptr<UiManager> uiManager;  // Управляет жизненным циклом UI элементов
```

## Методы Жизненного Цикла

### Конструктор
```cpp
InventoryState::InventoryState() {
    // Приостановить игровой мир
    EngineCore::GameWorld::Instance()->SetPaused(true);
    
    // Создать UI менеджер
    auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("InventoryUI");
    uiManager = std::make_unique<UiManager>(uiGameObject);
    
    // Простая логика кликов - без drag&drop
    
    // Создать UI элементы
    CreateUi();
}
```

### Деструктор
```cpp
InventoryState::~InventoryState() {
    // Возобновить игровой мир
    EngineCore::GameWorld::Instance()->SetPaused(false);
}
```

## Система Обработки Событий

### Простая Обработка Кликов

Метод `HandleEvent()` использует простой подход - обработка кликов по предметам:

```cpp
void InventoryState::HandleEvent(const sf::Event& event) {
    // Обрабатываем клики по предметам ПЕРВЫМИ
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = GetMousePosition();
        
        // Обработка кликов по предметам инвентаря
        for (size_t i = 0; i < inventoryItems.size(); ++i) {
            if (inventoryItems[i] && inventoryItems[i]->GetBounds().contains(mousePos)) {
                HandleInventoryItemClick(static_cast<int>(i));
                return;
            }
        }
        
        // Обработка кликов по предметам экипировки
        for (size_t i = 0; i < equipmentItems.size(); ++i) {
            if (equipmentItems[i] && equipmentItems[i]->GetBounds().contains(mousePos)) {
                HandleEquipmentItemClick(static_cast<int>(i));
                return;
            }
        }
    }
    
    // Обработка других UI элементов
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return; 
            }
        }
    }
    
    // Обработка горячих клавиш
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Tab) {
            EngineCore::GameStateManager::Instance()->PopState();
        }
    }
}
```

### Логика Простых Взаимодействий

**Клик по предмету в инвентаре**: Экипирует в первый свободный слот
**Клик по предмету в экипировке**: Снимает и возвращает в инвентарь

## Методы Создания UI

### CreateUi()
Создает основной интерфейс инвентаря:

```cpp
void InventoryState::CreateUi() {
    // Фоновые панели
    auto panel = std::make_shared<ImageUI>(
        "inventoryPanelMap", sf::IntRect(0, 0, 1123, 608),
        sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH/2.0f, SETTINGS.PLAYER_CAMERA_HEIGHT/2.0f));
    
    // Слоты экипировки (фон)
    for (int i = 0; i < 3; ++i) {
        auto equipmentIcon = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1210, 0, 105, 100),
            sf::Vector2f(800.0f, 510.0f + i * 130.0f));
        equipmentSlots[i] = equipmentIcon;
        uiManager->AddElement(equipmentIcon);
    }
    
    // Создать динамический контент
    CreateInventoryGrid();
    UpdateEquipmentSlots();
}
```

### CreateInventoryGrid()
Динамически создает предметы и слоты инвентаря:

```cpp
void InventoryState::CreateInventoryGrid() {
    // Очистить существующие элементы
    for (auto& item : inventoryItems) {
        if (item) uiManager->RemoveElement(item);
    }
    inventoryItems.clear();
    
    // Создать слоты сетки (фон)
    for (int i = 0; i < SETTINGS.INVENTORY_GRID_ROWS; ++i) {
        for (int j = 0; j < SETTINGS.INVENTORY_GRID_COLS; ++j) {
            sf::Vector2f position(1000.0f + j * 126.0f, 320.0f + i * 126.0f);
            auto gridIcon = std::make_shared<ImageUI>(
                "inventoryPanelMap", sf::IntRect(1123, 0, 85, 85), position);
            inventorySlots.push_back(gridIcon);
            uiManager->AddElement(gridIcon);
        }
    }
    
    // Создать предметы из данных инвентаря
    auto* inventorySystem = InventorySystem::Instance();
    const auto& inventory = inventorySystem->GetInventory();
    
    int itemIndex = 0;
    for (auto index = 0; index < inventory.size(); ++index) {
        if (itemIndex >= SETTINGS.INVENTORY_GRID_ROWS * SETTINGS.INVENTORY_GRID_COLS) break;
        
        const auto& itemData = inventory[index];
        
        int i = itemIndex / SETTINGS.INVENTORY_GRID_COLS;
        int j = itemIndex % SETTINGS.INVENTORY_GRID_COLS;
        
        sf::Vector2f itemPosition(1000.0f + j * 126.0f, 320.0f + i * 126.0f);
        
        auto itemIcon = std::make_shared<ImageUI>(
            itemData->GetTextureName(),
            sf::Vector2f(85, 85),
            itemPosition);
        itemIcon->SetScale(sf::Vector2f{0.3f, 0.3f});
        itemIcon->SetCenterOrigin();
        
        inventoryItems.push_back(itemIcon);
        uiManager->AddElement(itemIcon);
        
        // Отображение количества предметов если > 1
        if (itemData->GetCount() > 1) {
            auto countText = std::make_shared<TextUI>(
                16, 
                sf::Vector2f(itemPosition.x + 25.f, itemPosition.y + 25.f), false
            );
            countText->SetText(std::to_string(itemData->GetCount()), true);
            countText->SetColor(sf::Color::White);
            uiManager->AddElement(countText);
            countTexts.push_back(countText);
        }
        
        itemIndex++;
    }
}
```

### UpdateEquipmentSlots()
Обновляет визуализацию слотов экипировки:

```cpp
void InventoryState::UpdateEquipmentSlots() {
    // Очистить старые предметы экипировки
    for (int i = 0; i < 3; ++i) {
        if (equipmentItems[i]) {
            uiManager->RemoveElement(equipmentItems[i]);
            equipmentItems[i] = nullptr;
        }
    }
    
    // Очистить тексты количества экипировки
    for (auto& text : equipmentCountTexts) {
        if (text) {
            uiManager->RemoveElement(text);
        }
    }
    equipmentCountTexts.clear();
    
    // Создать новые предметы экипировки
    auto* inventorySystem = InventorySystem::Instance();
    for (int i = 0; i < 3; ++i) {
        const auto* equippedItem = inventorySystem->GetEquippedItem(i);
        if (equippedItem) {
            sf::Vector2f position(800.0f, 510.0f + i * 130.0f);
            
            auto itemIcon = std::make_shared<ImageUI>(
                equippedItem->GetTextureName(),
                sf::Vector2f(85, 85),
                position);
            itemIcon->SetScale(sf::Vector2f{0.3f, 0.3f});
            itemIcon->SetCenterOrigin();
            
            equipmentItems[i] = itemIcon;
            uiManager->AddElement(itemIcon);
            
            // Отображение количества если > 1
            if (equippedItem->GetCount() > 1) {
                auto countText = std::make_shared<TextUI>(
                    16, 
                    sf::Vector2f(position.x + 25.f, position.y + 25.f), false
                );
                countText->SetText(std::to_string(equippedItem->GetCount()), true);
                countText->SetColor(sf::Color::White);
                uiManager->AddElement(countText);
                equipmentCountTexts.push_back(countText);
            }
        }
    }
}
```

## Простые Обработчики Кликов

### HandleInventoryItemClick()
Обрабатывает клики по предметам в инвентаре:

```cpp
void InventoryState::HandleInventoryItemClick(int inventoryIndex) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        return;
    }
    
    // Проверка валидности индекса
    const auto& inventory = inventorySystem->GetInventory();
    if (inventoryIndex < 0 || inventoryIndex >= static_cast<int>(inventory.size())) {
        return;
    }
    
    // Найти первый пустой слот экипировки
    for (int equipSlot = 0; equipSlot < 3; ++equipSlot) {
        const auto* equippedItem = inventorySystem->GetEquippedItem(equipSlot);
        if (equippedItem == nullptr) {
            // Найден пустой слот - экипировать предмет
            if (inventorySystem->EquipItem(equipSlot, inventoryIndex)) {
                UpdateEquipmentSlots();
                CreateInventoryGrid();
            }
            return;
        }
    }
    // Все слоты экипировки заняты - ничего не делать
}
```

### HandleEquipmentItemClick()
Обрабатывает клики по предметам в экипировке:

```cpp
void InventoryState::HandleEquipmentItemClick(int equipmentSlot) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        return;
    }
    
    // Проверить, что в слоте действительно есть предмет
    const auto* equippedItem = inventorySystem->GetEquippedItem(equipmentSlot);
    if (equippedItem != nullptr) {
        // Снять предмет (добавить в инвентарь)
        if (inventorySystem->UnequipItem(equipmentSlot)) {
            UpdateEquipmentSlots();
            CreateInventoryGrid();
        }
    }
}
```

### GetMousePosition()
Получает позицию мыши в UI координатах:

```cpp
sf::Vector2f InventoryState::GetMousePosition() {
    // Получить позицию мыши в UI координатах
    auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(oldView);
    return mousePos;
}
```

## Стратегия Обновления UI

### Когда Происходят Обновления UI
- После успешной экипировки предмета
- После снятия предмета
- При любых изменениях в инвентаре или экипировке

### Методы Обновления
- `CreateInventoryGrid()` - Полное обновление инвентаря
- `UpdateEquipmentSlots()` - Только слоты экипировки
- Оба вызываются вместе для обеспечения синхронизации

### Соображения Производительности
- UI элементы пересоздаются для простоты
- Старые элементы правильно удаляются перед созданием новых
- Обновления происходят только после успешных операций

## Управление Памятью

### Автоматическая Очистка
```cpp
// UI элементы хранятся в shared_ptr
std::vector<std::shared_ptr<ImageUI>> inventoryItems;

// Автоматическая очистка при удалении элементов
for (auto& item : inventoryItems) {
    if (item) {
        uiManager->RemoveElement(item);  // Удаляет из отрисовки
    }
}
inventoryItems.clear();  // Освобождает ссылки shared_ptr
```

### Управление Ресурсами
- `UiManager` обрабатывает жизненный цикл UI элементов
- `shared_ptr` обеспечивает автоматическое управление памятью
- Правильная очистка в деструкторе обеспечивает отсутствие утечек

## Точки Интеграции

### С InventorySystem
```cpp
auto* inventorySystem = InventorySystem::Instance();
const auto& inventory = inventorySystem->GetInventory();
const auto* equippedItem = inventorySystem->GetEquippedItem(slot);
bool success = inventorySystem->EquipItem(slot, inventoryIndex);
bool success = inventorySystem->UnequipItem(slot);
```

### С GameStateManager
```cpp
// Открытие инвентаря
GameStateManager::Instance()->PushState(std::make_unique<InventoryState>());

// Закрытие инвентаря
GameStateManager::Instance()->PopState();
```

## Обработка Ошибок

### Проверки Null Указателей
```cpp
if (!inventorySystem) {
    return;
}
```

### Валидация Индексов
```cpp
if (inventoryIndex < 0 || inventoryIndex >= static_cast<int>(inventory.size())) {
    return;
}
```

### Валидация Состояния
```cpp
if (!uiManager) {
    return;
}
```

