// KapralovLR3-4_main.cpp
#include <ctime>
#include <map>
#include <iomanip>
#include "KapralovLR3-4_Methods.h"

int main() {
    srand(time(NULL));
    map<int, MenuItem> menu = {
        {1, {"Создать идею с полными параметрами", createIdeaWithAllParams}},
        {2, {"Показать массив идей", showArrayIdeas}},
        {3, {"Вычислить средние затраты идеи", calcAvgCostIdea}},
        {4, {"Сложить две идеи", addIdeas}},
        {5, {"Отсортировать идеи по году", sortIdeasByYear}}
    };
    unsigned choice = 0;
    while (true) {
        cout << "Меню:" << endl;
        for (const auto& item : menu)
            cout << item.first << ". " << item.second.title << endl;
        cout << "0. Выход" << endl;
        enterNumber(choice, "Введите номер пункта: ");
        if (choice == 0) {
            cout << "Программа завершена. Капралов 2025" << endl;
            break;
        }
        cout << "\n========== Действие: ==========\n";
        if (menu.find(choice) != menu.end())
            menu[choice].action();
        else
            cout << "Некорректный ввод." << endl;
        cout << endl;
    }
    return 0;
}