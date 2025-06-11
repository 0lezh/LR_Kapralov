/* Kapralov */
#include "Kapralov_LR7_8_Methods.h"
#include <ctime>
#include <map>
#include <limits>

using namespace std;

struct MenuItem {
    string name;
    void (*func)();
};

int main() {
    srand(time(nullptr));
    map<int, MenuItem> menu = {
        {1, {"Создать идею по умолчанию", createIdeaDefault}},
        {2, {"Создать идею с параметрами", createIdeaParam}},
        {3, {"Тестировать древнюю идею", testAncientIdea}},
        {4, {"Тестировать коллективных авторов", testCollectiveAuthors}},
        {5, {"Тестировать адаптер", testAdapter}},
        {6, {"Сортировать идеи", sortIdeas}},
        {7, {"Найти идею по автору", findIdeaByAuthor}},
        {8, {"Фильтровать идеи по реализациям", filterIdeasByImplCount}}
    };
    while (true) {
        cout << "\nМеню:\n";
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.name << endl;
        }
        cout << "0. Выход\nВыберите действие: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод.\n";
            continue;
        }
        cin.ignore();
        if (choice == 0) break;
        auto it = menu.find(choice);
        if (it != menu.end()) {
            try {
                it->second.func();
            } catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
            }
        } else {
            cout << "Неверный выбор.\n";
        }
    }
    return 0;
}