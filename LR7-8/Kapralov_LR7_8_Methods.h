#ifndef _KAPRALOV_LR7_8_METHODS_H
#define _KAPRALOV_LR7_8_METHODS_H

#include "Kapralov_LR7_8_Idea.h"
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
bool validateInput(T& value, const string& prompt) {
    cout << prompt << ": ";
    string input;
    getline(cin, input);
    istringstream iss(input);
    if (iss >> value && iss.eof()) return true;
    cout << "Некорректный ввод. Попробуйте снова.\n";
    return false;
}

bool validateInput(string& value, const string& prompt) {
    cout << prompt << ": ";
    getline(cin, value);
    return !value.empty();
}

void createIdeaDefault() {
    Idea<int, string> idea;
    cout << "Идея по умолчанию:\n";
    idea.printInfo();
}

void createIdeaParam() {
    string title, author;
    int year;
    vector<string> impls;
    if (validateInput(title, "Введите название идеи") &&
        validateInput(author, "Введите автора") &&
        validateInput(year, "Введите год создания")) {
        string impl;
        cout << "Введите реализации (пустая строка для завершения):\n";
        while (getline(cin, impl) && !impl.empty()) {
            impls.push_back(impl);
        }
        try {
            Idea<int, string> idea(title, author, year, impls);
            cout << "Создана идея:\n";
            idea.printInfo();
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
}

void testAncientIdea() {
    try {
        Idea<int, string> ancient("Пирамиды", "Фараон", -2500, {"Каменные блоки"});
        cout << "Древняя идея:\n";
        ancient.printInfo();
        cout << "До нашей эры: " << (ancient.isAncient() ? "Да" : "Нет") << endl;
        cout << "Исторический период: " << ancient.getEra() << endl;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void testCollectiveAuthors() {
    try {
        vector<string> authors = {"Иванов", "Петров"};
        Idea<int, vector<string>> idea("Кооператив", authors, 2020, {"Прототип"});
        cout << "Идея с коллективными авторами:\n";
        idea.printInfo();
        cout << "Количество соавторов: " << idea.countCoAuthors() << endl;
        cout << "Есть автор Иванов: " << (idea.hasAuthor("Иванов") ? "Да" : "Нет") << endl;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

template <template <typename...> class Container>
class IdeaAdapter {
private:
    Container<string> implementations;
public:
    IdeaAdapter(const Idea<int, string>& idea) {
        auto impls = idea.getImplementations();
        implementations = Container<string>(impls.begin(), impls.end());
    }
    void print() const {
        cout << "Реализации в контейнере: ";
        for (const auto& impl : implementations) cout << impl << ", ";
        cout << endl;
    }
};

void testAdapter() {
    try {
        Idea<int, string> idea("Тест", "Автор", 2020, {"Импл1", "Импл2"});
        IdeaAdapter<vector> vecAdapter(idea);
        IdeaAdapter<list> listAdapter(idea);
        IdeaAdapter<set> setAdapter(idea);
        cout << "Вектор:\n";
        vecAdapter.print();
        cout << "Список:\n";
        listAdapter.print();
        cout << "Множество:\n";
        setAdapter.print();
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void sortIdeas() {
    vector<Idea<int, string>> ideas = {
        {"Идея1", "Автор1", 2000, {"Импл1"}},
        {"Идея2", "Автор2", 1990, {"Импл2"}},
        {"Идея3", "Автор3", 2010, {"Импл3"}}
    };
    sort(ideas.begin(), ideas.end());
    cout << "Отсортированные идеи по году:\n";
    for (const auto& idea : ideas) idea.printInfo();
}

void findIdeaByAuthor() {
    vector<Idea<int, string>> ideas = {
        {"Идея1", "Иванов", 2000, {"Импл1"}},
        {"Идея2", "Петров", 1990, {"Импл2"}}
    };
    string author;
    if (validateInput(author, "Введите автора для поиска")) {
        bool found = false;
        for (const auto& idea : ideas) {
            if (idea.getAuthor() == author) {
                idea.printInfo();
                found = true;
            }
        }
        if (!found) cout << "Идеи автора " << author << " не найдены.\n";
    }
}

void filterIdeasByImplCount() {
    vector<Idea<int, string>> ideas = {
        {"Идея1", "Автор1", 2000, {"Импл1"}},
        {"Идея2", "Автор2", 1990, {"Импл2", "Импл3"}},
        {"Идея3", "Автор3", 2010, {"Импл4", "Импл5", "Импл6"}}
    };
    int minImpls;
    if (validateInput(minImpls, "Введите минимальное количество реализаций")) {
        cout << "Идеи с реализациями >= " << minImpls << ":\n";
        for (const auto& idea : ideas) {
            if (idea.countImplementations() >= minImpls) idea.printInfo();
        }
    }
}

#endif // _KAPRALOV_LR7_8_METHODS_H