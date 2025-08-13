# Система Инвентаря

## Обзор

Система инвентаря в Rogalique представляет собой надежную архитектуру для управления предметами с простым интерфейсом взаимодействия через клики. Система построена на принципе минимализма и четкого разделения ответственности, где каждый компонент имеет конкретную задачу.

## Основные Компоненты

### Ключевые Классы

1. **InventorySystem** - Управление данными и игровая логика инвентаря
2. **InventoryState** - Управление UI состоянием и обработка простых взаимодействий
3. **ImageUI** - Компонент для отображения UI элементов
4. **Item** - Модель данных предмета

### Принципы Проектирования

- **Простота**: Минимальная сложность для максимальной надежности
- **Единая Ответственность**: Каждый класс имеет одну четкую цель
- **Разделение Обязанностей**: UI, логика и данные четко разделены
- **Событийный Интерфейс**: Простые клики вместо сложных операций

## InventorySystem - Ядро Системы

### Основные Обязанности

`InventorySystem` управляет всеми данными инвентаря и предоставляет API для манипуляций:

```cpp
class InventorySystem {
public:
    // Singleton паттерн
    static InventorySystem* Instance();
    
    // Основные операции
    bool EquipItem(int equipmentSlot, int inventoryIndex);
    bool UnequipItem(int equipmentSlot);
    bool SwapInventoryItems(int index1, int index2);
    bool SwapEquipmentSlots(int slot1, int slot2);
    bool SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot);
    
    // Доступ к данным
    const std::vector<std::shared_ptr<Item>>& GetInventory() const;
    const Item* GetEquippedItem(int slot) const;
    
private:
    std::vector<std::shared_ptr<Item>> inventory;
    std::array<std::shared_ptr<Item>, 3> equipment;
};
```

### Основные Операции

#### EquipItem() - Экипировка Предмета
```cpp
bool InventorySystem::EquipItem(int equipmentSlot, int inventoryIndex) {
    // Валидация входных параметров
    if (equipmentSlot < 0 || equipmentSlot >= 3) return false;
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) return false;
    
    // Проверка, что слот экипировки свободен
    if (equipment[equipmentSlot] != nullptr) return false;
    
    // Экипировка предмета
    equipment[equipmentSlot] = inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);
    
    return true;
}
```

#### UnequipItem() - Снятие Предмета
```cpp
bool InventorySystem::UnequipItem(int equipmentSlot) {
    // Валидация входных параметров
    if (equipmentSlot < 0 || equipmentSlot >= 3) return false;
    if (equipment[equipmentSlot] == nullptr) return false;
    
    // Возврат предмета в инвентарь
    inventory.push_back(equipment[equipmentSlot]);
    equipment[equipmentSlot] = nullptr;
    
    return true;
}
```

#### SwapInventoryToEquipment() - Обмен Инвентарь ↔ Экипировка
```cpp
bool InventorySystem::SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot) {
    // Валидация
    if (equipmentSlot < 0 || equipmentSlot >= 3) return false;
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) return false;
    
    // Обмен предметами
    auto tempItem = equipment[equipmentSlot];
    equipment[equipmentSlot] = inventory[inventoryIndex];
    
    if (tempItem != nullptr) {
        inventory[inventoryIndex] = tempItem;
    } else {
        inventory.erase(inventory.begin() + inventoryIndex);
    }
    
    return true;
}
```

#### SwapInventoryItems() - Обмен Внутри Инвентаря
```cpp
bool InventorySystem::SwapInventoryItems(int index1, int index2) {
    // Валидация
    if (index1 < 0 || index1 >= inventory.size()) return false;
    if (index2 < 0 || index2 >= inventory.size()) return false;
    if (index1 == index2) return false;
    
    // Обмен позициями
    std::swap(inventory[index1], inventory[index2]);
    return true;
}
```

#### SwapEquipmentSlots() - Обмен Слотов Экипировки
```cpp
bool InventorySystem::SwapEquipmentSlots(int slot1, int slot2) {
    // Валидация
    if (slot1 < 0 || slot1 >= 3) return false;
    if (slot2 < 0 || slot2 >= 3) return false;
    if (slot1 == slot2) return false;
    
    // Обмен предметами между слотами
    std::swap(equipment[slot1], equipment[slot2]);
    return true;
}
```

##  Система Взаимодействий

### Принципы Взаимодействия

1. **Один Клик - Одно Действие**: Каждый клик выполняет понятное действие
2. **Автоматический Выбор Слота**: Система сама находит подходящий слот
3. **Немедленная Обратная Связь**: Действие происходит сразу
4. **Безопасность Операций**: Все операции валидируются

