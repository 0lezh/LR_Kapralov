#include "Kapralov_LR5_6_MethodsIngredients.h"
#include <iostream>
#include <map>
#include <functional>

using namespace std;

// Структура для пункта меню
struct MenuItem {
    string title;
    function<void()> action;
};

int main() {
    // Создание меню
    map<int, MenuItem> menu = {
        {1, {"Показать все ингредиенты", showAllIngredients}},
        {2, {"Добавить овощ", createVegetable}},
        {3, {"Добавить мясо", createMeat}},
        {4, {"Создать составной ингредиент", createCompositeIngredient}},
        {5, {"Демонстрация полиморфизма", demonstratePolymorphism}},
        {6, {"Объединить овощи", combineVegetables}}
    };

    int choice;
    do {
        cout << "\n=== Меню управления ингредиентами ===\n";
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.title << "\n";
        }
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        
        cin >> choice;
        cin.ignore(); // Очистка буфера
        
        if (choice == 0) break;
        
        auto it = menu.find(choice);
        if (it != menu.end()) {
            cout << "\n=== " << it->second.title << " ===\n";
            it->second.action();
        } else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
        
    } while (true);

    cout << "Работа завершена. До свидания!\n";
    return 0;
}
