#include "Kapralov_LR5_6_MethodsIngredients.h"
#include <vector>
#include <memory>
#include <map>

using namespace std;

vector<shared_ptr<Ingredient>> ingredients;

void showAllIngredients() {
    if (ingredients.empty()) {
        cout << "Список ингредиентов пуст.\n";
        return;
    }
    
    cout << "=== Список всех ингредиентов ===\n";
    for (size_t i = 0; i < ingredients.size(); ++i) {
        cout << i + 1 << ". " << *ingredients[i] << "\n";
        cout << "   Тип: " << ingredients[i]->getType() 
             << ", Калории: " << ingredients[i]->getCalories() << "\n";
    }
}

void createVegetable() {
    auto veg = make_shared<Vegetable>();
    cin >> *veg;
    ingredients.push_back(veg);
    cout << "Овощ успешно добавлен!\n";
}

void createMeat() {
    auto meat = make_shared<Meat>();
    cin >> *meat;
    ingredients.push_back(meat);
    cout << "Мясо успешно добавлено!\n";
}

void createCompositeIngredient() {
    auto comp = make_shared<CompositeIngredient>();
    cin >> *comp;
    
    showAllIngredients();
    cout << "Выберите ингредиенты для добавления (через пробел, 0 для завершения):\n";
    
    vector<size_t> indices;
    size_t index;
    while (cin >> index && index != 0) {
        if (index > 0 && index <= ingredients.size()) {
            indices.push_back(index - 1);
        }
    }
    cin.ignore(); // очистка буфера
    
    for (auto i : indices) {
        comp->addComponent(ingredients[i]);
    }
    
    ingredients.push_back(comp);
    cout << "Составной ингредиент успешно создан!\n";
}

void demonstratePolymorphism() {
    if (ingredients.empty()) {
        cout << "Нет ингредиентов для демонстрации.\n";
        return;
    }
    
    cout << "=== Демонстрация полиморфизма ===\n";
    for (const auto& ing : ingredients) {
        cout << *ing << "\n";
        cout << "Тип: " << ing->getType() << "\n";
        cout << "Калории: " << ing->getCalories() << "\n";
        
        // Демонстрация RTTI и специфических методов
        if (auto veg = dynamic_cast<Vegetable*>(ing.get())) {
            cout << "Сезонность: " << veg->checkSeason() << "\n";
        } else if (auto meat = dynamic_cast<Meat*>(ing.get())) {
            cout << "Рекомендуемое время приготовления: " << meat->recommendCookingTime() << " мин\n";
        } else if (auto comp = dynamic_cast<CompositeIngredient*>(ing.get())) {
            cout << "Общее количество калорий: " << comp->calculateTotalCalories() << "\n";
        }
        cout << "----------------------------\n";
    }
}

void combineVegetables() {
    showAllIngredients();
    cout << "Выберите два овоща для объединения (введите номера через пробел):\n";
    
    size_t i1, i2;
    cin >> i1 >> i2;
    cin.ignore();
    
    if (i1 > 0 && i1 <= ingredients.size() && 
        i2 > 0 && i2 <= ingredients.size()) {
        
        auto veg1 = dynamic_cast<Vegetable*>(ingredients[i1-1].get());
        auto veg2 = dynamic_cast<Vegetable*>(ingredients[i2-1].get());
        
        if (veg1 && veg2) {
            Vegetable combined = *veg1 + *veg2;
            auto newVeg = make_shared<Vegetable>(combined);
            ingredients.push_back(newVeg);
            cout << "Овощи успешно объединены!\n";
            cout << *newVeg << "\n";
        } else {
            cout << "Один или оба выбранных ингредиента не являются овощами!\n";
        }
    } else {
        cout << "Неверный выбор ингредиентов!\n";
    }
}
