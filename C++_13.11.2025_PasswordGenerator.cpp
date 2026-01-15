#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Чтобы русский работал

using namespace std;

class PasswordGenerator {
private:
    int length;
    bool useDigits;
    bool useSymbols;

    // Статическая переменная (общая для всех объектов)
    static int totalGenerated;

public:
    // Конструктор: настраиваем параметры генератора
    PasswordGenerator(int len, bool digits, bool symbols) {
        length = len;
        useDigits = digits;
        useSymbols = symbols;
    }

    // Метод генерации пароля
    string generate() {
        string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string numbers = "0123456789";
        string specials = "!@#$%^&*()-_=+";

        // Формируем набор допустимых символов
        string chars = alphabet;
        if (useDigits) {
            chars += numbers;
        }
        if (useSymbols) {
            chars += specials;
        }

        string password = "";

        // Собираем пароль
        for (int i = 0; i < length; i++) {
            int index = rand() % chars.length();
            password += chars[index];
        }

        // Увеличиваем общий счетчик
        totalGenerated++;

        return password;
    }

    // Статический метод, чтобы узнать сколько всего нагенерили
    static int getCount() {
        return totalGenerated;
    }
};

// Инициализация статической переменной (обязательно вне класса)
int PasswordGenerator::totalGenerated = 0;

int main() {
    // Настройка консоли и рандома
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    int len;
    char addDig, addSym;

    cout << "--- Настройка генератора ---\n";
    cout << "Длина пароля: ";
    cin >> len;
    cout << "Добавить цифры? (y/n): ";
    cin >> addDig;
    cout << "Добавить спец. символы? (y/n): ";
    cin >> addSym;

    bool useD = (addDig == 'y' || addDig == 'Y');
    bool useS = (addSym == 'y' || addSym == 'Y');

    // Создаем объект генератора с настройками
    PasswordGenerator myGen(len, useD, useS);

    cout << "\nГенерируем пароли...\n";
    cout << "Пароль 1: " << myGen.generate() << endl;
    cout << "Пароль 2: " << myGen.generate() << endl;
    cout << "Пароль 3: " << myGen.generate() << endl;

    // Можно создать другой генератор с другими настройками, счетчик будет общий
    PasswordGenerator shortGen(5, true, false);
    cout << "Короткий пароль: " << shortGen.generate() << endl;

    cout << "\n--------------------------------\n";
    cout << "Всего сгенерировано паролей: " << PasswordGenerator::getCount() << endl;

    return 0;
}
