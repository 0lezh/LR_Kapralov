#ifndef _KAPRALOV_LR7_8_IDEA_H
#define _KAPRALOV_LR7_8_IDEA_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// Предварительное объявление шаблона класса
template <typename YearType, typename AuthorType>
class Idea;

// Предварительное объявление шаблонных функций ввода/вывода
template <typename YearType, typename AuthorType>
ostream& operator<<(ostream& os, const Idea<YearType, AuthorType>& obj);

template <typename YearType, typename AuthorType>
istream& operator>>(istream& is, Idea<YearType, AuthorType>& obj);

template <typename YearType, typename AuthorType>
class Idea {
private:
    string title;
    AuthorType author;
    YearType creationYear;
    vector<string> implementations;

public:
    // Конструкторы
    Idea() : title(""), creationYear(YearType()), implementations() {}
    
    Idea(const string& t, const AuthorType& a, YearType y, const vector<string>& impl = {})
        : title(t), author(a), creationYear(y), implementations(impl) {
        if (y > 2025) throw invalid_argument("Анахроничный год создания");
    }

    template <typename U, typename V>
    Idea(const Idea<U, V>& other)
        : title(other.getTitle()), author(other.getAuthor()), 
          creationYear(other.getCreationYear()), 
          implementations(other.getImplementations()) {}

    Idea(const Idea& other) = default;
    Idea(Idea&& other) noexcept = default;

    // Методы доступа
    string getTitle() const { return title; }
    AuthorType getAuthor() const { return author; }
    YearType getCreationYear() const { return creationYear; }
    vector<string> getImplementations() const { return implementations; }

    void setTitle(const string& t) { title = t; }
    void setAuthor(const AuthorType& a) { author = a; }
    void setCreationYear(YearType y) {
        if (y > 2025) throw invalid_argument("Анахроничный год создания");
        creationYear = y;
    }
    void setImplementations(const vector<string>& impl) { implementations = impl; }

    // Методы
    void addImplementation(const string& impl) {
        if (impl.empty()) throw invalid_argument("Пустая реализация");
        implementations.push_back(impl);
    }

    void printInfo() const {
        cout << "Идея: " << title << "\nАвтор: " << author
             << "\nГод: " << creationYear << "\nРеализации: ";
        for (const auto& impl : implementations) cout << impl << ", ";
        cout << endl;
    }

    bool isAncient() const { return creationYear < 1000; }

    int countImplementations() const { return implementations.size(); }

    string getEra() const {
        if (implementations.empty()) throw logic_error("Пустой список реализаций");
        if (creationYear < 0) return "До нашей эры";
        if (creationYear < 500) return "Раннее Средневековье";
        if (creationYear < 1500) return "Средневековье";
        if (creationYear < 1900) return "Новое время";
        return "Современность";
    }

    // Перегруженные операторы
    Idea operator+(const Idea& other) const {
        Idea result = *this;
        result.implementations.insert(result.implementations.end(),
                                     other.implementations.begin(),
                                     other.implementations.end());
        return result;
    }

    Idea& operator+=(const string& impl) {
        addImplementation(impl);
        return *this;
    }

    Idea& operator++() { ++creationYear; return *this; }
    Idea operator++(int) { Idea temp = *this; ++(*this); return temp; }
    Idea& operator--() { --creationYear; return *this; }
    Idea operator--(int) { Idea temp = *this; --(*this); return temp; }

    Idea& operator=(const Idea& other) = default;
    Idea& operator=(Idea&& other) noexcept = default;

    bool operator<(const Idea& other) const { return creationYear < other.creationYear; }
    bool operator>(const Idea& other) const { return creationYear > other.creationYear; }
    bool operator==(const Idea& other) const { return creationYear == other.creationYear; }

    friend ostream& operator<< <YearType, AuthorType>(ostream& os, const Idea<YearType, AuthorType>& obj);
    friend istream& operator>> <YearType, AuthorType>(istream& is, Idea<YearType, AuthorType>& obj);
};

// Реализация операторов ввода/вывода
template <typename YearType, typename AuthorType>
ostream& operator<<(ostream& os, const Idea<YearType, AuthorType>& obj) {
    os << obj.title << ";" << obj.author << ";" << obj.creationYear << ";";
    for (const auto& impl : obj.implementations) os << impl << ",";
    return os;
}

template <typename YearType, typename AuthorType>
istream& operator>>(istream& is, Idea<YearType, AuthorType>& obj) {
    string temp;
    getline(is, temp, ';');
    obj.setTitle(temp);
    getline(is, temp, ';');
    istringstream iss(temp);
    AuthorType author;
    iss >> author;
    obj.setAuthor(author);
    YearType year;
    is >> year;
    is.ignore(1, ';');
    obj.setCreationYear(year);
    vector<string> impls;
    while (getline(is, temp, ',')) {
        if (!temp.empty()) impls.push_back(temp);
    }
    obj.setImplementations(impls);
    return is;
}