### Логика Взаимодействий

#### Клик по Предмету в Инвентаре
```
Предмет в Инвентаре → Первый Свободный Слот Экипировки
```

**Алгоритм:**
1. Найти первый пустой слот экипировки (0, 1, 2)
2. Если найден - экипировать предмет
3. Если все слоты заняты - ничего не делать

#### Клик по Предмету в Экипировке
```
Предмет в Экипировке → Инвентарь
```

**Алгоритм:**
1. Снять предмет с текущего слота
2. Добавить предмет в конец инвентаря
3. Обновить UI

### Преимущества Системы

#### Простота Использования
- **Интуитивность**: Понятно без обучения
- **Скорость**: Быстрые операции одним кликом
- **Надежность**: Меньше способов сделать ошибку

#### Техническая Простота
- **Меньше Кода**: Проще поддерживать
- **Меньше Состояний**: Меньше потенциальных багов
- **Проще Отладка**: Легче найти проблемы

#### Производительность
- **Нет Постоянного Отслеживания**: Только реакция на события
- **Простые Операции**: Быстрые вычисления
- **Минимальные Накладные Расходы**: Нет сложных состояний

## InventoryState - UI Контроллер

### Основные Методы

#### HandleInventoryItemClick() - Обработка Кликов по Инвентарю
```cpp
void InventoryState::HandleInventoryItemClick(int inventoryIndex) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) return;
    
    // Валидация индекса
    const auto& inventory = inventorySystem->GetInventory();
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) return;
    
    // Поиск первого свободного слота экипировки
    for (int equipSlot = 0; equipSlot < 3; ++equipSlot) {
        const auto* equippedItem = inventorySystem->GetEquippedItem(equipSlot);
        if (equippedItem == nullptr) {
            // Найден пустой слот - экипировать
            if (inventorySystem->EquipItem(equipSlot, inventoryIndex)) {
                UpdateEquipmentSlots();
                CreateInventoryGrid();
            }
            return;
        }
    }
    // Все слоты заняты - ничего не делать
}
```

#### HandleEquipmentItemClick() - Обработка Кликов по Экипировке
```cpp
void InventoryState::HandleEquipmentItemClick(int equipmentSlot) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) return;
    
    // Проверка наличия предмета в слоте
    const auto* equippedItem = inventorySystem->GetEquippedItem(equipmentSlot);
    if (equippedItem != nullptr) {
        // Снять предмет
        if (inventorySystem->UnequipItem(equipmentSlot)) {
            UpdateEquipmentSlots();
            CreateInventoryGrid();
        }
    }
}
```

### Обработка Событий

#### Простая Логика Событий
```cpp
void InventoryState::HandleEvent(const sf::Event& event) {
    // Обработка кликов по предметам ПЕРВЫМИ
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left) {
        
        sf::Vector2f mousePos = GetMousePosition();
        
        // Клики по предметам инвентаря
        for (size_t i = 0; i < inventoryItems.size(); ++i) {
            if (inventoryItems[i] && 
                inventoryItems[i]->GetBounds().contains(mousePos)) {
                HandleInventoryItemClick(static_cast<int>(i));
                return;
            }
        }
        
        // Клики по предметам экипировки
        for (size_t i = 0; i < equipmentItems.size(); ++i) {
            if (equipmentItems[i] && 
                equipmentItems[i]->GetBounds().contains(mousePos)) {
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
    
    // Горячие клавиши
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || 
            event.key.code == sf::Keyboard::Tab) {
            EngineCore::GameStateManager::Instance()->PopState();
        }
    }
}
```

## Управление UI

### Стратегия Обновления

#### Когда Обновлять UI
- После каждой успешной операции экипировки/снятия
- При любых изменениях в состоянии инвентаря
- При открытии интерфейса инвентаря

#### Методы Обновления

