#include <iostream>
#include <cmath>

class Vector2d {
public:
    double x, y;

    // Конструкторы
    Vector2d() : x(0.0), y(0.0) {}
    Vector2d(double _x, double _y) : x(_x), y(_y) {}

    // Сложение
    Vector2d operator+(const Vector2d& other) const {
        return Vector2d(x + other.x, y + other.y);
    }

    // Вычитание
    Vector2d operator-(const Vector2d& other) const {
        return Vector2d(x - other.x, y - other.y);
    }

    // Умножение на число (скаляр)
    Vector2d operator*(double scalar) const {
        return Vector2d(x * scalar, y * scalar);
    }

    // Унарный минус (инверсия вектора)
    Vector2d operator-() const {
        return Vector2d(-x, -y);
    }

    // Операторы присваивания с операцией
    Vector2d& operator+=(const Vector2d& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2d& operator-=(const Vector2d& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Сравнение
    bool operator==(const Vector2d& other) const {
        // В реальных проектах double сравнивают через epsilon, 
        // но для учебного примера сойдет и так.
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Vector2d& other) const {
        return !(*this == other);
    }

    // Доступ по индексу (0 для x, 1 для y)
    double& operator[](int index) {
        return (index == 0) ? x : y;
    }

    // Вычисление длины вектора (не оператор, но полезно)
    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // Дружественная функция для вывода в консоль (cout << v)
    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};
