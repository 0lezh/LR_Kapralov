#ifndef KAPRALOV_LR5_6_COMPOSITE_INGREDIENT_H
#define KAPRALOV_LR5_6_COMPOSITE_INGREDIENT_H

#include "Kapralov_LR5_6_AbstractIngredient.h"
#include "Kapralov_LR5_6_NutritionCalculator.h"
#include <vector>
#include <memory>

class CompositeIngredient : public Ingredient, public NutritionCalculator {
private:
    vector<shared_ptr<Ingredient>> components;
    bool isReadyToServe;

    ostream& print(ostream& os) const override {
        os << "Составной ингредиент [ID: " << id << ", Название: " << name 
           << ", Цена: " << pricePerUnit << " руб., Готов к подаче: " 
           << (isReadyToServe ? "Да" : "Нет") << "]\nКомпоненты:\n";
        for (const auto& comp : components) {
            os << "  - " << *comp << "\n";
        }
        return os;
    }

    istream& input(istream& is) override {
        Ingredient::input(is);
        string ready;
        inputData(ready, "Готов к подаче? (да/нет): ", validateNonEmptyString);
        isReadyToServe = (ready == "да" || ready == "Да");
        return is;
    }

public:
    CompositeIngredient() : Ingredient(), isReadyToServe(false) {}
    CompositeIngredient(const string& id, const string& name, double price, bool ready)
        : Ingredient(id, name, price), isReadyToServe(ready) {}
    
    ~CompositeIngredient() override {}

    // Переопределение виртуальных методов
    double getCalories() const override {
        return calculateTotalCalories();
    }

    string getType() const override {
        return "Составной ингредиент";
    }

    bool validate() const override {
        if (components.size() > 10) return false;
        return Ingredient::validate();
    }

    // Дополнительные методы
    void addComponent(shared_ptr<Ingredient> ingredient) {
        components.push_back(ingredient);
        // Пересчет средней цены
        double total = 0;
        for (const auto& comp : components) {
            total += comp->getPricePerUnit();
        }
        pricePerUnit = total / components.size();
    }

    void addDecoration(const string& decoration) {
        name += " с " + decoration;
    }

    // Перегрузка оператора []
    shared_ptr<Ingredient> operator[](size_t index) {
        if (index < components.size()) {
            return components[index];
        }
        return nullptr;
    }

    // Метод для расчета калорий
    double calculateTotalCalories() const {
        double total = 0;
        for (const auto& comp : components) {
            total += comp->getCalories();
        }
        return total;
    }
};

#endif // KAPRALOV_LR5_6_COMPOSITE_INGREDIENT_H
