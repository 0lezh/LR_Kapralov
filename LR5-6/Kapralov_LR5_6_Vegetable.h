#ifndef KAPRALOV_LR5_6_VEGETABLE_H
#define KAPRALOV_LR5_6_VEGETABLE_H

#include "Kapralov_LR5_6_AbstractIngredient.h"

class Vegetable : public Ingredient {
protected:
    bool isOrganic;
    string vitamins;

    ostream& print(ostream& os) const override {
        os << "Овощ [ID: " << id << ", Название: " << name 
           << ", Цена: " << pricePerUnit << " руб., Органический: " 
           << (isOrganic ? "Да" : "Нет") << ", Витамины: " << vitamins << "]";
        return os;
    }

    istream& input(istream& is) override {
        Ingredient::input(is);
        string organic;
        inputData(organic, "Органический продукт? (да/нет): ", validateNonEmptyString);
        isOrganic = (organic == "да" || organic == "Да");
        inputData(vitamins, "Введите список витаминов (через запятую): ", validateNonEmptyString);
        return is;
    }

public:
    Vegetable() : Ingredient(), isOrganic(false), vitamins("") {}
    Vegetable(const string& id, const string& name, double price, bool organic, const string& vit)
        : Ingredient(id, name, price), isOrganic(organic), vitamins(vit) {}
    Vegetable(const Vegetable& other) 
        : Ingredient(other), isOrganic(other.isOrganic), vitamins(other.vitamins) {}
    
    ~Vegetable() override {}

    // Переопределение виртуальных методов
    double getCalories() const override {
        return isOrganic ? 30 : 25;
    }

    string getType() const override {
        return "Овощ";
    }

    bool validate() const override {
        return Ingredient::validate() && !vitamins.empty();
    }

    // Дополнительный метод
    string checkSeason() const {
        if (name.find("картофель") != string::npos || name.find("морковь") != string::npos) {
            return "зима";
        }
        return "лето";
    }

    // Перегрузка оператора +
    Vegetable operator+(const Vegetable& other) const {
        string newVitamins = vitamins;
        if (!newVitamins.empty() && !other.vitamins.empty()) {
            newVitamins += ", ";
        }
        newVitamins += other.vitamins;
        return Vegetable(id + "_" + other.id, name + " и " + other.name, 
                        (pricePerUnit + other.pricePerUnit) / 2, 
                        isOrganic && other.isOrganic, newVitamins);
    }
};

#endif // KAPRALOV_LR5_6_VEGETABLE_H
