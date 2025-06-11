#ifndef KAPRALOV_LR5_6_ABSTRACT_INGREDIENT_H
#define KAPRALOV_LR5_6_ABSTRACT_INGREDIENT_H

#include "Kapralov_LR5_6_defIngredients.h"

class Ingredient {
protected:
    string id;
    string name;
    double pricePerUnit;

    virtual ostream& print(ostream& os) const {
        os << "Ингредиент [ID: " << id << ", Название: " << name 
           << ", Цена за единицу: " << pricePerUnit << " руб.]";
        return os;
    }

    virtual istream& input(istream& is) {
        inputData(id, "Введите ID ингредиента: ", validateNonEmptyString);
        inputData(name, "Введите название ингредиента: ", validateNonEmptyString);
        inputData(pricePerUnit, "Введите цену за единицу (руб.): ", validatePositiveNumber);
        return is;
    }

public:
    Ingredient() : id(""), name(""), pricePerUnit(0) {}
    Ingredient(const string& id, const string& name, double price) 
        : id(id), name(name), pricePerUnit(price) {}
    Ingredient(const Ingredient& other) 
        : id(other.id), name(other.name), pricePerUnit(other.pricePerUnit) {}
    
    virtual ~Ingredient() {}

    // Геттеры и сеттеры
    string getId() const { return id; }
    string getName() const { return name; }
    double getPricePerUnit() const { return pricePerUnit; }
    
    void setId(const string& id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void setPricePerUnit(double price) { this->pricePerUnit = price; }

    // Чисто виртуальные методы
    virtual double getCalories() const = 0;
    virtual string getType() const = 0;

    // Метод валидации
    virtual bool validate() const {
        return pricePerUnit > 0 && !id.empty() && !name.empty();
    }

    // Перегрузка операторов
    bool operator==(const Ingredient& other) const {
        return id == other.id;
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Ingredient& ing) {
        return ing.print(os);
    }

    friend istream& operator>>(istream& is, Ingredient& ing) {
        return ing.input(is);
    }
};

#endif // KAPRALOV_LR5_6_ABSTRACT_INGREDIENT_H
