tox:C3B6E6A3C58C0E1DAF62A136BD43FC94A21D3FD86EB9086A0B4FEE1573A71048624B7701C9EE

// KapralovLR3-4_Idea.cpp
#include "KapralovLR3-4_Idea.h"
#include <cmath>
#include <iomanip>
#include <algorithm>

Idea::Idea(string n, string a, int y, vector<string> impl, vector<double> c) : name(n), author(a), creationYear(y) {
    setIdea(n, a, y, impl, c);
}

Idea::Idea(const Idea& other) : name(other.name), author(other.author), creationYear(other.creationYear),
    implementations(other.implementations), costs(other.costs) {}

void Idea::setIdea(string n, string a, int y, const vector<string>& impl, const vector<double>& c) {
    if (impl.size() == c.size()) {
        name = n;
        author = a;
        creationYear = y;
        implementations = impl;
        costs = c;
    } else {
        cerr << "Ошибка: Количество реализаций не совпадает с количеством затрат." << endl;
    }
}

double Idea::calculateAverageCost() const {
    double sum = 0;
    for (const auto& cost : costs) sum += cost;
    return costs.empty() ? 0.0 : sum / costs.size();
}

Idea Idea::operator+(const Idea& other) const {
    Idea result = *this;
    result.implementations.insert(result.implementations.end(), other.implementations.begin(), other.implementations.end());
    result.costs.insert(result.costs.end(), other.costs.begin(), other.costs.end());
    return result;
}

Idea& Idea::operator++() {
    creationYear++;
    return *this;
}

Idea Idea::operator++(int) {
    Idea temp = *this;
    ++(*this);
    return temp;
}

Idea& Idea::operator--() {
    creationYear--;
    return *this;
}

Idea Idea::operator--(int) {
    Idea temp = *this;
    --(*this);
    return temp;
}

const Idea& Idea::operator=(const Idea& other) {
    if (this != &other) {
        name = other.name;
        author = other.author;
        creationYear = other.creationYear;
        implementations = other.implementations;
        costs = other.costs;
    }
    return *this;
}

ostream& operator<<(ostream& mystream, const Idea& obj) {
    mystream << "Идея: " << obj.name << ", Автор: " << obj.author << ", Год: " << obj.creationYear
             << ", Средние затраты: " << fixed << setprecision(2) << obj.calculateAverageCost() << endl
             << "Реализации: ";
    for (const auto& impl : obj.implementations) mystream << impl << " ";
    mystream << endl << "Затраты: ";
    for (const auto& cost : obj.costs) mystream << fixed << setprecision(2) << cost << " ";
    return mystream;
}

istream& operator>>(istream& mystream, Idea& obj) {
    string st;
    cout << "Введите название идеи: ";
    getline(mystream, obj.name);
    cout << "Введите автора: ";
    getline(mystream, obj.author);
    cout << "Введите год создания: ";
    getline(mystream, st);
    obj.creationYear = stoi(st);
    obj.implementations.clear();
    obj.costs.clear();
    unsigned count;
    cout << "Введите количество реализаций: ";
    getline(mystream, st);
    count = stoi(st);
    for (unsigned i = 0; i < count; i++) {
        cout << "Введите реализацию " << i + 1 << ": ";
        string impl;
        getline(mystream, impl);
        obj.implementations.push_back(impl);
        cout << "Введите затраты для реализации " << i + 1 << ": ";
        getline(mystream, st);
        obj.costs.push_back(stod(st));
    }
    return mystream;
}
