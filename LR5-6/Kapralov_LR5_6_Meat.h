#ifndef KAPRALOV_LR5_6_MEAT_H
#define KAPRALOV_LR5_6_MEAT_H

#include "Kapralov_LR5_6_AbstractIngredient.h"

class Meat final : public Ingredient {
private:
    double fatPercentage;
    string origin;

    ostream& print(ostream& os) const override {
        os << "Мясо [ID: " << id << ", Название: " << name 
           << ", Цена: " << pricePerUnit << " руб., Происхождение: " << origin 
           << ", Жирность: " << fatPercentage << "%]";
        return os;
    }

    istream& input(istream& is) override {
        Ingredient::input(is);
        inputData(origin, "Введите происхождение (говядина/курица и т.д.): ", validateNonEmptyString);
        inputData(fatPercentage, "Введите процент жирности (1-50): ", 
                 [](const string& s) { 
                     try { 
                         double p = stod(s); 
                         return p >= 1 && p <= 50; 
                     } catch (...) { 
                         return false; 
                     } 
                 });
        return is;
    }

public:
    Meat() : Ingredient(), fatPercentage(0), origin("") {}
    Meat(const string& id, const string& name, double price, double fat, const string& orig)
        : Ingredient(id, name, price), fatPercentage(fat), origin(orig) {}
    Meat(const Meat& other) 
        : Ingredient(other), fatPercentage(other.fatPercentage), origin(other.origin) {}
    
    ~Meat() override {}

    // Переопределение виртуальных методов
    double getCalories() const override {
        return fatPercentage * 10 + 100;
    }

    string getType() const override {
        return "Мясо";
    }

    bool validate() const override {
        return Ingredient::validate() && fatPercentage >= 1 && fatPercentage <= 50 && !origin.empty();
    }

    // Дополнительный метод
    int recommendCookingTime() const {
        if (origin == "говядина") {
            return fatPercentage < 10 ? 30 : 45;
        } else if (origin == "курица") {
            return 25;
        }
        return 30; // значение по умолчанию
    }

    // Перегрузка оператора +=
    Meat& operator+=(double increase) {
        fatPercentage += increase;
        if (fatPercentage > 50) fatPercentage = 50;
        return *this;
    }
};

#endif // KAPRALOV_LR5_6_MEAT_H
