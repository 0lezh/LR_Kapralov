#ifndef KAPRALOV_LR5_6_NUTRITION_CALCULATOR_H
#define KAPRALOV_LR5_6_NUTRITION_CALCULATOR_H

#include "Kapralov_LR5_6_AbstractIngredient.h"
#include <vector>

class NutritionCalculator {
protected:
    virtual double calculateTotalCalories(const vector<Ingredient*>& ingredients) const {
        double total = 0;
        for (const auto& ing : ingredients) {
            total += ing->getCalories();
        }
        return total;
    }
};

#endif // KAPRALOV_LR5_6_NUTRITION_CALCULATOR_H