##### CreateInventoryGrid() - Обновление Инвентаря
```cpp
void InventoryState::CreateInventoryGrid() {
    // 1. Очистка старых элементов
    for (auto& item : inventoryItems) {
        if (item) uiManager->RemoveElement(item);
    }
    inventoryItems.clear();
    
    // 2. Создание слотов сетки
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            sf::Vector2f position(1000.0f + j * 126.0f, 320.0f + i * 126.0f);
            auto gridIcon = std::make_shared<ImageUI>(
                "inventoryPanelMap", sf::IntRect(1123, 0, 85, 85), position);
            inventorySlots.push_back(gridIcon);
            uiManager->AddElement(gridIcon);
        }
    }
    
    // 3. Создание предметов
    auto* inventorySystem = InventorySystem::Instance();
    const auto& inventory = inventorySystem->GetInventory();
    
    int itemIndex = 0;
    for (const auto& itemData : inventory) {
        if (itemIndex >= GRID_ROWS * GRID_COLS) break;
        
        // Вычисление позиции
        int i = itemIndex / GRID_COLS;
        int j = itemIndex % GRID_COLS;
        sf::Vector2f itemPosition(1000.0f + j * 126.0f, 320.0f + i * 126.0f);
        
        // Создание иконки предмета
        auto itemIcon = std::make_shared<ImageUI>(
            itemData->GetTextureName(),
            sf::Vector2f(85, 85),
            itemPosition);
        itemIcon->SetScale(sf::Vector2f{0.3f, 0.3f});
        itemIcon->SetCenterOrigin();
        
        inventoryItems.push_back(itemIcon);
        uiManager->AddElement(itemIcon);
        
        // Отображение количества если > 1
        if (itemData->GetCount() > 1) {
            auto countText = std::make_shared<TextUI>(
                16, sf::Vector2f(itemPosition.x + 25.f, itemPosition.y + 25.f), false);
            countText->SetText(std::to_string(itemData->GetCount()), true);
            countText->SetColor(sf::Color::White);
            uiManager->AddElement(countText);
            countTexts.push_back(countText);
        }
        
        itemIndex++;
    }
}
```

##### UpdateEquipmentSlots() - Обновление Экипировки
```cpp
void InventoryState::UpdateEquipmentSlots() {
    // 1. Очистка старых предметов экипировки
    for (int i = 0; i < 3; ++i) {
        if (equipmentItems[i]) {
            uiManager->RemoveElement(equipmentItems[i]);
            equipmentItems[i] = nullptr;
        }
    }
    
    // 2. Очистка текстов количества
    for (auto& text : equipmentCountTexts) {
        if (text) uiManager->RemoveElement(text);
    }
    equipmentCountTexts.clear();
    
    // 3. Создание новых предметов экипировки
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
                    16, sf::Vector2f(position.x + 25.f, position.y + 25.f), false);
                countText->SetText(std::to_string(equippedItem->GetCount()), true);
                countText->SetColor(sf::Color::White);
                uiManager->AddElement(countText);
                equipmentCountTexts.push_back(countText);
            }
        }
    }
}
```

### Управление Памятью

#### Автоматическая Очистка
```cpp
// UI элементы используют shared_ptr для автоматического управления памятью
std::vector<std::shared_ptr<ImageUI>> inventoryItems;

// Правильная очистка перед обновлением
for (auto& item : inventoryItems) {
    if (item) {
        uiManager->RemoveElement(item);  // Удаляет из системы отрисовки
    }
}
inventoryItems.clear();  // Освобождает shared_ptr ссылки
```

#### Жизненный Цикл UI
1. **Создание**: UI элементы создаются через shared_ptr
2. **Регистрация**: Добавляются в UiManager для отрисовки
3. **Обновление**: Старые удаляются, новые создаются
4. **Очистка**: Автоматическая при деструкции или явная при обновлении

## Обработка Ошибок

### Валидация Входных Данных

#### Проверка Указателей
```cpp
auto* inventorySystem = InventorySystem::Instance();
if (!inventorySystem) {
    return;  // Тихий возврат для недопустимого состояния
}
```

#### Проверка Индексов
```cpp
if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) {
    return;  // Выход при недопустимом индексе
}
```

#### Проверка Состояния Слотов
```cpp
const auto* equippedItem = inventorySystem->GetEquippedItem(equipmentSlot);
if (equippedItem == nullptr) {
    return;  // Нет предмета для снятия
}
```

### Стратегия Обработки Ошибок

1. **Тихие Возвраты**: Не логируем обычные случаи (пустые слоты и т.д.)
2. **Валидация Границ**: Всегда проверяем индексы массивов
3. **Проверка Указателей**: Валидируем все получаемые указатели
4. **Консистентность**: Обеспечиваем целостность состояния

## Оптимизации Производительности

### Эффективная Обработка Событий
- **Приоритетная Обработка**: Предметы обрабатываются первыми
- **Ранние Возвраты**: Предотвращают ненужные проверки
- **Минимальные Вычисления**: Простые операции сравнения

