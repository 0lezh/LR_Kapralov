#ifndef KAPRALOV_LR5_6_DEF_INGREDIENTS_H
#define KAPRALOV_LR5_6_DEF_INGREDIENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <sstream>

using namespace std;

// Функция проверки ввода положительного числа
inline bool validatePositiveNumber(const string& input) {
    if (input.empty()) return false;
    try {
        double num = stod(input);
        return num > 0;
    } catch (...) {
        return false;
    }
}

// Функция проверки ввода непустой строки
inline bool validateNonEmptyString(const string& input) {
    return !input.empty();
}

// Шаблонная функция для ввода данных
template<typename T>
void inputData(T& var, const string& prompt, function<bool(const string&)> validator) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
    } while (!validator(input));
    
    istringstream iss(input);
    iss >> var;
}

#endif // KAPRALOV_LR5_6_DEF_INGREDIENTS_H
