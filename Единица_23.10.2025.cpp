#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;


// 1. КЛАСС ПРЕДМЕТА

class Item {
public:
    string name;
    int weight;

    Item(string n, int w) : name(n), weight(w) {}
};


// 2. КЛАСС РЮКЗАКА

class Backpack {
private:
    vector<Item> items;
    int maxWeight;
    int currentWeight;

public:
    Backpack(int limit) : maxWeight(limit), currentWeight(0) {}

    bool addItem(Item item) {
        if (currentWeight + item.weight <= maxWeight) {
            items.push_back(item);
            currentWeight += item.weight;
            return true;
        }
        return false;
    }

    void showItems() {
        if (items.empty()) {
            cout << "  [Рюкзак пуст]" << endl;
            return;
        }
        cout << "  [Содержимое (" << currentWeight << "/" << maxWeight << " кг)]:" << endl;
        for (const auto& item : items) {
            cout << "    - " << item.name << " (" << item.weight << " кг)" << endl;
        }
    }
};


// 3. КЛАСС ИГРОВОЙ КАРТЫ

class GameMap {
private:
    int width, height;

public:
    GameMap(int w, int h) : width(w), height(h) {}

    bool isWithinBounds(int x, int y) const {
        return (x >= 0 && x < width && y >= 0 && y < height);
    }

    void render(int unitX, int unitY) const {
        cout << "\n--- КАРТА МИРА ---" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == unitY && j == unitX)
                    cout << " P "; 
                else
                    cout << " . "; // привет :)
            }
            cout << endl;
        }
        cout << "------------------" << endl;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// 4. КЛАСС ЮНИТА

class Unit {
private:
    string name;
    int health;
    int x, y;
    Backpack inventory;

public:
    Unit(string n, int startX, int startY, int bagLimit)
        : name(n), x(startX), y(startY), health(100), inventory(bagLimit) {
    }

    void move(char direction, const GameMap& world) {
        int nextX = x;
        int nextY = y;

        switch (tolower(direction)) {
        case 'w': nextY--; break;
        case 's': nextY++; break;
        case 'a': nextX--; break;
        case 'd': nextX++; break;
        default: return;
        }

        if (world.isWithinBounds(nextX, nextY)) {
            x = nextX;
            y = nextY;
        }
        else {
            cout << "!!! Ошибка: Впереди непреодолимая преграда (край карты)!" << endl;
            Sleep(500); 
        }
    }

    void pickUp(Item item) {
        if (inventory.addItem(item)) {
            cout << ">> Вы подобрали: " << item.name << endl;
        }
        else {
            cout << ">> Слишком тяжело! Не удалось взять: " << item.name << endl;
        }
        Sleep(700);
    }

    void displayStatus() {
        cout << "\nПЕРСОНАЖ: " << name << " | Здоровье: " << health << "%" << endl;
        cout << "Координаты: (" << x << ", " << y << ")" << endl;
        inventory.showItems();
    }

    int getX() const { return x; }
    int getY() const { return y; }
};


// ГЛАВНАЯ ФУНКЦИЯ

int main() {
 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    GameMap level(15, 7);
    Unit hero("Бродяга", 0, 0, 30); 


    hero.pickUp(Item("Ржавый меч", 10));
    hero.pickUp(Item("Кожаная броня", 15));

    char action;
    while (true) {
        system("cls");
        hero.displayStatus();
        level.render(hero.getX(), hero.getY());

        cout << "\nУправление (W-A-S-D), Взять предмет (E), Выход (Q): ";
        cin >> action;
        action = tolower(action);

        if (action == 'q') break;

        if (action == 'e') {
            hero.pickUp(Item("Тяжелый камень", 10));
        }
        else {
            hero.move(action, level);
        }
    }

    cout << "Игра завершена. До встречи!" << endl;
    return 0;
}