### Управление UI
- **Пакетные Обновления**: Обновляем UI только после успешных операций
- **Пересоздание vs Модификация**: Пересоздаем для простоты кода
- **Автоматическая Очистка**: shared_ptr минимизирует ручное управление памятью

### Оптимизация Данных
- **Векторы vs Списки**: Используем std::vector для лучшей локальности
- **Минимальные Копирования**: Передаем по ссылке где возможно
- **Singleton**: InventorySystem - один экземпляр для всей игры

## Точки Интеграции

### С Системой Предметов
```cpp
// Получение данных предмета
const auto& inventory = inventorySystem->GetInventory();
const auto& itemData = inventory[index];
std::string textureName = itemData->GetTextureName();
int count = itemData->GetCount();
```

### С Системой Рендеринга
```cpp
// Создание UI элементов
auto itemIcon = std::make_shared<ImageUI>(
    itemData->GetTextureName(),
    sf::Vector2f(85, 85),
    position);
uiManager->AddElement(itemIcon);
```

### С Системой Состояний
```cpp
// Управление состоянием инвентаря
GameStateManager::Instance()->PushState(std::make_unique<InventoryState>());
GameStateManager::Instance()->PopState();
```

## Примеры Использования

### Простая Экипировка
```cpp
// Пользователь кликает по предмету в инвентаре
// 1. HandleEvent ловит клик
// 2. Определяется позиция мыши
// 3. Находится предмет под курсором  
// 4. Вызывается HandleInventoryItemClick(index)
// 5. Находится первый пустой слот экипировки
// 6. Вызывается InventorySystem::EquipItem()
// 7. Обновляется UI
```

### Простое Снятие
```cpp
// Пользователь кликает по предмету в экипировке
// 1. HandleEvent ловит клик
// 2. Определяется позиция мыши
// 3. Находится экипированный предмет
// 4. Вызывается HandleEquipmentItemClick(slot)
// 5. Вызывается InventorySystem::UnequipItem()
// 6. Обновляется UI
```

## Расширение Системы

### Добавление Новых Типов Предметов
1. **Обновить Item**: Добавить новые свойства
2. **Обновить InventorySystem**: Добавить специфичную логику
3. **Обновить UI**: Обновить отображение при необходимости

### Добавление Новых Слотов Экипировки
1. **Изменить Размер Массива**: equipment[3] → equipment[N]  
2. **Обновить Циклы**: Во всех методах обработки
3. **Обновить UI**: Создание слотов и позиционирование

### Добавление Горячих Клавиш
1. **Расширить HandleEvent**: Добавить обработку клавиш
2. **Добавить Маппинг**: Клавиша → Слот экипировки
3. **Реализовать Логику**: Использовать существующие методы

## Лучшие Практики

### Организация Кода
- **Разделение Ответственности**: UI в State, данные в System
- **Простые Методы**: Одна функция - одна задача
- **Понятные Имена**: Имена методов описывают действие

### Обработка Ошибок
- **Валидация Входных Данных**: Всегда проверяем параметры
- **Тихие Возвраты**: Для обычных неуспешных случаев
- **Консистентность**: Обеспечиваем целостность состояния

### Производительность
- **Минимальные Обновления**: Обновляем только что изменилось
- **Эффективные Структуры**: Используем подходящие контейнеры
- **Избегаем Преждевременной Оптимизации**: Простота сначала

## Отладка

### Типичные Проблемы

#### Клики Не Работают
- **Проверить GetBounds()**: Правильно ли вычисляются границы
- **Проверить Координаты Мыши**: Соответствуют ли UI координатам
- **Проверить Порядок Обработки**: Не перехватывают ли другие элементы

#### UI Не Обновляется  
- **Проверить Вызовы Обновления**: Вызываются ли UpdateEquipmentSlots/CreateInventoryGrid
- **Проверить Очистку**: Удаляются ли старые элементы
- **Проверить UiManager**: Добавляются ли новые элементы

#### Некорректные Индексы
- **Валидация Границ**: Проверить все массивы
- **Логирование**: Добавить временные выводы индексов
- **Отладчик**: Использовать пошаговое выполнение

### Диагностические Методы

```cpp
// Временное логирование для отладки
void InventoryState::HandleInventoryItemClick(int inventoryIndex) {
    LOG_INFO("Клик по предмету инвентаря: " << inventoryIndex);
    // ... остальная логика
}

void InventoryState::HandleEquipmentItemClick(int equipmentSlot) {
    LOG_INFO("Клик по предмету экипировки: " << equipmentSlot);
    // ... остальная логика
}
```

