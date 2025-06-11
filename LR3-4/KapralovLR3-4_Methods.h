// KapralovLR3-4_Methods.h
#ifndef METHODS_H
#define METHODS_H
#include "KapralovLR3-4_Idea.h"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>

vector<Idea> vectorOfAllIdeas;

bool isValidNumber(const string& str) {
    try {
        size_t pos;
        stod(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

void enterNumber(unsigned& num, const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
    } while (!isValidNumber(input));
    num = stoi(input);
}

void enterInt(int& num, const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
    } while (!isValidNumber(input));
    num = stoi(input);
}

void createIdeaWithAllParams() {
    string name, author;
    int year;
    unsigned count;
    cout << "Введите название идеи: ";
    getline(cin, name);
    cout << "Введите автора: ";
    getline(cin, author);
    enterInt(year, "Введите год создания: ");
    enterNumber(count, "Введите количество реализаций: ");
    vector<string> impls;
    vector<double> costs;
    for (unsigned i = 0; i < count; i++) {
        cout << "Введите реализацию " << i + 1 << ": ";
        string impl;
        getline(cin, impl);
        impls.push_back(impl);
        string input;
        do {
            cout << "Введите затраты для реализации " << i + 1 << ": ";
            getline(cin, input);
        } while (!isValidNumber(input));
        costs.push_back(stod(input));
    }
    Idea idea(name, author, year, impls, costs);
    vectorOfAllIdeas.push_back(idea);
    cout << "Идея создана: " << idea << endl;
}

void showArrayIdeas() {
    if (vectorOfAllIdeas.empty()) {
        cout << "Массив идей пуст." << endl;
        return;
    }
    for (size_t i = 0; i < vectorOfAllIdeas.size(); i++)
        cout << "Идея " << i + 1 << ": " << vectorOfAllIdeas[i] << endl;
}

void calcAvgCostIdea() {
    if (vectorOfAllIdeas.empty()) {
        cout << "Массив идей пуст." << endl;
        return;
    }
    unsigned idx;
    enterNumber(idx, "Введите индекс идеи: ");
    if (idx >= vectorOfAllIdeas.size()) {
        cout << "Некорректный индекс." << endl;
        return;
    }
    cout << "Средние затраты: " << fixed << setprecision(2) << vectorOfAllIdeas[idx].calculateAverageCost() << endl;
}

void addIdeas() {
    if (vectorOfAllIdeas.size() < 2) {
        cout << "Недостаточно идей для сложения." << endl;
        return;
    }
    unsigned idx1, idx2;
    enterNumber(idx1, "Введите индекс первой идеи: ");
    enterNumber(idx2, "Введите индекс второй идеи: ");
    if (idx1 >= vectorOfAllIdeas.size() || idx2 >= vectorOfAllIdeas.size()) {
        cout << "Некорректный индекс." << endl;
        return;
    }
    Idea result = vectorOfAllIdeas[idx1] + vectorOfAllIdeas[idx2];
    vectorOfAllIdeas.push_back(result);
    cout << "Результат сложения: " << result << endl;
}

void sortIdeasByYear() {
    if (vectorOfAllIdeas.empty()) {
        cout << "Массив идей пуст." << endl;
        return;
    }
    vector<Idea> sortedIdeas = vectorOfAllIdeas;
    sort(sortedIdeas.begin(), sortedIdeas.end());
    cout << "Идеи, отсортированные по году создания:" << endl;
    for (size_t i = 0; i < sortedIdeas.size(); i++)
        cout << "Идея " << i + 1 << ": " << sortedIdeas[i] << endl;
}

struct MenuItem {
    string title;
    void (*action)();
};

#endif 