// Специализация для коллективных авторов
template <typename YearType>
class Idea<YearType, vector<string>> {
private:
    string title;
    vector<string> author;
    YearType creationYear;
    vector<string> implementations;

public:
    Idea() : title(""), creationYear(YearType()), implementations() {}
    
    Idea(const string& t, const vector<string>& a, YearType y, const vector<string>& impl = {})
        : title(t), author(a), creationYear(y), implementations(impl) {
        if (y > 2025) throw invalid_argument("Анахроничный год создания");
        if (a.empty()) throw invalid_argument("Пустой список авторов");
    }

    template <typename U, typename V>
    Idea(const Idea<U, V>& other)
        : title(other.getTitle()), author(other.getAuthor()), 
          creationYear(other.getCreationYear()), 
          implementations(other.getImplementations()) {}

    Idea(const Idea& other) = default;
    Idea(Idea&& other) noexcept = default;

    // Методы доступа
    string getTitle() const { return title; }
    vector<string> getAuthor() const { return author; }
    YearType getCreationYear() const { return creationYear; }
    vector<string> getImplementations() const { return implementations; }

    void setTitle(const string& t) { title = t; }
    void setAuthor(const vector<string>& a) {
        if (a.empty()) throw invalid_argument("Пустой список авторов");
        author = a;
    }
    void setCreationYear(YearType y) {
        if (y > 2025) throw invalid_argument("Анахроничный год создания");
        creationYear = y;
    }
    void setImplementations(const vector<string>& impl) { implementations = impl; }

    // Методы
    void addImplementation(const string& impl) {
        if (impl.empty()) throw invalid_argument("Пустая реализация");
        implementations.push_back(impl);
    }

    void printInfo() const {
        cout << "Идея: " << title << "\nАвторы: ";
        for (const auto& a : author) cout << a << ", ";
        cout << "\nГод: " << creationYear << "\nРеализации: ";
        for (const auto& impl : implementations) cout << impl << ", ";
        cout << endl;
    }

    bool isAncient() const { return creationYear < 1000; }

    int countImplementations() const { return implementations.size(); }

    string getEra() const {
        if (implementations.empty()) throw logic_error("Пустой список реализаций");
        if (creationYear < 0) return "До нашей эры";
        if (creationYear < 500) return "Раннее Средневековье";
        if (creationYear < 1500) return "Средневековье";
        if (creationYear < 1900) return "Новое время";
        return "Современность";
    }

    int countCoAuthors() const { return author.size(); }

    bool hasAuthor(const string& name) const {
        return find(author.begin(), author.end(), name) != author.end();
    }

    // Перегруженные операторы
    Idea operator+(const Idea& other) const {
        Idea result = *this;
        result.implementations.insert(result.implementations.end(),
                                     other.implementations.begin(),
                                     other.implementations.end());
        return result;
    }

    Idea& operator+=(const string& impl) {
        addImplementation(impl);
        return *this;
    }

    Idea& operator++() { ++creationYear; return *this; }
    Idea operator++(int) { Idea temp = *this; ++(*this); return temp; }
    Idea& operator--() { --creationYear; return *this; }
    Idea operator--(int) { Idea temp = *this; --(*this); return temp; }

    Idea& operator=(const Idea& other) = default;
    Idea& operator=(Idea&& other) noexcept = default;

    bool operator<(const Idea& other) const { return creationYear < other.creationYear; }
    bool operator>(const Idea& other) const { return creationYear > other.creationYear; }
    bool operator==(const Idea& other) const { return creationYear == other.creationYear; }

    friend ostream& operator<< <YearType, vector<string>>(ostream& os, const Idea<YearType, vector<string>>& obj);
    friend istream& operator>> <YearType, vector<string>>(istream& is, Idea<YearType, vector<string>>& obj);
};

// Реализация операторов ввода/вывода для специализации
template <typename YearType>
ostream& operator<<(ostream& os, const Idea<YearType, vector<string>>& obj) {
    os << obj.title << ";";
    for (size_t i = 0; i < obj.author.size(); ++i) {
        os << obj.author[i];
        if (i < obj.author.size() - 1) os << ",";
    }
    os << ";" << obj.creationYear << ";";
    for (const auto& impl : obj.implementations) os << impl << ",";
    return os;
}

template <typename YearType>
istream& operator>>(istream& is, Idea<YearType, vector<string>>& obj) {
    string temp;
    getline(is, temp, ';');
    obj.setTitle(temp);

    getline(is, temp, ';');
    vector<string> authors;
    string author;
    istringstream iss(temp);
    while (getline(iss, author, ',')) {
        if (!author.empty()) authors.push_back(author);
    }
    obj.setAuthor(authors);

    YearType year;
    is >> year;
    is.ignore(1, ';');
    obj.setCreationYear(year);

    vector<string> impls;
    while (getline(is, temp, ',')) {
        if (!temp.empty()) impls.push_back(temp);
    }
    obj.setImplementations(impls);

    return is;
}

#endif // _KAPRALOV_LR7_8_IDEA_H